#pragma once
/*
 *  重映射与仿射变换
 */
#include<iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;
#define WINDOW_NAME "[程序窗口]"
#define WINDOW_NAME1 "原始图窗口"
#define WINDOW_NAME2 "经过Warp后图像"
#define WINDOW_NAME3 "经过Warp和Rotate后的图像"


int update_map(int key);
static void ShowHelpText();
static void ShowHelpText_2();

void CVMap_Demo();//重映射

void Affine_Demo();//仿射变换