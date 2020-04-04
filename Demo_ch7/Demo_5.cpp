#include <iostream>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
/**
 *  直方图均衡化
 */
int main() {
    Mat srcImage,dstImage;
    srcImage = imread("F:\\腾讯\\图\\薇尔莉特.jpg",1);

    //灰度化
    cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
    imshow("原始图", srcImage);
    //进行直方图均衡化后的图
    equalizeHist(srcImage, dstImage);

    imshow("直方图均衡化后的图", dstImage);
    waitKey(0);
    return 0;
}

