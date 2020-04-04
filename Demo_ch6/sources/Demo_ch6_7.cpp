#include "../header/Demo_ch6_7.h"

int g_nThresholdValue = 100;
int g_nThresholdType = 3;
Mat g_srcImage,g_grayImage,g_dstImage;

void on_Threshold(int, void *){
    threshold(g_grayImage, g_dstImage, g_nThresholdValue, 255, g_nThresholdType);
    imshow(WINDOW_NAME, g_dstImage);
}

void Threshold_Demo(){
    g_srcImage = imread("F:\\��Ѷ\\ͼ\\chouyou.jpg");
    if(g_srcImage.empty()){
        cout<<"��ȡͼƬ����"<<endl;
        return;
    }
    imshow("ԭͼ", g_srcImage);
    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);

    namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
    createTrackbar("ģʽ",WINDOW_NAME,&g_nThresholdType,4,on_Threshold);
    createTrackbar("����ֵ",WINDOW_NAME,&g_nThresholdValue,255,on_Threshold);

    on_Threshold(0,0);

    while(1){
        int key;
        key = waitKey(20);
        if((char)key==27){break;}
    }

}

