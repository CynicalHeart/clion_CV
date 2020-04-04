#include"../header/Demo_ch6_1.h"

Mat g_srcImage, g_dstImage1, g_dstImage2, g_dstImage3,g_dstImage4,g_dstImage5;
int g_nBoxFilterValue = 6;//�����˲�����
int g_nMeanBlurValue = 10;//��ֵ�˲�����
int g_nGaussianBlurValue = 6;//��˹�˲�����
int g_nMedianBlurValue = 10;//��ֵ�˲�����
int g_nBilateralFilterValue = 10;//˫���˲�����

void on_BoxFilter(int, void*)
{
    boxFilter(g_srcImage, g_dstImage1, -1, Size(g_nBoxFilterValue + 1, g_nBoxFilterValue + 1));
    imshow("�������˲���", g_dstImage1);
}

void on_MeanBlur(int, void*)
{
    blur(g_srcImage, g_dstImage2, Size(g_nMeanBlurValue + 1, g_nMeanBlurValue + 1), Point(-1, -1));
    imshow("����ֵ�˲���", g_dstImage2);
}

void on_GaussianBlur(int, void*)
{
    GaussianBlur(g_srcImage, g_dstImage3, Size(g_nGaussianBlurValue * 2 + 1, g_nGaussianBlurValue * 2 + 1), 0, 0);
    imshow("����˹�˲���", g_dstImage3);
}
void on_MedianBlur(int, void *)
{
    medianBlur(g_srcImage,g_dstImage4,g_nMedianBlurValue*2+1);
    imshow("����ֵ�˲���", g_dstImage4);
}
void on_BilateralFilter(int, void *)
{
    bilateralFilter(g_srcImage,g_dstImage5,g_nBilateralFilterValue,g_nBilateralFilterValue*2,g_nBilateralFilterValue/2);
    imshow("��˫���˲���",g_dstImage5);
}

void Blur_Demo() {
    g_srcImage = imread("F:\\��Ѷ\\ͼ\\67814952_p0_master1200.jpg", 1);
    if(g_srcImage.empty()){
        cout<<"��ȡͼƬ����"<<endl;
    }

    g_dstImage1 = g_srcImage.clone();
    g_dstImage2 = g_srcImage.clone();
    g_dstImage3 = g_srcImage.clone();
    g_dstImage4 = g_srcImage.clone();
    g_dstImage5 = g_srcImage.clone();

    namedWindow("����ʾԭͼ��", 1);
    imshow("����ʾԭͼ��", g_srcImage);

    /* ====================== �����˲� ======================= */
    namedWindow("�������˲���", 1);
    createTrackbar("�ں�ֵ", "�������˲���", &g_nBoxFilterValue, 50, on_BoxFilter);
    on_BoxFilter(g_nBoxFilterValue, 0);
    /* ====================== ��ֵ�˲� ======================= */
    namedWindow("����ֵ�˲���", 1);
    createTrackbar("�ں�ֵ", "����ֵ�˲���", &g_nMeanBlurValue, 50, on_MeanBlur);
    on_MeanBlur(g_nMeanBlurValue, 0);
    /* ====================== ��˹�˲� ======================= */
    namedWindow("����˹�˲���", 1);
    createTrackbar("�ں�ֵ", "����˹�˲���", &g_nGaussianBlurValue, 50, on_GaussianBlur);
    on_GaussianBlur(g_nGaussianBlurValue, 0);
    /* ====================== ��ֵ�˲� ======================= */
    namedWindow("����ֵ�˲���", 1);
    createTrackbar("�ں�ֵ", "����ֵ�˲���", &g_nMedianBlurValue, 50, on_MedianBlur);
    on_MedianBlur(g_nMedianBlurValue, 0);
    /* ====================== ˫���˲� ======================= */
    namedWindow("��˫���˲���", 1);
    createTrackbar("�ں�ֵ", "��˫���˲���", &g_nBilateralFilterValue, 50, on_BilateralFilter);
    on_BilateralFilter(g_nBilateralFilterValue, 0);

    cout << "�����������۲�ͼ��Ч��" << endl << "��q�˳�����" << endl;

    while (char(waitKey(1)) != 'q') {}
}


