#pragma once
/*
 *  ��ӳ�������任
 */
#include<iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;
#define WINDOW_NAME "[���򴰿�]"
#define WINDOW_NAME1 "ԭʼͼ����"
#define WINDOW_NAME2 "����Warp��ͼ��"
#define WINDOW_NAME3 "����Warp��Rotate���ͼ��"


int update_map(int key);
static void ShowHelpText();
static void ShowHelpText_2();

void CVMap_Demo();//��ӳ��

void Affine_Demo();//����任