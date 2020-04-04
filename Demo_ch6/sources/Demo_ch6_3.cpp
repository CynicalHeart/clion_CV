#include "../header/Demo_ch6_3.h"

//声明全局变量
Mat  g_srcImage, g_dstImage;
int g_nTrackbarNumer = 0;//0表腐蚀，1表示膨胀
int g_nStructElementSize = 3;//内核矩阵尺寸

int g_nElementShape = MORPH_RECT;
int g_nMaxIterationNum = 10;
int g_nOpenCloseNum = 0;
int g_nErodeDilateNum = 0;
int g_nTopBlackNum = 0;


void Morph_ErodeAndDilate(){
    g_srcImage = imread("F:\\腾讯\\图\\chouyou.jpg");
    namedWindow("原始图");
    imshow("原始图",g_srcImage);
    namedWindow("【效果图】");
    Mat element = getStructuringElement(MORPH_RECT,Size(2*g_nStructElementSize+1,2*g_nStructElementSize+1),Point(g_nStructElementSize,g_nStructElementSize));
    erode(g_srcImage, g_dstImage, element);
    imshow("【效果图】", g_dstImage);

    createTrackbar("腐蚀/膨胀","【效果图】",&g_nTrackbarNumer,1,on_TrackbarNumChange);
    createTrackbar("内核尺寸","【效果图 ",&g_nStructElementSize,21,on_ElementSizeChange);
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
    imshow("【效果图】", g_dstImage);
}

void on_TrackbarNumChange(int, void *) {
    process();
}

void on_ElementSizeChange(int, void *) {
    process();
}

void Morph_Demo(){
    g_srcImage = imread("F:\\腾讯\\图\\chouyou.jpg");
    namedWindow("【原始图】");
    imshow("【原始图】",g_srcImage);

    namedWindow("【开运算/闭运算】",1);
    namedWindow("【腐蚀/膨胀】",1);
    namedWindow("【顶帽/黑帽】", 1);
    g_nOpenCloseNum = 9;
    g_nErodeDilateNum = 9;
    g_nTopBlackNum = 2;

    createTrackbar("迭代值","【开运算/闭运算】",&g_nOpenCloseNum,g_nMaxIterationNum*2+1,on_OpenClose);
    createTrackbar("迭代值","【腐蚀/膨胀】",&g_nErodeDilateNum,g_nMaxIterationNum*2+1,on_ErodeDilate);
    createTrackbar("迭代值","【顶帽/黑帽】",&g_nTopBlackNum,g_nMaxIterationNum*2+1,on_TopBlackHat);

    while(1){
        int c;
        //执行回调
        on_OpenClose(g_nOpenCloseNum,0);
        on_ErodeDilate(g_nErodeDilateNum,0);
        on_TopBlackHat(g_nTopBlackNum,0);
        c=waitKey(0);
        if((char)c == 'q'||(char)c == 27) break;
        if((char)c == 49){
            g_nElementShape = MORPH_ELLIPSE;//1 椭圆
        } else if((char)c == 50){
            g_nElementShape = MORPH_RECT; // 2 矩形
        } else if((char)c == 51){
            g_nElementShape = MORPH_CROSS; // 3 交叉
        } else if((char)c ==' '){
            g_nElementShape = (g_nElementShape+1)%3;
        }
    }
}
void on_OpenClose(int, void *){
    int offset = g_nOpenCloseNum - g_nMaxIterationNum;//偏移量
    int Absolute_offset = offset>0?offset : -offset;
    Mat element = getStructuringElement(g_nElementShape,Size(Absolute_offset*2+1,Absolute_offset*2+1)
    ,Point(Absolute_offset,Absolute_offset));
    if(offset<0){
        morphologyEx(g_srcImage,g_dstImage,MORPH_OPEN,element);
    }else{
        morphologyEx(g_srcImage,g_dstImage,MORPH_CLOSE,element);
    }
    imshow("【开运算/闭运算】",g_dstImage);
}
void on_ErodeDilate(int, void *){
    int offset = g_nErodeDilateNum - g_nMaxIterationNum;//偏移量
    int Absolute_offset = offset>0?offset : -offset;
    Mat element = getStructuringElement(g_nElementShape,Size(Absolute_offset*2+1,Absolute_offset*2+1)
            ,Point(Absolute_offset,Absolute_offset));
    if(offset<0){
        erode(g_srcImage,g_dstImage,element);
    }else{
        dilate(g_srcImage,g_dstImage,element);
    }
    imshow("【腐蚀/膨胀】",g_dstImage);
}
void on_TopBlackHat(int, void *){
    int offset = g_nTopBlackNum - g_nMaxIterationNum;//偏移量
    int Absolute_offset = offset>0?offset : -offset;
    Mat element = getStructuringElement(g_nElementShape,Size(Absolute_offset*2+1,Absolute_offset*2+1)
            ,Point(Absolute_offset,Absolute_offset));
    if(offset<0){
        morphologyEx(g_srcImage,g_dstImage,MORPH_TOPHAT,element);
    }else{
        morphologyEx(g_srcImage,g_dstImage,MORPH_BLACKHAT,element);
    }
    imshow("【顶帽/黑帽】",g_dstImage);
}