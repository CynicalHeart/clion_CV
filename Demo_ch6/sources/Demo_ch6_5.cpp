#include "../header/Demo_ch6_5.h"

Mat g_srcImage,g_dstImage,g_grayImage,g_maskImage;
int g_nFillMode = 1;//漫水填充模式
int g_nLowDifference = 20,g_nUpDifference=20;//负差正差最大值
int g_nConnectivity = 4;//低8位连通值
int g_bIsColor =true;
int g_bUseMask = false;
int g_nNewMaskVal = 255;

static void  onMouse(int event , int x,int y,void*){
    if(event!=EVENT_LBUTTONDOWN){
        return;
    }
    //参数准备
    Point seed = Point(x,y);
    int LowDifference = g_nFillMode ==0?0:g_nLowDifference;
    int UpDifference = g_nFillMode ==0?0:g_nUpDifference;
    int flags = g_nConnectivity+(g_nNewMaskVal<<8)+(g_nFillMode==1?FLOODFILL_FIXED_RANGE:0);
    //随机生成bgr
    int b = (unsigned)theRNG()&255;
    int g = (unsigned)theRNG()&255;
    int r = (unsigned)theRNG()&255;
    //重绘区域最小边界
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
    imshow("效果图", dst);
    cout<<area<<"个像素被重绘"<<endl;
}

void Flood_Demo(){
    g_srcImage = imread("F:\\腾讯\\图\\刃.jpg");
    g_srcImage.copyTo(g_dstImage);
    cvtColor(g_srcImage,g_grayImage,COLOR_BGR2GRAY);
    g_maskImage.create(g_srcImage.rows+2,g_srcImage.cols+2,CV_8UC1);
    namedWindow("效果图",WINDOW_AUTOSIZE);
    createTrackbar("负差最大值","效果图",&g_nLowDifference,255,0);
    createTrackbar("正差最大值","效果图",&g_nLowDifference,255,0);
    //鼠标回调
    setMouseCallback("效果图", reinterpret_cast<MouseCallback>(onMouse), 0);
    while(1){
        imshow("效果图", g_bIsColor ? g_dstImage : g_grayImage);
        int c = waitKey(0);
        if((c&255) == 27){
            cout<<"程序退出"<<endl;
            break;
        }
        switch((char)c){
            case '1':
                if(g_bIsColor){
                    cout<<"键盘1被按下，切换彩色/灰色模式，当前操作为彩色转灰色"<<endl;
                    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
                    g_maskImage = Scalar::all(0);
                    g_bIsColor = false;
                }else{
                    cout<<"键盘1被按下，切换彩色/灰色模式，当前操作为灰色转彩色"<<endl;
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
                cout<<"按键3被按下，恢复原始图像"<<endl;
                g_srcImage.copyTo(g_dstImage);
                cvtColor(g_dstImage, g_grayImage, COLOR_BGR2GRAY);
                g_maskImage = Scalar::all(0);
                break;
            case '4':
                cout<<"按键4被按下,使用空范围的漫水填充"<<endl;
                g_nFillMode = 0;
                break;
            case '5':
                cout<<"按键5被按下,使用渐变、固定范围的漫水填充"<<endl;
                g_nFillMode = 1;
                break;
            case '6':
                cout<<"按键6被按下,使用渐变、浮动范围的漫水填充"<<endl;
                g_nFillMode = 2;
                break;
            case '7':
                cout<<"按键7被按下,操作标志符的低八位使用4位的连接诶模式"<<endl;
                g_nConnectivity = 4;
                break;
            case '8':
                cout<<"按键8被按下,操作符号的低八位使用8位的连接模式"<<endl;
                g_nConnectivity = 8;
                break;
        }
    }

}

