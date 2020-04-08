/**
 * 图像的矩
 */
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

#define WINDOW_NAME1 "原始图"
#define WINDOW_NAME2 "图像轮廓"

Mat g_srcImage,g_grayImage;
int g_nThresh = 100;
int g_nMaxThresh = 255;
RNG g_rng(1245);
Mat g_cannyMat_output;
vector<vector<Point>> g_vContours;
vector<Vec4i> g_vHierarchy;

void on_ThreshChange(int, void *);

int main() {
    g_srcImage = imread("F:\\腾讯\\图\\67814952_p0_master1200.jpg");
    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
    namedWindow(WINDOW_NAME1, 1);
    imshow(WINDOW_NAME1, g_srcImage);

    createTrackbar("阈值", WINDOW_NAME1, &g_nThresh, g_nMaxThresh, on_ThreshChange);
    on_ThreshChange(0, 0);
    waitKey(0);

    return 0;
}
void on_ThreshChange(int, void *){
    Canny(g_grayImage, g_cannyMat_output, g_nThresh, 2 * g_nThresh, 3);
    //找到轮廓
    findContours(g_cannyMat_output, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    //计算矩
    vector<Moments> mu(g_vContours.size());
    for (int i = 0; i <g_vContours.size() ; ++i) {
        mu[i] = moments(g_vContours[i], false);
    }
    //计算中心距
    vector<Point2f> mc(g_vContours.size());
    for (int j = 0; j <g_vContours.size() ; ++j) {
        mc[j] = Point2f(static_cast<float>(mu[j].m10/mu[j].m00),static_cast<float>(mu[j].m01/mu[j].m00));
    }

    Mat drawing = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);
    for (int  k = 0; k <g_vContours.size() ; ++k) {
        Scalar color = Scalar(g_rng.uniform(0,255),g_rng.uniform(0,255),g_rng.uniform(0, 255));
        drawContours(drawing, g_vContours, k, color, 2, 8, g_vHierarchy, 0, Point(0, 0));
        circle(drawing, mc[k], 4, color, -1, 8, 0);
    }
    namedWindow(WINDOW_NAME2, 1);
    imshow(WINDOW_NAME2, drawing);

    cout<<"输出轮廓面积和轮廓长度"<<endl;
    for (int l = 0;l<g_vContours.size(); ++l) {
        cout << "轮廓面积为:" << contourArea(g_vContours[l]) << ",长度为:" << arcLength(g_vContours[l], true)<<endl;
        Scalar color = Scalar(g_rng.uniform(0,255),g_rng.uniform(0,255),g_rng.uniform(0, 255));
        drawContours(drawing, g_vContours, l, color, 2, 8, g_vHierarchy, 0, Point(0, 0));
        circle(drawing, mc[l], 4, color, -1, 8, 0);
    }
}

