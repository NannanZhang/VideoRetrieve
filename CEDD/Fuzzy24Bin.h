#pragma once
#include "util.h"
class Fuzzy24Bin
{
public:
	Fuzzy24Bin(bool bVaule);
	~Fuzzy24Bin();

public:
	bool KeepPreviuesValues;

public:
	double ResultsTable[3];
//	double Fuzzy24BinHisto[24];

protected:
	double* SaturationMembershipValues;
	double* ValueMembershipValues;

public:
	FuzzyRules Fuzzy24BinRules[4];

	double SaturationActivation[2];
	double ValueActivation[2];

private:
	void FindMembershipValueForTriangles(double Input, double* Triangles, double* MembershipFunctionToSave,int TrianglesLength);
	void LOM_Defazzificator(FuzzyRules* Rules, double* Input1, double* Input2, double* ResultTable, int RulesLength);
	void MultiParticipate_Equal_Defazzificator(FuzzyRules* Rules, double* Input1, double* Input2, double* ResultTable, int RulesLength);
	void MultiParticipate_Defazzificator(FuzzyRules* Rules, double* Input1, double* Input2, double* ResultTable, int RulesLength);

public:
	void ApplyFilter(double Hue, double Saturation, double Value, double* ColorValues, int Method, double* Results);
};