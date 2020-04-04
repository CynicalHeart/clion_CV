#include "../header/Demo_ch7_2.h"

Mat g_srcImage,g_dstImage,g_midImage;
vector<Vec4i> g_lines;//�߶�ʸ������

int g_nthreshold = 100;


void Hough_Demo() {
    g_srcImage = imread("F:\\��Ѷ\\ͼ\\77564597_p0.png");
    imshow("ԭʼͼ", g_srcImage);
    namedWindow("Ч��ͼ", 1);
    createTrackbar("ֵ","Ч��ͼ",&g_nthreshold,200,on_HoughLines);
    Canny(g_srcImage,g_midImage,80,200,
            3);//��Ե���
    cvtColor(g_midImage,g_dstImage,COLOR_GRAY2BGR);//�Ҷ�

    on_HoughLines(g_nthreshold, 0);
    //HoughLinesP(g_midImage, g_lines, 1, CV_PI / 180, 80, 50, 10);

    imshow("Ч��ͼ", g_dstImage);
    waitKey(0);
}

void on_HoughLines(int, void *) {
    Mat dstImage = g_dstImage.clone();
    Mat midImage = g_midImage.clone();
    vector<Vec4i> mylines;
    HoughLinesP(midImage, mylines, 1, CV_PI / 180, g_nthreshold + 1, 100, 10);

    for (size_t i = 0; i <mylines.size() ; ++i) {
        Vec4i l = mylines[i];
        line(dstImage,Point(l[0],l[1]),Point(l[2],l[3]),Scalar(23,180,55),1,LINE_AA);
    }
    imshow("Ч��ͼ", dstImage);
}
