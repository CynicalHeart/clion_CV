#include "../header/Demo_ch6_3.h"

//����ȫ�ֱ���
Mat  g_srcImage, g_dstImage;
int g_nTrackbarNumer = 0;//0��ʴ��1��ʾ����
int g_nStructElementSize = 3;//�ں˾���ߴ�

int g_nElementShape = MORPH_RECT;
int g_nMaxIterationNum = 10;
int g_nOpenCloseNum = 0;
int g_nErodeDilateNum = 0;
int g_nTopBlackNum = 0;


void Morph_ErodeAndDilate(){
    g_srcImage = imread("F:\\��Ѷ\\ͼ\\chouyou.jpg");
    namedWindow("ԭʼͼ");
    imshow("ԭʼͼ",g_srcImage);
    namedWindow("��Ч��ͼ��");
    Mat element = getStructuringElement(MORPH_RECT,Size(2*g_nStructElementSize+1,2*g_nStructElementSize+1),Point(g_nStructElementSize,g_nStructElementSize));
    erode(g_srcImage, g_dstImage, element);
    imshow("��Ч��ͼ��", g_dstImage);

    createTrackbar("��ʴ/����","��Ч��ͼ��",&g_nTrackbarNumer,1,on_TrackbarNumChange);
    createTrackbar("�ں˳ߴ�","��Ч��ͼ ",&g_nStructElementSize,21,on_ElementSizeChange);
    while(char(waitKey(1))!='q'){}
}
void process(){
    Mat element = getStructuringElement(MORPH_RECT,Size(2*g_nStructElementSize+1,2*g_nStructElementSize+1)
            ,Point(g_nStructElementSize,g_nStructElementSize));
    if(g_nTrackbarNumer == 0){
        erode(g_srcImage,g_dstImage,element);
    }else{
        dilate(g_srcImage,g_dstImage,element);
    }
    imshow("��Ч��ͼ��", g_dstImage);
}

void on_TrackbarNumChange(int, void *) {
    process();
}

void on_ElementSizeChange(int, void *) {
    process();
}

void Morph_Demo(){
    g_srcImage = imread("F:\\��Ѷ\\ͼ\\chouyou.jpg");
    namedWindow("��ԭʼͼ��");
    imshow("��ԭʼͼ��",g_srcImage);

    namedWindow("��������/�����㡿",1);
    namedWindow("����ʴ/���͡�",1);
    namedWindow("����ñ/��ñ��", 1);
    g_nOpenCloseNum = 9;
    g_nErodeDilateNum = 9;
    g_nTopBlackNum = 2;

    createTrackbar("����ֵ","��������/�����㡿",&g_nOpenCloseNum,g_nMaxIterationNum*2+1,on_OpenClose);
    createTrackbar("����ֵ","����ʴ/���͡�",&g_nErodeDilateNum,g_nMaxIterationNum*2+1,on_ErodeDilate);
    createTrackbar("����ֵ","����ñ/��ñ��",&g_nTopBlackNum,g_nMaxIterationNum*2+1,on_TopBlackHat);

    while(1){
        int c;
        //ִ�лص�
        on_OpenClose(g_nOpenCloseNum,0);
        on_ErodeDilate(g_nErodeDilateNum,0);
        on_TopBlackHat(g_nTopBlackNum,0);
        c=waitKey(0);
        if((char)c == 'q'||(char)c == 27) break;
        if((char)c == 49){
            g_nElementShape = MORPH_ELLIPSE;//1 ��Բ
        } else if((char)c == 50){
            g_nElementShape = MORPH_RECT; // 2 ����
        } else if((char)c == 51){
            g_nElementShape = MORPH_CROSS; // 3 ����
        } else if((char)c ==' '){
            g_nElementShape = (g_nElementShape+1)%3;
        }
    }
}
void on_OpenClose(int, void *){
    int offset = g_nOpenCloseNum - g_nMaxIterationNum;//ƫ����
    int Absolute_offset = offset>0?offset : -offset;
    Mat element = getStructuringElement(g_nElementShape,Size(Absolute_offset*2+1,Absolute_offset*2+1)
    ,Point(Absolute_offset,Absolute_offset));
    if(offset<0){
        morphologyEx(g_srcImage,g_dstImage,MORPH_OPEN,element);
    }else{
        morphologyEx(g_srcImage,g_dstImage,MORPH_CLOSE,element);
    }
    imshow("��������/�����㡿",g_dstImage);
}
void on_ErodeDilate(int, void *){
    int offset = g_nErodeDilateNum - g_nMaxIterationNum;//ƫ����
    int Absolute_offset = offset>0?offset : -offset;
    Mat element = getStructuringElement(g_nElementShape,Size(Absolute_offset*2+1,Absolute_offset*2+1)
            ,Point(Absolute_offset,Absolute_offset));
    if(offset<0){
        erode(g_srcImage,g_dstImage,element);
    }else{
        dilate(g_srcImage,g_dstImage,element);
    }
    imshow("����ʴ/���͡�",g_dstImage);
}
void on_TopBlackHat(int, void *){
    int offset = g_nTopBlackNum - g_nMaxIterationNum;//ƫ����
    int Absolute_offset = offset>0?offset : -offset;
    Mat element = getStructuringElement(g_nElementShape,Size(Absolute_offset*2+1,Absolute_offset*2+1)
            ,Point(Absolute_offset,Absolute_offset));
    if(offset<0){
        morphologyEx(g_srcImage,g_dstImage,MORPH_TOPHAT,element);
    }else{
        morphologyEx(g_srcImage,g_dstImage,MORPH_BLACKHAT,element);
    }
    imshow("����ñ/��ñ��",g_dstImage);
}