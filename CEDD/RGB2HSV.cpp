
#include "RGB2HSV.h"

#include <math.h>

RGB2HSV::RGB2HSV()
{

}

RGB2HSV::~RGB2HSV()
{

}

void RGB2HSV::ApplyFilter(int red, int green, int blue,  int* Result)
{
	int HSV_H = 0;
	int HSV_S = 0;
	int HSV_V = 0;

	double MaxHSV = (max(red, max(green, blue, int_less), int_less));
	double MinHSV = (min(red, min(green, blue, int_less), int_less));

	//V
	HSV_V = (int) (MaxHSV);

	//S
	//HSV_S = 0;
	if (MaxHSV != 0)
		HSV_S = (int) (255 - 255 * (MinHSV / MaxHSV));

	//H
	if (MaxHSV != MinHSV) 
	{

		int IntegerMaxHSV = (int) (MaxHSV);

		if (IntegerMaxHSV == red && green >= blue) 
		{
			HSV_H = (int) (60 * (green - blue) / (MaxHSV - MinHSV));
		} 
		else if (IntegerMaxHSV == red && green < blue)
		{
			HSV_H = (int) (359 + 60 * (green - blue) / (MaxHSV - MinHSV));
		} 
		else if (IntegerMaxHSV == green) 
		{
			HSV_H = (int) (119 + 60 * (blue - red) / (MaxHSV - MinHSV));
		} 
		else if (IntegerMaxHSV == blue) 
		{
			HSV_H = (int) (239 + 60 * (red - green) / (MaxHSV - MinHSV));
		}
	} 
//	else 
//		HSV_H = 0;

	Result[0] = HSV_H;
	Result[1] = HSV_S;
	Result[2] = HSV_V;
}

bool int_less(int a, int b)		//用于比较整型数，相等的情况下返回在前的参数
{
	return a < b;
}

bool double_less(double a, double b)		//用于比较浮点数，相等情况下返回在前的参数
{
	return a < b;
}