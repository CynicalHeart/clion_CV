#include "../header/Demo_ch7_1.h"

Mat g_srcImage,g_grayImage,g_dstImage;

Mat g_cannyDetectedEdges;
int g_cannyLowThreshold = 1;

Mat g_sobelGradient_X,g_sobelGradient_Y;
Mat g_sobelAbsGradient_X,g_sobelAbsGradient_Y;
int g_sobelKernelSize = 1;

Mat g_scharrGradient_X,g_scharrGradient_Y;
Mat g_scharrAbsGradient_X,g_scharrAbsGradient_Y;

void on_Canny(int, void *){
    //先降噪
    blur(g_grayImage, g_cannyDetectedEdges, Size(3, 3));
    //运用算子
    Canny(g_cannyDetectedEdges,g_cannyDetectedEdges,g_cannyLowThreshold,g_cannyLowThreshold*3,3);
    //目标图黑屏
    g_dstImage = Scalar::all(0);
    //将Canny算子输出的边缘图g_cannyDetectedEdges作为掩码，来将源图拷贝到目标图
    g_srcImage.copyTo(g_dstImage, g_cannyDetectedEdges);

    imshow("Canny边缘检测", g_dstImage);
}

void on_Sobel(int, void *){
    //X方向梯度
    Sobel(g_srcImage,g_sobelGradient_X,CV_16S,1,0,2*g_sobelKernelSize+1,1,1,BORDER_DEFAULT);
    convertScaleAbs(g_sobelGradient_X,g_sobelAbsGradient_X);//计算绝对值并将结果转为8位
    //Y方向梯度
    Sobel(g_srcImage,g_sobelGradient_Y,CV_16S,0,1,2*g_sobelKernelSize+1,1,1,BORDER_DEFAULT);
    convertScaleAbs(g_sobelGradient_Y, g_sobelAbsGradient_Y);

    //合并梯度
    addWeighted(g_sobelAbsGradient_X,0.5,g_sobelAbsGradient_Y,0.5,0,g_dstImage);

    imshow("Sobel边缘检测",g_dstImage);
}

void Scharr(){
    Scharr(g_srcImage,g_scharrGradient_X,CV_16S,1,0,1,0,BORDER_DEFAULT);
    convertScaleAbs(g_scharrGradient_X, g_scharrAbsGradient_X);

    Scharr(g_srcImage,g_scharrGradient_Y,CV_16S,0,1,1,0,BORDER_DEFAULT);
    convertScaleAbs(g_scharrGradient_Y, g_scharrAbsGradient_Y);

    //合并梯度
    addWeighted(g_scharrAbsGradient_X, 0.5, g_scharrAbsGradient_Y, 0.5, 0, g_dstImage);

    imshow("Scharr滤波器",g_dstImage);
}

void Canny_Demo(){
    g_srcImage = imread("F:\\腾讯\\图\\chouyou.jpg");
    /*if(g_srcImage.empty()){
        cout<<"读片读取失败"<<endl;
        return;
    }*/
    namedWindow("【原始图】");
    imshow("【原始图】",g_srcImage);

    g_dstImage.create(g_srcImage.size(),g_srcImage.type());
    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);

    namedWindow("Canny边缘检测", WINDOW_AUTOSIZE);
    namedWindow("Sobel边缘检测", WINDOW_AUTOSIZE);
    namedWindow("Scharr滤波器", WINDOW_AUTOSIZE);

    createTrackbar("参数值","Canny边缘检测",&g_cannyLowThreshold,120,on_Canny);
    createTrackbar("参数值","Sobel边缘检测",&g_sobelKernelSize,3,on_Sobel);
    on_Canny(0, 0);
    on_Sobel(0, 0);

    Scharr();

    while ((char(waitKey(1))!='q')){}
}


