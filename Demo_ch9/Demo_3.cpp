/**
 * ֱ��ͼ�Ա�-compareHist
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

    srcImage_base = imread("F:\\��Ѷ\\ͼ\\73340944_p0_master1200.jpg",1);
    srcImage_test1 = imread("F:\\��Ѷ\\ͼ\\74653002_p0.png",1);
    srcImage_test2 = imread("F:\\��Ѷ\\ͼ\\74653002_p8.png",1);

    imshow("��׼ͼ��", srcImage_base);
    imshow("����ͼ��1", srcImage_test1);
    imshow("����ͼ��2", srcImage_test2);
    //RGBתHSV
    cvtColor(srcImage_base, hsvImage_base, COLOR_BGR2HSV);
    cvtColor(srcImage_test1, hsvImage_test1, COLOR_BGR2HSV);
    cvtColor(srcImage_test2, hsvImage_test2, COLOR_BGR2HSV);
    //ͼƬ�°���
    hsvImage_halfDown = hsvImage_base(Range(hsvImage_base.rows/2, hsvImage_base.rows - 1), Range(0, hsvImage_base.cols - 1));
    //��ʼ������ֱ��ͼ��Ҫ�Ĳ���
    int h_bins = 50, s_bins = 60;
    int histSize[] = {h_bins,s_bins};
    float h_ranges[] = {0,256};
    float s_ranges[] = {0,180};
    const float *range[] = {h_ranges,s_ranges};
    int channels[] = {0,1};
    MatND baseHist, halfDownHist, testHist1, testHist2;//Ŀ������
    //����ֱ��ͼ ������һ������
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
        //������
        cout<<"����"<<(i+1)<<"��ƥ��������\n"<<"[��׼ͼ-��׼ͼ]:"<<base_base<<","
        <<"[��׼ͼ-����ͼ]:"<<base_half<<",[��׼ͼ-����ͼ1]:"<<base_test1<<",[��׼ͼ-����ͼ2]:"<<base_test2<<endl;
    }
    cout<<"\n������"<<endl;
    waitKey(0);
    return 0;
}

