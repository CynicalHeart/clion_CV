#include "../header/Demo_ch6_7.h"

int g_nThresholdValue = 100;
int g_nThresholdType = 3;
Mat g_srcImage,g_grayImage,g_dstImage;

void on_Threshold(int, void *){
    threshold(g_grayImage, g_dstImage, g_nThresholdValue, 255, g_nThresholdType);
    imshow(WINDOW_NAME, g_dstImage);
}

void Threshold_Demo(){
    g_srcImage = imread("F:\\腾讯\\图\\chouyou.jpg");
    if(g_srcImage.empty()){
        cout<<"读取图片错误"<<endl;
        return;
    }
    imshow("原图", g_srcImage);
    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);

    namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
    createTrackbar("模式",WINDOW_NAME,&g_nThresholdType,4,on_Threshold);
    createTrackbar("参数值",WINDOW_NAME,&g_nThresholdValue,255,on_Threshold);

    on_Threshold(0,0);

    while(1){
        int key;
        key = waitKey(20);
        if((char)key==27){break;}
    }

}

