#pragma once

#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

#define WINDOW_NAME1 "ԭʼͼ����"
#define WINDOW_NAME2 "Ч��ͼ����"
/**
 * ʹ�ö���ν�������Χ
 *  �ⲿ���α߽� - boundingRect()
 *  Ѱ����С��Χ���� - minAreaRect()
 *  Ѱ����СԲ�ΰ�Χ - minEnclosingCircle()
 *  ����Բ��϶�ά�㼯 - fitEllipse()
 *  �ƽ���������� - approxPolyDP()
 */

//������Χ�����ľ��α߽�
void minAreaRectTest();
//��Χ����Բ�α߽�
void minEnclosingCircle();

void on_ContoursChange(int,void*);
void Enclosing_Demo();



