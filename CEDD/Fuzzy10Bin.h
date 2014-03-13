#pragma once
#include "util.h"
class Fuzzy10Bin
{
public:
	Fuzzy10Bin(bool bVaule);
	~Fuzzy10Bin();

public:
	bool KeepPreviuesValues;

protected:

// 	static	double HueMembershipValues[] = {0, 0, 5, 10,
// 		5, 10, 35, 50,
// 		35, 50, 70, 85,
// 		70, 85, 150, 165,
// 		150, 165, 195, 205,
// 		195, 205, 265, 280,
// 		265, 280, 315, 330,
// 		315, 330, 360, 360}; // Table Dimensions= Number Of Triangles X 4 (Start - Stop)
//	static double* HueMembershipValues;
	double* HueMembershipValues;

// 	static double SaturationMembershipValues[] = {0,0,10,75,
// 		10,75,255,255};
	double* SaturationMembershipValues;

 
// 	static double ValueMembershipValues[] = {0, 0, 10, 75,
// 		10, 75, 180, 220,
// 		180, 220, 255, 255};
	double* ValueMembershipValues;

	//Vector fuzzy10BinRules = new Vector();
public:
//	static FuzzyRules Fuzzy10BinRules[48];
	FuzzyRules Fuzzy10BinRules[48];

//	double Fuzzy10BinHisto[10];
// 	static double HueActivation[8];
// 	static double SaturationActivation[2];
// 	static double ValueActivation[3];
	double HueActivation[8];
	double SaturationActivation[2];
	double ValueActivation[3];

// 	static int Fuzzy10BinRulesDefinition[][] = {{0, 0, 0, 2},
// 		{0, 1, 0, 2},
// 		{0, 0, 2, 0},
// 		{0, 0, 1, 1},
// 		{1, 0, 0, 2},
// 		{1, 1, 0, 2},
// 		{1, 0, 2, 0},
// 		{1, 0, 1, 1},
// 		{2, 0, 0, 2},
// 		{2, 1, 0, 2},
// 		{2, 0, 2, 0},
// 		{2, 0, 1, 1},
// 		{3, 0, 0, 2},
// 		{3, 1, 0, 2},
// 		{3, 0, 2, 0},
// 		{3, 0, 1, 1},
// 		{4, 0, 0, 2},
// 		{4, 1, 0, 2},
// 		{4, 0, 2, 0},
// 		{4, 0, 1, 1},
// 		{5, 0, 0, 2},
// 		{5, 1, 0, 2},
// 		{5, 0, 2, 0},
// 		{5, 0, 1, 1},
// 		{6, 0, 0, 2},
// 		{6, 1, 0, 2},
// 		{6, 0, 2, 0},
// 		{6, 0, 1, 1},
// 		{7, 0, 0, 2},
// 		{7, 1, 0, 2},
// 		{7, 0, 2, 0},
// 		{7, 0, 1, 1},
// 		{0, 1, 1, 3},
// 		{0, 1, 2, 3},
// 		{1, 1, 1, 4},
// 		{1, 1, 2, 4},
// 		{2, 1, 1, 5},
// 		{2, 1, 2, 5},
// 		{3, 1, 1, 6},
// 		{3, 1, 2, 6},
// 		{4, 1, 1, 7},
// 		{4, 1, 2, 7},
// 		{5, 1, 1, 8},
// 		{5, 1, 2, 8},
// 		{6, 1, 1, 9},
// 		{6, 1, 2, 9},
// 		{7, 1, 1, 3},
// 		{7, 1, 2, 3}};  // 48 

//	static int** Fuzzy10BinRulesDefinition;

private:
	void FindMembershipValueForTriangles(double Input, double* Triangles, double* MembershipFunctionToSave, int TrianglesLength); 
	void LOM_Defazzificator(FuzzyRules* Rules, double* Input1, double* Input2, double* Input3, double* ResultTable, int RulesLength);
	void MultiParticipate_Equal_Defazzificator(FuzzyRules* Rules, double* Input1, double* Input2, double* Input3, double* ResultTable, int RulesLength);
	void MultiParticipate_Defazzificator(FuzzyRules* Rules, double* Input1, double* Input2, double* Input3, double* ResultTable, int RulesLength);

public:
	void ApplyFilter(double Hue, double Saturation, double Value, int Method, double *ReturnValue);

};