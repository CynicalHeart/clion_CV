/**
 *  harris角点检测与绘制(针对灰度图L形)
 */
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
#define WINDOW_NAME1 "程序窗口1"
#define WINDOW_NAME2 "程序窗口2"

Mat g_srcImage,g_srcImage1,g_grayImage;
int thresh = 30; // 当前阈值
int max_thresh = 175;

void on_CornerHarris(int, void *);

int main() {
    g_srcImage = imread("F:\\腾讯\\图\\77564597_p0.png",1);
    if (!g_srcImage.data) {
        cout<<"读取图片错误"<<endl;
    }
    imshow("原始图", g_srcImage);
    g_srcImage1 = g_srcImage.clone();
    //留存一张灰度图
    cvtColor(g_srcImage1, g_grayImage, COLOR_BGR2GRAY);
    //创建窗口、滑动条和
    namedWindow(WINDOW_NAME1,1);
    createTrackbar("阈值", WINDOW_NAME1, &thresh, max_thresh, on_CornerHarris);
    on_CornerHarris(0, 0);
    waitKey(0);
    return 0;
}

void on_CornerHarris(int, void *){
    Mat dstImage;//目标
    Mat normImage;//归一化
    Mat scaledImage; //线性变换后的八位无符号整型图

    dstImage = Mat::zeros(g_srcImage.size(), CV_32FC1);
    g_srcImage1 = g_srcImage.clone();

    //检测
    cornerHarris(g_grayImage,dstImage,2,3,0.04,BORDER_DEFAULT);
    //归一化
    normalize(dstImage,normImage,0,255,NORM_MINMAX,CV_32FC1,Mat());
    //将归一化的图线性变换成8位无符号整型
    convertScaleAbs(normImage, scaledImage);

    //绘制
    for (int i = 0; i <normImage.rows ; ++i) {
        for (int j = 0; j <normImage.cols ; ++j) {
            if ((int) normImage.at<float>(i, j) > thresh + 80) {
                circle(g_srcImage1, Point(j, i), 5, Scalar(10, 10, 255), 2, 8, 0);
                circle(scaledImage, Point(j, i), 5, Scalar(10, 10, 255), 2, 8, 0);
            }
        }
    }
    imshow(WINDOW_NAME1, g_srcImage1);
    imshow(WINDOW_NAME2, scaledImage);
}

