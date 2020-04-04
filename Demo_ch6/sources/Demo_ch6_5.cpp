#include "../header/Demo_ch6_5.h"

Mat g_srcImage,g_dstImage,g_grayImage,g_maskImage;
int g_nFillMode = 1;//��ˮ���ģʽ
int g_nLowDifference = 20,g_nUpDifference=20;//�����������ֵ
int g_nConnectivity = 4;//��8λ��ֵͨ
int g_bIsColor =true;
int g_bUseMask = false;
int g_nNewMaskVal = 255;

static void  onMouse(int event , int x,int y,void*){
    if(event!=EVENT_LBUTTONDOWN){
        return;
    }
    //����׼��
    Point seed = Point(x,y);
    int LowDifference = g_nFillMode ==0?0:g_nLowDifference;
    int UpDifference = g_nFillMode ==0?0:g_nUpDifference;
    int flags = g_nConnectivity+(g_nNewMaskVal<<8)+(g_nFillMode==1?FLOODFILL_FIXED_RANGE:0);
    //�������bgr
    int b = (unsigned)theRNG()&255;
    int g = (unsigned)theRNG()&255;
    int r = (unsigned)theRNG()&255;
    //�ػ�������С�߽�
    Rect comp;
    Scalar newVal = g_bIsColor ? Scalar(b, g, r) : Scalar(r * 0.299, g * 0.587, b * 0.114);
    Mat dst = g_bIsColor?g_dstImage:g_grayImage;

    int area;
    if(g_bUseMask){
        threshold(g_maskImage,g_maskImage,1,128,THRESH_BINARY);
        area = floodFill(dst, g_maskImage, seed, newVal, &comp, Scalar(LowDifference, LowDifference, LowDifference),
                         Scalar(UpDifference, UpDifference, g_nUpDifference), flags);
        imshow("mask",g_maskImage);
    } else{
        area = floodFill(dst, seed, newVal, &comp, Scalar(LowDifference, LowDifference, LowDifference),
                         Scalar(UpDifference, UpDifference, g_nUpDifference), flags);
    }
    imshow("Ч��ͼ", dst);
    cout<<area<<"�����ر��ػ�"<<endl;
}

void Flood_Demo(){
    g_srcImage = imread("F:\\��Ѷ\\ͼ\\��.jpg");
    g_srcImage.copyTo(g_dstImage);
    cvtColor(g_srcImage,g_grayImage,COLOR_BGR2GRAY);
    g_maskImage.create(g_srcImage.rows+2,g_srcImage.cols+2,CV_8UC1);
    namedWindow("Ч��ͼ",WINDOW_AUTOSIZE);
    createTrackbar("�������ֵ","Ч��ͼ",&g_nLowDifference,255,0);
    createTrackbar("�������ֵ","Ч��ͼ",&g_nLowDifference,255,0);
    //���ص�
    setMouseCallback("Ч��ͼ", reinterpret_cast<MouseCallback>(onMouse), 0);
    while(1){
        imshow("Ч��ͼ", g_bIsColor ? g_dstImage : g_grayImage);
        int c = waitKey(0);
        if((c&255) == 27){
            cout<<"�����˳�"<<endl;
            break;
        }
        switch((char)c){
            case '1':
                if(g_bIsColor){
                    cout<<"����1�����£��л���ɫ/��ɫģʽ����ǰ����Ϊ��ɫת��ɫ"<<endl;
                    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
                    g_maskImage = Scalar::all(0);
                    g_bIsColor = false;
                }else{
                    cout<<"����1�����£��л���ɫ/��ɫģʽ����ǰ����Ϊ��ɫת��ɫ"<<endl;
                    g_srcImage.copyTo(g_grayImage);
                    g_maskImage = Scalar::all(0);
                    g_bIsColor = true;
                }
                break;
            case '2':
                if(g_bUseMask){
                    destroyWindow("mask");
                    g_bUseMask = false;
                } else{
                    namedWindow("mask");
                    g_maskImage = Scalar::all(0);
                    imshow("mask",g_maskImage);
                    g_bUseMask = true;
                }
                break;
            case '3':
                cout<<"����3�����£��ָ�ԭʼͼ��"<<endl;
                g_srcImage.copyTo(g_dstImage);
                cvtColor(g_dstImage, g_grayImage, COLOR_BGR2GRAY);
                g_maskImage = Scalar::all(0);
                break;
            case '4':
                cout<<"����4������,ʹ�ÿշ�Χ����ˮ���"<<endl;
                g_nFillMode = 0;
                break;
            case '5':
                cout<<"����5������,ʹ�ý��䡢�̶���Χ����ˮ���"<<endl;
                g_nFillMode = 1;
                break;
            case '6':
                cout<<"����6������,ʹ�ý��䡢������Χ����ˮ���"<<endl;
                g_nFillMode = 2;
                break;
            case '7':
                cout<<"����7������,������־���ĵͰ�λʹ��4λ��������ģʽ"<<endl;
                g_nConnectivity = 4;
                break;
            case '8':
                cout<<"����8������,�������ŵĵͰ�λʹ��8λ������ģʽ"<<endl;
                g_nConnectivity = 8;
                break;
        }
    }

}

