/**
 *  harris�ǵ��������(��ԻҶ�ͼL��)
 */
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
#define WINDOW_NAME1 "���򴰿�1"
#define WINDOW_NAME2 "���򴰿�2"

Mat g_srcImage,g_srcImage1,g_grayImage;
int thresh = 30; // ��ǰ��ֵ
int max_thresh = 175;

void on_CornerHarris(int, void *);

int main() {
    g_srcImage = imread("F:\\��Ѷ\\ͼ\\77564597_p0.png",1);
    if (!g_srcImage.data) {
        cout<<"��ȡͼƬ����"<<endl;
    }
    imshow("ԭʼͼ", g_srcImage);
    g_srcImage1 = g_srcImage.clone();
    //����һ�ŻҶ�ͼ
    cvtColor(g_srcImage1, g_grayImage, COLOR_BGR2GRAY);
    //�������ڡ���������
    namedWindow(WINDOW_NAME1,1);
    createTrackbar("��ֵ", WINDOW_NAME1, &thresh, max_thresh, on_CornerHarris);
    on_CornerHarris(0, 0);
    waitKey(0);
    return 0;
}

void on_CornerHarris(int, void *){
    Mat dstImage;//Ŀ��
    Mat normImage;//��һ��
    Mat scaledImage; //���Ա任��İ�λ�޷�������ͼ

    dstImage = Mat::zeros(g_srcImage.size(), CV_32FC1);
    g_srcImage1 = g_srcImage.clone();

    //���
    cornerHarris(g_grayImage,dstImage,2,3,0.04,BORDER_DEFAULT);
    //��һ��
    normalize(dstImage,normImage,0,255,NORM_MINMAX,CV_32FC1,Mat());
    //����һ����ͼ���Ա任��8λ�޷�������
    convertScaleAbs(normImage, scaledImage);

    //����
    for (int i = 0; i <normImage.rows ; ++i) {
        for (int j = 0; j <normImage.cols ; ++j) {
            if ((int) normImage.at<float>(i, j) > thresh + 80) {
                circle(g_srcImage1, Point(j, i), 5, Scalar(10, 10, 255), 2, 8, 0);
                circle(scaledImage, Point(j, i), 5, Scalar(10, 10, 255), 2, 8, 0);
            }
        }
    }
    imshow(WINDOW_NAME1, g_srcImage1);
    imshow(WINDOW_NAME2, scaledImage);
}

