#pragma once
/*
 *  形态学滤波
 */
#include<iostream>
#include"opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;

void process();//处理腐蚀膨胀的函数
void on_TrackbarNumChange(int, void *);//回调函数
void on_ElementSizeChange(int, void *);
void Morph_ErodeAndDilate();

static void on_OpenClose(int, void *);
static void on_ErodeDilate(int, void *);
static void on_TopBlackHat(int, void *);
void Morph_Demo();
