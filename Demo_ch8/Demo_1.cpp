/**
 * 查找并绘制轮廓
 */
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

#define WINDOW_NAME1 "原始图窗口"
#define WINDOW_NAME2 "轮廓图"

Mat g_srcImage,g_grayImage;
int g_nThresh = 80;
int g_nThresh_max = 255;
RNG g_rng(12345);//产生随机数
Mat g_cannyMat_output;
vector<vector<Point>> g_vContours;
vector<Vec4i> g_vHierarchy;

void on_ThreshChange(int, void *);

int main() {
    g_srcImage = imread("F:\\腾讯\\图\\191223_03.jpg",1);
    if (!g_srcImage.data) {
        cout <<"图片读取错误"<< endl;
        return false;
    }
    //灰度并降噪
    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
    blur(g_grayImage, g_grayImage, Size(3, 3));
    //创建窗口
    namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
    imshow(WINDOW_NAME1,g_srcImage);
    //创建滑动条
    createTrackbar("canny", WINDOW_NAME1, &g_nThresh, g_nThresh_max, on_ThreshChange);
    on_ThreshChange(0, 0);//初始化

    waitKey(0);

    return 0;
}

void on_ThreshChange(int, void *){
    //canny边缘检测
    Canny(g_grayImage, g_cannyMat_output, g_nThresh, g_nThresh * 2, 3);
    //寻找轮廓
    findContours(g_cannyMat_output, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    //绘制轮廓
    Mat drawing = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);//黑色目标图初始
    for (int i = 0; i < g_vContours.size() ; ++i) {//轮廓数循环
        Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
        drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point(0, 0));
    }
    imshow(WINDOW_NAME2, drawing);
}


