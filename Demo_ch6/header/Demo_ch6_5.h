#pragma once
/*
 *  漫水填充
 */
#include<iostream>
#include"opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;

static void onMouse(int event , int x,int y,void*);//鼠标回调函数
void Flood_Demo();//漫水填充案例

