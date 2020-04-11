/**
 * ģ��ƥ��
 */
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

#define WINDOW_NAME1 "ԭʼ����"
#define WINDOW_NAME2 "Ч������"

Mat g_srcImage,g_templateImage,g_resultImage;
int g_nMatchMethod=0;
int g_nMaxTrackBarNum = 5;

void on_Matching(int, void *);

int main() {
    g_srcImage = imread("G:\\src.jpg",1);
    g_templateImage = imread("G:\\t.jpg", 1);//ģ��ͼҪС��ԭͼ

    namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
    namedWindow(WINDOW_NAME2, WINDOW_AUTOSIZE);
    //��������������ʼ��һ��
    createTrackbar("����",WINDOW_NAME1,&g_nMatchMethod,g_nMaxTrackBarNum,on_Matching);
    on_Matching(0, 0);
    waitKey(0);
    return 0;
}

void on_Matching(int, void *){
    Mat srcImage;
    g_srcImage.copyTo(srcImage);
    //ƥ����ͼ�Ĵ�С��(W-w+1)*(H-h+1)
    int resultImage_rows = g_srcImage.rows-g_templateImage.rows+1;
    int resultImage_cols = g_srcImage.cols-g_templateImage.cols+1;
    g_resultImage.create(resultImage_rows, resultImage_cols, CV_32FC1);//������32λ���㵥ͨ��
    //ƥ�䲢�ұ�׼��
    matchTemplate(g_srcImage, g_templateImage, g_resultImage, g_nMatchMethod);
    normalize(g_resultImage, g_resultImage, 0, 1, NORM_MINMAX,-1,Mat());
    //ͨ��minMaxLoc��λ��ƥ���λ��
    double minValue,maxValue;
    Point minLocation,maxLocation;
    Point matchLocation;
    minMaxLoc(g_resultImage,&minValue,&maxValue,&minLocation,&maxLocation);

    //����SQDIFF �� SQDIFF_NORMED ԽС��ֵƥ��Ч��Խ�ã�����Ķ���ֵԽ��Խ��
    if(g_nMatchMethod == TM_SQDIFF || g_nMatchMethod == TM_SQDIFF_NORMED){
        matchLocation = minLocation;
    } else{
        matchLocation = maxLocation;
    }
    //���Ƴ�����
    rectangle(srcImage, matchLocation,
              Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows),Scalar(0,0,255),2,8,0);
    rectangle(g_resultImage, matchLocation,
              Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows),Scalar(0,0,255),2,8,0);
    imshow(WINDOW_NAME1, srcImage);
    imshow(WINDOW_NAME2, g_resultImage);
}
