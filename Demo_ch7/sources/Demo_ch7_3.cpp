#include "../header/Demo_ch7_3.h"

Mat g_srcImage,g_dstImage;
Mat g_map_x,g_map_y;


void CVMap_Demo() {
    ShowHelpText();

    g_srcImage = imread("F:\\腾讯\\图\\chouyou.jpg");
    if(!g_srcImage.data){
        cout<<"读取图片错误"<<endl;
    }
    imshow("原始图", g_srcImage);

    g_dstImage.create(g_srcImage.size(),g_srcImage.type());
    g_map_x.create(g_srcImage.size(),CV_32FC1);
    g_map_y.create(g_srcImage.size(),CV_32FC1);

    namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
    imshow(WINDOW_NAME, g_srcImage);

    while(1){
        int key = waitKey(0);
        if((key&255) == 27){
            cout<<"程序退出"<<endl;
            break;
        }
        update_map(key);
        remap(g_srcImage, g_dstImage, g_map_x, g_map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
        imshow(WINDOW_NAME, g_dstImage);
    }
}

void ShowHelpText() {
    cout<<"重映射示例程序"<<endl;
    cout<<"当前openCV版本为"<<CV_VERSION<<endl;
    cout<<endl;
    cout<<"按键说明:"<<endl;
    cout<<"\t键盘按ESC - 退出程序"<<endl;
    cout<<"\t键盘按1 - 第一种映射方式"<<endl;
    cout<<"\t键盘按2 - 第二种映射方式"<<endl;
    cout<<"\t键盘按3 - 第三种映射方式"<<endl;
    cout<<"\t键盘按4 - 第四种映射方式"<<endl;
}

int update_map(int key) {
    for (int i = 0; i <g_srcImage.rows ; ++i) {
        for (int j = 0; j <g_srcImage.cols ; ++j) {
            switch(key){
                case '1':
                    if(j>g_srcImage.cols*0.25&&j<g_srcImage.cols*0.75&&i>g_srcImage.rows*0.25&&i<g_srcImage.rows*0.75) {
                        g_map_x.at<float>(i,j) = static_cast<float>(2*(j-g_srcImage.cols*0.25)+0.5);
                        g_map_y.at<float>(i,j) = static_cast<float>(2*(i-g_srcImage.rows*0.25)+0.5);
                    } else{
                        g_map_x.at<float>(i,j) = 0;
                        g_map_y.at<float>(i, j) = 0;
                    }
                    break;
                case '2':
                    g_map_x.at<float>(i,j) = static_cast<float>(j);
                    g_map_y.at<float>(i, j) = static_cast<float>(g_srcImage.rows-i);
                    break;
                case '3':
                    g_map_x.at<float>(i, j) = static_cast<float>(g_srcImage.cols - j);
                    g_map_y.at<float>(i,j) = static_cast<float>(i);
                    break;
                case '4':
                    g_map_x.at<float>(i, j) = static_cast<float>(g_srcImage.cols - j);
                    g_map_y.at<float>(i, j) = static_cast<float>(g_srcImage.rows - i);
                    break;
            }
        }
    }
    return 1;
}

void Affine_Demo() {
    ShowHelpText_2();
    Point2f srcTriangle[3];
    Point2f dstTriangle[3];

    Mat rotMat(2, 3, CV_32FC1);
    Mat warpMat(2, 3, CV_32FC1);
    Mat srcImage, dstImage_warp, dstImage_warp_rotate;

    srcImage = imread("F:\\腾讯\\图\\67814952_p0_master1200.jpg");
    dstImage_warp = Mat::zeros(srcImage.rows, srcImage.cols, srcImage.type());

    //原图三点对应目标图三点
    srcTriangle[0] = Point2f(0, 0);
    srcTriangle[1] = Point2f(static_cast<float>(srcImage.cols - 1), 0);
    srcTriangle[2] = Point2f(0, static_cast<float>(srcImage.rows-1));

    dstTriangle[0] = Point2f(static_cast<float>(srcImage.cols*0.0), static_cast<float>(srcImage.rows*0.33));
    dstTriangle[1] = Point2f(static_cast<float>(srcImage.cols*0.65), static_cast<float>(srcImage.rows*0.35));
    dstTriangle[2] = Point2f(static_cast<float>(srcImage.cols*0.15), static_cast<float>(srcImage.rows*0.6));
    //求的仿射变换
    warpMat = getAffineTransform(srcTriangle, dstTriangle);
    //应用仿射变换
    warpAffine(srcImage, dstImage_warp, warpMat, dstImage_warp.size());

    //对图像进行缩放后再旋转
    Point center = Point(dstImage_warp.cols/2,dstImage_warp.rows/2);
    double angle = -30;
    double scale = 0.8;
    //求得旋转矩阵
    rotMat = getRotationMatrix2D(center, angle, scale);
    //旋转已经缩放后的图像
    warpAffine(dstImage_warp,dstImage_warp_rotate,rotMat,dstImage_warp.size());

    imshow(WINDOW_NAME1, srcImage);
    imshow(WINDOW_NAME2, dstImage_warp);
    imshow(WINDOW_NAME3, dstImage_warp_rotate);
    waitKey(0);
}

void ShowHelpText_2() {
    cout<<"欢迎来到【仿射变换】示例程序"<<endl;
    cout<<"\t当前使用的OpenCV版本为"<<CV_VERSION<<endl;
}

