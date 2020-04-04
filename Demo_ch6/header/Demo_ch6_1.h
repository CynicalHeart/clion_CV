#pragma once
/*
 *  线型滤波和非线性滤波
 */
#include<iostream>
#include"opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;

//三个线性滤波回调函数
void Blur_Demo();
static void on_BoxFilter(int, void*);
static void on_MeanBlur(int, void*);
static void on_GaussianBlur(int, void*);

//两个非线性滤波回调函数
static void on_MedianBlur(int, void *);
static void on_BilateralFilter(int, void *);





