/**
 * 模板匹配
 */
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

#define WINDOW_NAME1 "原始窗口"
#define WINDOW_NAME2 "效果窗口"

Mat g_srcImage,g_templateImage,g_resultImage;
int g_nMatchMethod=0;
int g_nMaxTrackBarNum = 5;

void on_Matching(int, void *);

int main() {
    g_srcImage = imread("G:\\src.jpg",1);
    g_templateImage = imread("G:\\t.jpg", 1);//模板图要小于原图

    namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
    namedWindow(WINDOW_NAME2, WINDOW_AUTOSIZE);
    //创建滑动条并初始化一次
    createTrackbar("方法",WINDOW_NAME1,&g_nMatchMethod,g_nMaxTrackBarNum,on_Matching);
    on_Matching(0, 0);
    waitKey(0);
    return 0;
}

void on_Matching(int, void *){
    Mat srcImage;
    g_srcImage.copyTo(srcImage);
    //匹配结果图的大小：(W-w+1)*(H-h+1)
    int resultImage_rows = g_srcImage.rows-g_templateImage.rows+1;
    int resultImage_cols = g_srcImage.cols-g_templateImage.cols+1;
    g_resultImage.create(resultImage_rows, resultImage_cols, CV_32FC1);//必须是32位浮点单通道
    //匹配并且标准化
    matchTemplate(g_srcImage, g_templateImage, g_resultImage, g_nMatchMethod);
    normalize(g_resultImage, g_resultImage, 0, 1, NORM_MINMAX,-1,Mat());
    //通过minMaxLoc定位最匹配的位置
    double minValue,maxValue;
    Point minLocation,maxLocation;
    Point matchLocation;
    minMaxLoc(g_resultImage,&minValue,&maxValue,&minLocation,&maxLocation);

    //对于SQDIFF 和 SQDIFF_NORMED 越小的值匹配效果越好，其余的都是值越大越好
    if(g_nMatchMethod == TM_SQDIFF || g_nMatchMethod == TM_SQDIFF_NORMED){
        matchLocation = minLocation;
    } else{
        matchLocation = maxLocation;
    }
    //绘制出矩阵
    rectangle(srcImage, matchLocation,
              Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows),Scalar(0,0,255),2,8,0);
    rectangle(g_resultImage, matchLocation,
              Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows),Scalar(0,0,255),2,8,0);
    imshow(WINDOW_NAME1, srcImage);
    imshow(WINDOW_NAME2, g_resultImage);
}
