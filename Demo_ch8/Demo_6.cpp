/**
 * ͼ���޲� - inpint
 */
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/photo/photo.hpp>
using namespace std;
using namespace cv;
#define WINDOW_NAME1 "ԭʼͼ"
#define WINDOW_NAME2 "�޲����Ч��ͼ"

Mat srcImage1, inpaintMask;
Point previousPoint(-1, -1);//ԭ���ĵ�����

static void on_Mouse(int event, int x, int y, int flags, void *){
    //������������Ϣ,���ɿ������ǰ�õ�����(-1,-1)
    //EVENT_LBUTTONUP �ſ����,EVENT_FLAG_LBUTTON �����ק
    if(event == EVENT_LBUTTONUP || !(flags&EVENT_FLAG_LBUTTON)) {
        previousPoint = Point(-1, -1);
    } else if(event == EVENT_LBUTTONUP){
        previousPoint = Point(x, y);
    } else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON)) {
        Point pt(x, y);
        if (previousPoint.x <0) {
            previousPoint = pt;
        }
        //������ͼ��ԭͼ����ɫ��
        line(inpaintMask, previousPoint, pt, Scalar::all(255), 5, 8,0);
        line(srcImage1, previousPoint, pt, Scalar::all(255), 5, 8, 0);
        previousPoint = pt;//������ǰ��
        imshow(WINDOW_NAME1, srcImage1);
    }
}

int main() {
    Mat srcImage = imread("F:\\��Ѷ\\ͼ\\��.jpg");
    srcImage1 = srcImage.clone();
    inpaintMask = Mat::zeros(srcImage1.size(),CV_8U);

    imshow(WINDOW_NAME1,srcImage1);

    setMouseCallback(WINDOW_NAME1, on_Mouse, 0);

    while (1) {
        char c = (char) waitKey();
        if (c == 27) {
            break;
        }
        if (c == '2') {
            inpaintMask = Scalar::all(0);
            srcImage.copyTo(srcImage1);
            imshow(WINDOW_NAME1, srcImage1);
        }
        if (c == '1' || c == ' ') {
            Mat inpaintedImage;
            inpaint(srcImage1, inpaintMask, inpaintedImage, 3, INPAINT_TELEA);
            imshow(WINDOW_NAME2, inpaintedImage);
        }
    }
    return 0;
}

