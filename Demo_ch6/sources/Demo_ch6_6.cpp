#include "../header/Demo_ch6_6.h"

Mat g_srcImage,g_dstImage,g_tmpImage;

void PYR_Demo(){
    g_srcImage = imread("F:\\腾讯\\图\\67814952_p0_master1200.jpg");
    if(g_srcImage.empty()){
        cout<<"读取图片错误"<<endl;
        return;
    }
    namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
    imshow(WINDOW_NAME, g_srcImage);

    g_tmpImage = g_srcImage;
    g_dstImage = g_tmpImage;
    int key = 0;

    while (1){
        key = waitKey(0);
        switch (key){
            case 27:
                return;
                break;
            case 'q':
                return;
                break;
            case 'a':
                pyrUp(g_tmpImage,g_dstImage,Size(g_tmpImage.cols*2,g_tmpImage.rows*2));
                cout << "A键被按下，开始进行基于pyrUp函数的图片放大" << endl;
                break;
            case 'w':
                resize(g_tmpImage, g_dstImage, Size(g_tmpImage.cols * 2, g_tmpImage.rows * 2));
                cout << "W键被按下，开始进行基于resize函数的图片放大" << endl;
                break;
            case '1':
                resize(g_tmpImage, g_dstImage, Size(g_tmpImage.cols * 2, g_tmpImage.rows * 2));
                cout << "1键被按下，开始进行基于resize函数的图片放大" << endl;
                break;
            case '3':
                pyrUp(g_tmpImage,g_dstImage,Size(g_tmpImage.cols*2,g_tmpImage.rows*2));
                cout << "3键被按下，开始进行基于pyrUp函数的图片放大" << endl;
                break;
            case 'd':
                pyrDown(g_tmpImage,g_dstImage,Size(g_tmpImage.cols/2,g_tmpImage.rows/2));
                cout << "D键被按下，开始进行基于pyrDown函数的图片缩小" << endl;
                break;
            case 's':
                resize(g_tmpImage, g_dstImage, Size(g_tmpImage.cols / 2, g_tmpImage.rows / 2));
                cout << "S键被按下，开始进行基于resize函数的图片缩小" << endl;
                break;
            case '2':
                resize(g_tmpImage, g_dstImage, Size(g_tmpImage.cols / 2, g_tmpImage.rows / 2)
                        ,(0,0),(0,0),2);
                cout << "2键被按下，开始进行基于resize函数的图片缩小" << endl;
                break;
            case '4':
                pyrDown(g_tmpImage,g_dstImage,Size(g_tmpImage.cols/2,g_tmpImage.rows/2));
                cout << "4键被按下，开始进行基于pyrDown函数的图片缩小" << endl;
                break;
        }
        imshow(WINDOW_NAME,g_dstImage);
        g_tmpImage = g_dstImage;
    }
}
