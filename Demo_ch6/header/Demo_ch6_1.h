#pragma once
/*
 *  �����˲��ͷ������˲�
 */
#include<iostream>
#include"opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;

//���������˲��ص�����
void Blur_Demo();
static void on_BoxFilter(int, void*);
static void on_MeanBlur(int, void*);
static void on_GaussianBlur(int, void*);

//�����������˲��ص�����
static void on_MedianBlur(int, void *);
static void on_BilateralFilter(int, void *);





