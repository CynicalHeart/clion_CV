/**
 * 直方图对比-compareHist
 */
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

int main() {
    Mat srcImage_base, hsvImage_base;
    Mat srcImage_test1, hsvImage_test1;
    Mat srcImage_test2, hsvImage_test2;
    Mat hsvImage_halfDown;

    srcImage_base = imread("F:\\腾讯\\图\\73340944_p0_master1200.jpg",1);
    srcImage_test1 = imread("F:\\腾讯\\图\\74653002_p0.png",1);
    srcImage_test2 = imread("F:\\腾讯\\图\\74653002_p8.png",1);

    imshow("基准图像", srcImage_base);
    imshow("测试图像1", srcImage_test1);
    imshow("测试图像2", srcImage_test2);
    //RGB转HSV
    cvtColor(srcImage_base, hsvImage_base, COLOR_BGR2HSV);
    cvtColor(srcImage_test1, hsvImage_test1, COLOR_BGR2HSV);
    cvtColor(srcImage_test2, hsvImage_test2, COLOR_BGR2HSV);
    //图片下半身
    hsvImage_halfDown = hsvImage_base(Range(hsvImage_base.rows/2, hsvImage_base.rows - 1), Range(0, hsvImage_base.cols - 1));
    //初始化计算直方图需要的参数
    int h_bins = 50, s_bins = 60;
    int histSize[] = {h_bins,s_bins};
    float h_ranges[] = {0,256};
    float s_ranges[] = {0,180};
    const float *range[] = {h_ranges,s_ranges};
    int channels[] = {0,1};
    MatND baseHist, halfDownHist, testHist1, testHist2;//目标数组
    //计算直方图 并做归一化处理
    calcHist(&hsvImage_base,1,channels,Mat(),baseHist,2,histSize,range, true, false);
    normalize(baseHist, baseHist, 0, 1, NORM_MINMAX);

    calcHist(&hsvImage_halfDown,1,channels,Mat(),halfDownHist,2,histSize,range, true, false);
    normalize(halfDownHist, halfDownHist, 0, 1, NORM_MINMAX);

    calcHist(&hsvImage_test1,1,channels,Mat(),testHist1,2,histSize,range, true, false);
    normalize(testHist1, testHist1, 0, 1, NORM_MINMAX);

    calcHist(&hsvImage_test2,1,channels,Mat(),testHist2,2,histSize,range, true, false);
    normalize(testHist2, testHist2, 0, 1, NORM_MINMAX);

    for (int i = 0; i <4 ; ++i) {
        int compare_method = i;
        double base_base = compareHist(baseHist, baseHist, compare_method);
        double base_half = compareHist(baseHist, halfDownHist, compare_method);
        double base_test1 = compareHist(baseHist, testHist1, compare_method);
        double base_test2 = compareHist(baseHist, testHist2, compare_method);
        //输出结果
        cout<<"方法"<<(i+1)<<"的匹配结果如下\n"<<"[基准图-基准图]:"<<base_base<<","
        <<"[基准图-半身图]:"<<base_half<<",[基准图-测试图1]:"<<base_test1<<",[基准图-测试图2]:"<<base_test2<<endl;
    }
    cout<<"\n检测结束"<<endl;
    waitKey(0);
    return 0;
}

