#include "../header/Demo_ch9_2.h"

void drawHS02() {
    //????????HSV??????
    Mat srcImage,hsvImage;
    srcImage = imread("F:\\腾讯\\图\\刃.jpg");
    cvtColor(srcImage,hsvImage,COLOR_BGR2HSV);
    //???????
    //??????????30???????????????????32?????
    int hueBinNum = 30;//?????????????
    int saturationBinNum = 32;//?????????????????
    int histSize[] = {hueBinNum,saturationBinNum};
    //????????仯??Χ 0-179
    float hueRanges[] = {0,180};
    //???履????仯??Χ0(????)??255?????????????
    float saturationRanges[] = {0,256};
    const float* ranges[] = {hueRanges,saturationRanges};
    MatND dstHist; //Mat ?2? MatND ???
    //calcHist?????? ?????0??????1?????????
    int channels[] = {0,1};
    calcHist(&hsvImage, //????????
            1,//???????
            channels,//???????
            Mat(),//????????
            dstHist,//??????????
            2,//???
            histSize,//??????????????
            ranges,//?????????Χ
            true,//??????
            false //???????
            );
    //???????
    double maxValue = 0;
    minMaxLoc(dstHist, 0, &maxValue, 0, 0);
    int scale = 10;
    Mat histImage = Mat::zeros(saturationBinNum * scale, hueBinNum * 10, CV_8UC3);
    for (int hue = 0; hue <hueBinNum ; ++hue) {
        for (int saturation = 0; saturation <saturationBinNum ; ++saturation) {
            float binValue = dstHist.at<float>(hue, saturation);
            int intensity = cvRound(binValue * 255 / maxValue);//???
            //????
            rectangle(histImage, Point(hue * scale, saturation * scale),
                      Point((hue + 1) * scale - 1, (saturation + 1) * scale - 1), Scalar::all(intensity), FILLED);
        }
    }
    imshow("素材图", srcImage);
    imshow("H-S直方图", histImage);
    waitKey(0);
}

void drawHS01(){
    Mat srcImage = imread("F:\\腾讯\\图\\75878503_p0.png", 0);
    imshow("原始图", srcImage);
    //定义变量
    MatND dstHist;
    int dims = 1;//1维度
    float hranges[] = {0,255};
    const float *range[] = {hranges};
    int size = 256; //区段数目
    int channels = 0;//通道索引

    calcHist(&srcImage, 1, &channels, Mat(), dstHist, dims, &size, range);
    cout<<"size经历calcHist后的大小"<<size<<endl;
    int scale = 1;
    //获取最大最小值
    Mat dstImage(size * scale, size, CV_8U, Scalar(0));
    double minValue = 0;
    double maxValue = 0;
    minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);
    //绘制出直方图
    int hpt = saturate_cast<int>(0.9 * size);//防止像素溢出
    for (int i = 0; i <256 ; ++i) {
        float binValue = dstHist.at<float>(i);
        int realValue = saturate_cast<float>(binValue * hpt / maxValue);
        rectangle(dstImage,Point(i*scale,size-1),Point((i+1)*scale-1,size-realValue),Scalar(255));
    }
    imshow("一维直方图", dstImage);
    waitKey(0);
}

void drawHSRHB(){
    Mat srcImage = imread("F:\\腾讯\\图\\jing.jpg");
    imshow("素材图",srcImage);
    //参数准备
    int bins = 256;
    int hist_size[] = {bins};
    float range[] = {0,256};
    const float *ranges[] = {range};
    MatND redHist,greenHist,blueHist;
    //红色分量
    int channels_r[] = {0};
    calcHist(&srcImage, 1, channels_r, Mat(), redHist, 1, hist_size, ranges, true, false);
    //绿色分量
    int channels_g[] = {1};
    calcHist(&srcImage, 1, channels_g, Mat(), greenHist, 1, hist_size, ranges, true, false);
    //蓝色分量
    int channels_b[] = {2};
    calcHist(&srcImage, 1, channels_b, Mat(), blueHist, 1, hist_size, ranges, true, false);
    //绘制
    double maxValue_red,maxValue_green,maxValue_blue;
    minMaxLoc(redHist,0,&maxValue_red,0,0);
    minMaxLoc(greenHist,0,&maxValue_green,0,0);
    minMaxLoc(blueHist, 0, &maxValue_blue, 0, 0);
    int scale = 1;
    int histHeight = 256;
    Mat histImage = Mat::zeros(histHeight,bins*3,CV_8UC3);
    for (int i = 0; i <bins; ++i) {
        float binValue_red = redHist.at<float>(i);
        float binValue_green = greenHist.at<float>(i);
        float binValue_blue = blueHist.at<float>(i);
        int intensity_red = cvRound(binValue_red*histHeight/maxValue_red);
        int intensity_green = cvRound(binValue_green*histHeight/maxValue_green);
        int intensity_blue = cvRound(binValue_blue*histHeight/maxValue_blue);
        //绘制红色分量的直方图
        rectangle(histImage,Point(i*scale,histHeight-1),Point((i+1)*scale-1,histHeight-intensity_red),Scalar(255,0,0));
        //绘制绿色分量的直方图
        rectangle(histImage,Point((i+bins)*scale,histHeight-1),Point((i+bins+1)*scale-1,histHeight-intensity_green),Scalar(0,255,0));
        //绘制蓝色分量的直方图
        rectangle(histImage,Point((i+bins*2)*scale,histHeight-1),Point((i+1+2*bins)*scale-1,histHeight-intensity_blue),Scalar(0,0,255));
    }
    imshow("图像的RBG直方图", histImage);
    waitKey(0);
}


