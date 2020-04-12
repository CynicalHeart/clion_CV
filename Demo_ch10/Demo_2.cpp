/**
 *  Shi-Tomasi �ǵ����������ؼ��ǵ���
 */
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME "Shi-Tomasi�ǵ���"

Mat g_srcImage,g_grayImage;
int g_maxCornerNumber = 33;
int g_maxTrackBarNumber = 500;
RNG g_rng(12345);

void on_GoodFeaturesToTrack(int, void *);
int main() {
    g_srcImage = imread("F:\\��Ѷ\\ͼ\\ޱ������.jpg");
    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);

    namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
    createTrackbar("���ǵ���", WINDOW_NAME, &g_maxCornerNumber, g_maxTrackBarNumber, on_GoodFeaturesToTrack);
    imshow(WINDOW_NAME, g_srcImage);
    on_GoodFeaturesToTrack(0, 0);
    waitKey(0);

    return 0;
}
void on_GoodFeaturesToTrack(int, void *){
    if(g_maxCornerNumber<=1){ g_maxCornerNumber = 1; }

    //Shi-Tomasi����Ԥ��
    vector<Point2f> corners;
    double qualityLevel = 0.01; //�ǵ�����Խ��ܵ���С����ֵ
    double minDistance = 10; //�ǵ�֮��������
    int blockSize = 3; //���㵼������ؾ���ʱָ��������Χ
    double k = 0.04; //Ȩ��ϵ��
    Mat copy = g_srcImage.clone(); //ԭͼ���ƹ�����������Ȥ������
    //Shi-Tomasi�ǵ���
    goodFeaturesToTrack(g_grayImage, corners, g_maxCornerNumber, qualityLevel, minDistance, Mat(), blockSize, false, k);

    cout<<"�˴μ�⵽�Ľǵ���ĿΪ��"<<corners.size()<<endl;

    //���ƽǵ�
    int r = 4;
    for (int i = 0; i <corners.size() ; ++i) {
        circle(copy, corners[i], r, Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)), -1, 8,
               0);
    }

    imshow(WINDOW_NAME,copy);

    /*------------------------�����ؽǵ���-----------------------*/
    //����׼��
    Size winSize = Size(5, 5);//(5*2+1)*(5*2+1) ��11*11����������
    Size zeroZone = Size(-1, -1);//������

    TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::MAX_ITER, 40, 0.001);
    //����������ؽǵ�λ��
    cornerSubPix(g_grayImage, corners, winSize, zeroZone, criteria);
    //����ǵ���Ϣ
    for (int j = 0; j <corners.size() ; ++j) {
        cout<<"��׼�ǵ���"<<j<<":["<<corners[j].x<<","<<corners[j].y<<"]"<<endl;
    }
}

