/**
 * 反向投影
 */
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

#define WINDOW_NAME "原始图"

Mat g_srcImage,g_hsvImage,g_hueImage;
int g_bins = 30;

void on_BinChange(int, void *);

int main() {
    g_srcImage = imread("F:\\腾讯\\图\\chouyou.jpg",1);
    cvtColor(g_srcImage,g_hsvImage,COLOR_BGR2HSV);
    //分离Hue色调通道
    g_hueImage.create(g_hsvImage.size(), g_hsvImage.depth());
    int ch[] = {0,0};
    //待复制原始图、第一个参数的矩阵数目、被复制图、分离矩阵数目、索引(原图通道对目标通道)、索引对数
    mixChannels(&g_hsvImage, 1, &g_hueImage, 1, ch, 1);

    namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
    createTrackbar("色调组距",WINDOW_NAME,&g_bins,180,on_BinChange);
    on_BinChange(0, 0);//初始化

    imshow(WINDOW_NAME, g_srcImage);

    waitKey(0);
    return 0;
}
void on_BinChange(int, void *){
    MatND hist;
    int histSize = MAX(g_bins, 2);
    float hue_range[] = {0,180};
    const float *ranges[] = {hue_range};

    //计算并归一化
    calcHist(&g_hueImage, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false);
    normalize(hist,hist,0,255,NORM_MINMAX);
    //计算 反向投影
    MatND backproj;
    calcBackProject(&g_hueImage, 1, 0, hist, backproj, ranges,1, true);
    imshow("反向投影图", backproj);
    //绘制
    int w = 400, h = 400;
    int bin_w = cvRound((double) w / histSize);//单组距间隔
    Mat histImg = Mat::zeros(w, h, CV_8UC3);
    for (int i = 0; i <g_bins ; ++i) {
        rectangle(histImg, Point(i * bin_w, h), Point((i + 1) * bin_w, h - cvRound(hist.at<float>(i) * h / 255.0)),
                  Scalar(100, 123, 255), -1);
    }
    imshow("直方图", histImg);
}
