#pragma once
/**
 * 直方图的计算与绘制
 */
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

//H-S直方图：计算彩色图像的色调、饱和度的二维直方图
void drawHS02();

//一维直方图
void drawHS01();

//RGB三色直方图
void drawHSRHB();