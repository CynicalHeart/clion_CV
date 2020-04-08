#pragma once

#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

#define WINDOW_NAME1 "原始图窗口"
#define WINDOW_NAME2 "效果图窗口"
/**
 * 使用多边形将轮廓包围
 *  外部矩形边界 - boundingRect()
 *  寻找最小包围矩形 - minAreaRect()
 *  寻找最小圆形包围 - minEnclosingCircle()
 *  用椭圆拟合二维点集 - fitEllipse()
 *  逼近多边形曲线 - approxPolyDP()
 */

//创建包围轮廓的矩形边界
void minAreaRectTest();
//包围轮廓圆形边界
void minEnclosingCircle();

void on_ContoursChange(int,void*);
void Enclosing_Demo();



