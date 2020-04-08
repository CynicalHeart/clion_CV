#include "../header/Demo_ch8_3.h"

Mat g_srcImage, g_grayImage;
int g_nThresh = 50;
int g_nMaxThresh = 255;
RNG g_rng(12345);

void Enclosing_Demo(){
    g_srcImage = imread("F:\\��Ѷ\\ͼ\\77564597_p0.png",1);
    if (!g_srcImage.data) {
        cout<<"��ȡͼƬʧ��"<<endl;
        return;
    }
    //�ҶȻ�����
    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
    blur(g_grayImage, g_grayImage, Size(3, 3));

    namedWindow(WINDOW_NAME1, 1);
    imshow(WINDOW_NAME1, g_srcImage);

    createTrackbar("��ֵ",WINDOW_NAME1,&g_nThresh,g_nMaxThresh,on_ContoursChange);
    on_ContoursChange(0, 0);
    waitKey(0);
}

void on_ContoursChange(int,void*){
    Mat threshold_output;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    //ʹ����ֵ����Ե
    threshold(g_grayImage, threshold_output, g_nThresh, 255, THRESH_BINARY);
    //�ҳ�����
    findContours(threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    //����αƽ�����+��ȡ���κ�Բ�α߽�
    vector<vector<Point>> contours_poly(contours.size());
    vector<Rect> boundRect(contours.size());
    vector<Point2f> center(contours.size());
    vector<float> radius(contours.size());

    for (unsigned int i = 0; i <contours.size() ; ++i) {
        approxPolyDP(Mat(contours[i]),contours_poly[i],3, true);
        boundRect[i] = boundingRect(Mat(contours_poly[i]));
        minEnclosingCircle(contours_poly[i], center[i], radius[i]);
    }
    Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
    //��������� ���� Բ��
    for (unsigned j = 0; j <contours.size() ; ++j) {
        Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
        drawContours(drawing, contours_poly, j, color, 1, 8, vector<Vec4i>(), 0, Point(0, 0));
        rectangle(drawing, boundRect[j].tl(), boundRect[j].br(), color, 2, 8, 0);
        circle(drawing, center[j], (int) radius[j], color, 2, 8, 0);
    }
    namedWindow(WINDOW_NAME2, 1);
    imshow(WINDOW_NAME2, drawing);
}


void minAreaRectTest(){
    Mat image(600, 600, CV_8UC3);
    RNG &rng = theRNG();

    while(1){
        int count = rng.uniform(3, 103);
        vector<Point> points;
        //�����������
        for (int i = 0; i <count ; ++i) {
            Point point;
            point.x = rng.uniform(image.cols / 4, image.cols * 3 / 4);
            point.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);
            points.push_back(point);
        }
        //Ѱ����С�����Χ����
        RotatedRect box = minAreaRect(Mat(points));
        Point2f vertex[4];
        box.points(vertex);
        //���Ƴ���������ɫ
        image = Scalar::all(0);
        for (int j = 0; j <count ; ++j) {
            circle(image, points[j], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED,
                   LINE_AA);
        }
        //���Ƴ���С�������
        for (int k = 0; k <4 ; ++k) {
            line(image, vertex[k], vertex[(k + 1) % 4], Scalar(100, 200, 211), 2, LINE_AA);
        }
        imshow("���ΰ�Χʾ��", image);
        char key = (char)waitKey();
        if(key == 27||key=='q'||key=='Q'){
            break;
        }
    }
}

void minEnclosingCircle(){
    Mat image(600, 600, CV_8UC3);
    RNG &rng = theRNG();
    while(1) {
        int count = rng.uniform(3, 103);
        vector<Point> points;
        for (int i = 0; i < count; ++i) {
            Point point;
            point.x = rng.uniform(image.cols / 4, image.cols * 3 / 4);
            point.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);
            points.push_back(point);
        }
        //�Ը�����2D�㼯Ѱ����С����İ�ΧԲ
        Point2f center;
        float radius;
        minEnclosingCircle((Mat) points, center, radius);
        //���Ƴ������ɫ�ĵ�
        image = Scalar::all(0);
        for (int j = 0; j < count; ++j) {
            circle(image, points[j], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED,
                   LINE_AA);
        }
        circle(image, center, cvRound(radius), Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)),
               2, LINE_AA);

        imshow("Բ�ΰ�Χʾ��", image);
        char key = (char) waitKey();
        if (key == 27 || key == 'q' || key == 'Q') {
            break;
        }
    }
}

