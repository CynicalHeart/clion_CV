#include <iostream>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
/**
 *  ֱ��ͼ���⻯
 */
int main() {
    Mat srcImage,dstImage;
    srcImage = imread("F:\\��Ѷ\\ͼ\\ޱ������.jpg",1);

    //�ҶȻ�
    cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
    imshow("ԭʼͼ", srcImage);
    //����ֱ��ͼ���⻯���ͼ
    equalizeHist(srcImage, dstImage);

    imshow("ֱ��ͼ���⻯���ͼ", dstImage);
    waitKey(0);
    return 0;
}

