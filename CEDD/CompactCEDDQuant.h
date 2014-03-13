#pragma once
#include <stdlib.h>

class CompactCEDDQuant
{
public:
	CompactCEDDQuant();
	~CompactCEDDQuant();

public:
	void Apply(double* Local_Edge_Histogram, int* Edge_HistogramElement);

private:
	double *QuantTable;
	double *QuantTable2;
    double *QuantTable3;
    double *QuantTable4;
	double *QuantTable5;
	double *QuantTable6;
};
