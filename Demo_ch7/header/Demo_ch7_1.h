#pragma once
/*
 *  ±ßÔµ¼ì²â
 */
#include<iostream>
#include"opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;

static void on_Canny(int,void*);
static void on_Sobel(int, void *);
void Scharr();

void Canny_Demo();

