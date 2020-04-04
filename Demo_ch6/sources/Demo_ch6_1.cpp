#include"../header/Demo_ch6_1.h"

Mat g_srcImage, g_dstImage1, g_dstImage2, g_dstImage3,g_dstImage4,g_dstImage5;
int g_nBoxFilterValue = 6;//方框滤波参数
int g_nMeanBlurValue = 10;//均值滤波参数
int g_nGaussianBlurValue = 6;//高斯滤波参数
int g_nMedianBlurValue = 10;//均值滤波参数
int g_nBilateralFilterValue = 10;//双边滤波参数

void on_BoxFilter(int, void*)
{
    boxFilter(g_srcImage, g_dstImage1, -1, Size(g_nBoxFilterValue + 1, g_nBoxFilterValue + 1));
    imshow("【方框滤波】", g_dstImage1);
}

void on_MeanBlur(int, void*)
{
    blur(g_srcImage, g_dstImage2, Size(g_nMeanBlurValue + 1, g_nMeanBlurValue + 1), Point(-1, -1));
    imshow("【均值滤波】", g_dstImage2);
}

void on_GaussianBlur(int, void*)
{
    GaussianBlur(g_srcImage, g_dstImage3, Size(g_nGaussianBlurValue * 2 + 1, g_nGaussianBlurValue * 2 + 1), 0, 0);
    imshow("【高斯滤波】", g_dstImage3);
}
void on_MedianBlur(int, void *)
{
    medianBlur(g_srcImage,g_dstImage4,g_nMedianBlurValue*2+1);
    imshow("【中值滤波】", g_dstImage4);
}
void on_BilateralFilter(int, void *)
{
    bilateralFilter(g_srcImage,g_dstImage5,g_nBilateralFilterValue,g_nBilateralFilterValue*2,g_nBilateralFilterValue/2);
    imshow("【双边滤波】",g_dstImage5);
}

void Blur_Demo() {
    g_srcImage = imread("F:\\腾讯\\图\\67814952_p0_master1200.jpg", 1);
    if(g_srcImage.empty()){
        cout<<"读取图片错误"<<endl;
    }

    g_dstImage1 = g_srcImage.clone();
    g_dstImage2 = g_srcImage.clone();
    g_dstImage3 = g_srcImage.clone();
    g_dstImage4 = g_srcImage.clone();
    g_dstImage5 = g_srcImage.clone();

    namedWindow("【显示原图】", 1);
    imshow("【显示原图】", g_srcImage);

    /* ====================== 方框滤波 ======================= */
    namedWindow("【方框滤波】", 1);
    createTrackbar("内核值", "【方框滤波】", &g_nBoxFilterValue, 50, on_BoxFilter);
    on_BoxFilter(g_nBoxFilterValue, 0);
    /* ====================== 均值滤波 ======================= */
    namedWindow("【均值滤波】", 1);
    createTrackbar("内核值", "【均值滤波】", &g_nMeanBlurValue, 50, on_MeanBlur);
    on_MeanBlur(g_nMeanBlurValue, 0);
    /* ====================== 高斯滤波 ======================= */
    namedWindow("【高斯滤波】", 1);
    createTrackbar("内核值", "【高斯滤波】", &g_nGaussianBlurValue, 50, on_GaussianBlur);
    on_GaussianBlur(g_nGaussianBlurValue, 0);
    /* ====================== 中值滤波 ======================= */
    namedWindow("【中值滤波】", 1);
    createTrackbar("内核值", "【中值滤波】", &g_nMedianBlurValue, 50, on_MedianBlur);
    on_MedianBlur(g_nMedianBlurValue, 0);
    /* ====================== 双边滤波 ======================= */
    namedWindow("【双边滤波】", 1);
    createTrackbar("内核值", "【双边滤波】", &g_nBilateralFilterValue, 50, on_BilateralFilter);
    on_BilateralFilter(g_nBilateralFilterValue, 0);

    cout << "调整滚动条观察图像效果" << endl << "按q退出程序" << endl;

    while (char(waitKey(1)) != 'q') {}
}


