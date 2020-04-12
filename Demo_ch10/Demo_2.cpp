/**
 *  Shi-Tomasi 角点检测与亚像素级角点检测
 */
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME "Shi-Tomasi角点检测"

Mat g_srcImage,g_grayImage;
int g_maxCornerNumber = 33;
int g_maxTrackBarNumber = 500;
RNG g_rng(12345);

void on_GoodFeaturesToTrack(int, void *);
int main() {
    g_srcImage = imread("F:\\腾讯\\图\\薇尔莉特.jpg");
    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);

    namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
    createTrackbar("最大角点数", WINDOW_NAME, &g_maxCornerNumber, g_maxTrackBarNumber, on_GoodFeaturesToTrack);
    imshow(WINDOW_NAME, g_srcImage);
    on_GoodFeaturesToTrack(0, 0);
    waitKey(0);

    return 0;
}
void on_GoodFeaturesToTrack(int, void *){
    if(g_maxCornerNumber<=1){ g_maxCornerNumber = 1; }

    //Shi-Tomasi参数预备
    vector<Point2f> corners;
    double qualityLevel = 0.01; //角点检测可以接受的最小特征值
    double minDistance = 10; //角点之间的最距离
    int blockSize = 3; //计算导数自相关矩阵时指定的邻域范围
    double k = 0.04; //权重系数
    Mat copy = g_srcImage.clone(); //原图复制过来当做感兴趣的区域
    //Shi-Tomasi角点检测
    goodFeaturesToTrack(g_grayImage, corners, g_maxCornerNumber, qualityLevel, minDistance, Mat(), blockSize, false, k);

    cout<<"此次检测到的角点数目为："<<corners.size()<<endl;

    //绘制角点
    int r = 4;
    for (int i = 0; i <corners.size() ; ++i) {
        circle(copy, corners[i], r, Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)), -1, 8,
               0);
    }

    imshow(WINDOW_NAME,copy);

    /*------------------------亚像素角点检测-----------------------*/
    //参数准备
    Size winSize = Size(5, 5);//(5*2+1)*(5*2+1) 即11*11的搜索窗口
    Size zeroZone = Size(-1, -1);//无死区

    TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::MAX_ITER, 40, 0.001);
    //计算出亚像素角点位置
    cornerSubPix(g_grayImage, corners, winSize, zeroZone, criteria);
    //输出角点信息
    for (int j = 0; j <corners.size() ; ++j) {
        cout<<"精准角点坐"<<j<<":["<<corners[j].x<<","<<corners[j].y<<"]"<<endl;
    }
}

