/**
 * ����ͶӰ
 */
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

#define WINDOW_NAME "ԭʼͼ"

Mat g_srcImage,g_hsvImage,g_hueImage;
int g_bins = 30;

void on_BinChange(int, void *);

int main() {
    g_srcImage = imread("F:\\��Ѷ\\ͼ\\chouyou.jpg",1);
    cvtColor(g_srcImage,g_hsvImage,COLOR_BGR2HSV);
    //����Hueɫ��ͨ��
    g_hueImage.create(g_hsvImage.size(), g_hsvImage.depth());
    int ch[] = {0,0};
    //������ԭʼͼ����һ�������ľ�����Ŀ��������ͼ�����������Ŀ������(ԭͼͨ����Ŀ��ͨ��)����������
    mixChannels(&g_hsvImage, 1, &g_hueImage, 1, ch, 1);

    namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
    createTrackbar("ɫ�����",WINDOW_NAME,&g_bins,180,on_BinChange);
    on_BinChange(0, 0);//��ʼ��

    imshow(WINDOW_NAME, g_srcImage);

    waitKey(0);
    return 0;
}
void on_BinChange(int, void *){
    MatND hist;
    int histSize = MAX(g_bins, 2);
    float hue_range[] = {0,180};
    const float *ranges[] = {hue_range};

    //���㲢��һ��
    calcHist(&g_hueImage, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false);
    normalize(hist,hist,0,255,NORM_MINMAX);
    //���� ����ͶӰ
    MatND backproj;
    calcBackProject(&g_hueImage, 1, 0, hist, backproj, ranges,1, true);
    imshow("����ͶӰͼ", backproj);
    //����
    int w = 400, h = 400;
    int bin_w = cvRound((double) w / histSize);//�������
    Mat histImg = Mat::zeros(w, h, CV_8UC3);
    for (int i = 0; i <g_bins ; ++i) {
        rectangle(histImg, Point(i * bin_w, h), Point((i + 1) * bin_w, h - cvRound(hist.at<float>(i) * h / 255.0)),
                  Scalar(100, 123, 255), -1);
    }
    imshow("ֱ��ͼ", histImg);
}
