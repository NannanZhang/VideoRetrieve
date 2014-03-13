#pragma once
//#include <cv.h>
#include "../PublicHeaders.h"

class CEDDFeature
{
public:
	CEDDFeature();
	~CEDDFeature();

public:
	int extract(IplImage* image);

public:
	double T0;
	double T1;
	double T2;
	double T3;
	bool Compact;
	int qCEDD[144];
//	double* data;
};
