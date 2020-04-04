#include "../header/Demo_ch7_1.h"

Mat g_srcImage,g_grayImage,g_dstImage;

Mat g_cannyDetectedEdges;
int g_cannyLowThreshold = 1;

Mat g_sobelGradient_X,g_sobelGradient_Y;
Mat g_sobelAbsGradient_X,g_sobelAbsGradient_Y;
int g_sobelKernelSize = 1;

Mat g_scharrGradient_X,g_scharrGradient_Y;
Mat g_scharrAbsGradient_X,g_scharrAbsGradient_Y;

void on_Canny(int, void *){
    //�Ƚ���
    blur(g_grayImage, g_cannyDetectedEdges, Size(3, 3));
    //��������
    Canny(g_cannyDetectedEdges,g_cannyDetectedEdges,g_cannyLowThreshold,g_cannyLowThreshold*3,3);
    //Ŀ��ͼ����
    g_dstImage = Scalar::all(0);
    //��Canny��������ı�Եͼg_cannyDetectedEdges��Ϊ���룬����Դͼ������Ŀ��ͼ
    g_srcImage.copyTo(g_dstImage, g_cannyDetectedEdges);

    imshow("Canny��Ե���", g_dstImage);
}

void on_Sobel(int, void *){
    //X�����ݶ�
    Sobel(g_srcImage,g_sobelGradient_X,CV_16S,1,0,2*g_sobelKernelSize+1,1,1,BORDER_DEFAULT);
    convertScaleAbs(g_sobelGradient_X,g_sobelAbsGradient_X);//�������ֵ�������תΪ8λ
    //Y�����ݶ�
    Sobel(g_srcImage,g_sobelGradient_Y,CV_16S,0,1,2*g_sobelKernelSize+1,1,1,BORDER_DEFAULT);
    convertScaleAbs(g_sobelGradient_Y, g_sobelAbsGradient_Y);

    //�ϲ��ݶ�
    addWeighted(g_sobelAbsGradient_X,0.5,g_sobelAbsGradient_Y,0.5,0,g_dstImage);

    imshow("Sobel��Ե���",g_dstImage);
}

void Scharr(){
    Scharr(g_srcImage,g_scharrGradient_X,CV_16S,1,0,1,0,BORDER_DEFAULT);
    convertScaleAbs(g_scharrGradient_X, g_scharrAbsGradient_X);

    Scharr(g_srcImage,g_scharrGradient_Y,CV_16S,0,1,1,0,BORDER_DEFAULT);
    convertScaleAbs(g_scharrGradient_Y, g_scharrAbsGradient_Y);

    //�ϲ��ݶ�
    addWeighted(g_scharrAbsGradient_X, 0.5, g_scharrAbsGradient_Y, 0.5, 0, g_dstImage);

    imshow("Scharr�˲���",g_dstImage);
}

void Canny_Demo(){
    g_srcImage = imread("F:\\��Ѷ\\ͼ\\chouyou.jpg");
    /*if(g_srcImage.empty()){
        cout<<"��Ƭ��ȡʧ��"<<endl;
        return;
    }*/
    namedWindow("��ԭʼͼ��");
    imshow("��ԭʼͼ��",g_srcImage);

    g_dstImage.create(g_srcImage.size(),g_srcImage.type());
    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);

    namedWindow("Canny��Ե���", WINDOW_AUTOSIZE);
    namedWindow("Sobel��Ե���", WINDOW_AUTOSIZE);
    namedWindow("Scharr�˲���", WINDOW_AUTOSIZE);

    createTrackbar("����ֵ","Canny��Ե���",&g_cannyLowThreshold,120,on_Canny);
    createTrackbar("����ֵ","Sobel��Ե���",&g_sobelKernelSize,3,on_Sobel);
    on_Canny(0, 0);
    on_Sobel(0, 0);

    Scharr();

    while ((char(waitKey(1))!='q')){}
}


