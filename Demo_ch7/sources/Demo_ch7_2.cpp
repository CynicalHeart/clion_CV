#include "../header/Demo_ch7_2.h"

Mat g_srcImage,g_dstImage,g_midImage;
vector<Vec4i> g_lines;//线段矢量集合

int g_nthreshold = 100;


void Hough_Demo() {
    g_srcImage = imread("F:\\腾讯\\图\\77564597_p0.png");
    imshow("原始图", g_srcImage);
    namedWindow("效果图", 1);
    createTrackbar("值","效果图",&g_nthreshold,200,on_HoughLines);
    Canny(g_srcImage,g_midImage,80,200,
            3);//边缘检测
    cvtColor(g_midImage,g_dstImage,COLOR_GRAY2BGR);//灰度

    on_HoughLines(g_nthreshold, 0);
    //HoughLinesP(g_midImage, g_lines, 1, CV_PI / 180, 80, 50, 10);

    imshow("效果图", g_dstImage);
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
    imshow("效果图", dstImage);
}
