#pragma once

#include <stdio.h>
//#include <tchar.h>
#include <map>
#include "RGB2HSV.h"
// TODO: 在此处引用程序需要的其他头文件
struct MaskResults 
{
	double Mask1;
	double Mask2;
	double Mask3;
	double Mask4;
	double Mask5;
};

struct Neighborhood 
{
	double Area1;
	double Area2;
	double Area3;
	double Area4;
};

struct FuzzyRules 
{
	int Input1;
	int Input2;
	int Input3;
	int Output;
};
