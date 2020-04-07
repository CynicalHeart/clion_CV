/**
 * 寻找凸包并绘制案例  - convexHull()
 */
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
#define WINDOW_NAME1 "原始图窗口"
#define WINDOW_NAME2 "效果图窗口"

Mat g_srcImage,g_grayImage;
int g_nThresh = 50;
int g_maxThresh = 255;
RNG g_rng(12345);
Mat srcImage_copy = g_srcImage.clone();
Mat g_thresholdImage_output;
vector<vector<Point>> g_vContours;
vector<Vec4i> g_vHierarchy;

void on_ThreshChange(int, void *);

int main() {
    g_srcImage = imread("F:\\腾讯\\图\\67814952_p0_master1200.jpg");

    //灰度降噪
    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
    blur(g_grayImage, g_grayImage, Size(3, 3));
    //创建窗口并显示
    namedWindow(WINDOW_NAME1, 1);
    imshow(WINDOW_NAME1, g_srcImage);
    //创建滚动条
    createTrackbar("阈值", WINDOW_NAME1, &g_nThresh, g_maxThresh, on_ThreshChange);
    on_ThreshChange(0, 0);
    waitKey(0);
    return 0;
}

void on_ThreshChange(int, void *){
    //二值化，控制阈值
    threshold(g_grayImage, g_thresholdImage_output, g_nThresh, 255, THRESH_BINARY);
    //寻找轮廓
    findContours(g_thresholdImage_output, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    //遍历每个轮廓寻找凸包
    vector<vector<Point>> hull(g_vContours.size());
    for (int i = 0; i <g_vContours.size() ; ++i) {
        convexHull(Mat(g_vContours[i]),hull[i], false);
    }
    //绘初轮廓及其凸包
    Mat drawing = Mat::zeros(g_thresholdImage_output.size(), CV_8UC3);
    for (unsigned i = 0; i <g_vContours.size() ; ++i) {
        Scalar color = Scalar(g_rng.uniform(0,255),g_rng.uniform(0,255),g_rng.uniform(0,255));
        drawContours(drawing,g_vContours,i,color,1,8,vector<Vec4i>(),0,Point());
        drawContours(drawing,hull,i,color,1,8,vector<Vec4i>(),0,Point());
    }

    imshow(WINDOW_NAME2, drawing);
}

