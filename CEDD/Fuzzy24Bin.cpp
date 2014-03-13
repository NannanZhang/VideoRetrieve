

#include "Fuzzy24Bin.h"

#include "RGB2HSV.h"

Fuzzy24Bin::Fuzzy24Bin(bool bVaule)
{
	static double tmpSaturationMembershipValues[] = {0, 0, 68, 188,
		68, 188, 255, 255};

	SaturationMembershipValues = tmpSaturationMembershipValues;

	static double tmpValueMembershipValues[] = {0, 0, 68, 188,
		68, 188, 255, 255};

	ValueMembershipValues = tmpValueMembershipValues;

 	static int Fuzzy24BinRulesDefinition[][3] = {
 		{1, 1, 1},
 		{0, 0, 2},
 		{0, 1, 0},
 		{1, 0, 2}};

		for (int R = 0; R < 4; R++) 
		{
			//Fuzzy24BinRules[R] = new FuzzyRules();
			Fuzzy24BinRules[R].Input1 = Fuzzy24BinRulesDefinition[R][0];
			Fuzzy24BinRules[R].Input2 = Fuzzy24BinRulesDefinition[R][1];
			Fuzzy24BinRules[R].Output = Fuzzy24BinRulesDefinition[R][2];

		}

	KeepPreviuesValues = bVaule;
}

Fuzzy24Bin::~Fuzzy24Bin()
{

}

void Fuzzy24Bin::FindMembershipValueForTriangles(double Input, double* Triangles, double* MembershipFunctionToSave,int TrianglesLength)
{
	int Temp = 0;

	for (int i = 0; i <= TrianglesLength - 1; i += 4) 
	{

		MembershipFunctionToSave[Temp] = 0;

		if (Input >= Triangles[i + 1] && Input <= Triangles[i + 2]) 
		{
			MembershipFunctionToSave[Temp] = 1;
		}

		if (Input >= Triangles[i] && Input < Triangles[i + 1]) 
		{
			MembershipFunctionToSave[Temp] = (Input - Triangles[i]) / (Triangles[i + 1] - Triangles[i]);
		}

		if (Input > Triangles[i + 2] && Input <= Triangles[i + 3]) 
		{
			MembershipFunctionToSave[Temp] = (Input - Triangles[i + 2]) / (Triangles[i + 2] - Triangles[i + 3]) + 1;
		}

		Temp += 1;
	}
}

void Fuzzy24Bin::LOM_Defazzificator(FuzzyRules* Rules, double* Input1, double* Input2, double* ResultTable, int RulesLength)
{
	int RuleActivation = -1;
	double LOM_MAXofMIN = 0;

	for (int i = 0; i < RulesLength; i++) {

		if ((Input1[Rules[i].Input1] > 0) && (Input2[Rules[i].Input2] > 0)) {

			double Min = 0;
			Min = min(Input1[Rules[i].Input1], Input2[Rules[i].Input2], double_less);

			if (Min > LOM_MAXofMIN) {
				LOM_MAXofMIN = Min;
				RuleActivation = Rules[i].Output;
			}

		}

	}

	ResultTable[RuleActivation]++;

}

void Fuzzy24Bin::MultiParticipate_Equal_Defazzificator(FuzzyRules* Rules, double* Input1, double* Input2, double* ResultTable, int RulesLength)
{
	int RuleActivation = -1;

	for (int i = 0; i < RulesLength; i++) 
	{
		if ((Input1[Rules[i].Input1] > 0) && (Input2[Rules[i].Input2] > 0)) 
		{
			RuleActivation = Rules[i].Output;
			ResultTable[RuleActivation]++;

		}

	}
}

void Fuzzy24Bin::MultiParticipate_Defazzificator(FuzzyRules* Rules, double* Input1, double* Input2, double* ResultTable, int RulesLength)
{
	int RuleActivation = -1;
	double Min = 0;
	for (int i = 0; i < RulesLength; i++) 
	{
		if ((Input1[Rules[i].Input1] > 0) && (Input2[Rules[i].Input2] > 0)) 
		{
			Min = min(Input1[Rules[i].Input1], Input2[Rules[i].Input2], double_less);

			RuleActivation = Rules[i].Output;
			ResultTable[RuleActivation] += Min;

		}

	}
}

void Fuzzy24Bin::ApplyFilter(double Hue, double Saturation, double Value, double* ColorValues, int Method, double* Fuzzy24BinHisto)
{
	ResultsTable[0] = 0;
	ResultsTable[1] = 0;
	ResultsTable[2] = 0;
	double Temp = 0;


	FindMembershipValueForTriangles(Saturation, SaturationMembershipValues, SaturationActivation, 8);		//输出SaturationActivation, 数组中两个数之和为1
	FindMembershipValueForTriangles(Value, ValueMembershipValues, ValueActivation, 8);		//输出ValueActivation, 数组中两个数之和为1


	if (KeepPreviuesValues == false) 
	{
		for (int i = 0; i < 24; i++) 
		{
			Fuzzy24BinHisto[i] = 0;
		}

	}

	for (int i = 3; i < 10; i++) 
	{
		Temp += ColorValues[i];
	}

	if (Temp > 0)	//输出Result, 数组中三个数之和为1
	{
		if (Method == 0) 
			LOM_Defazzificator(Fuzzy24BinRules, SaturationActivation, ValueActivation, ResultsTable, 4);
		if (Method == 1)
			MultiParticipate_Equal_Defazzificator(Fuzzy24BinRules, SaturationActivation, ValueActivation, ResultsTable, 4);
		if (Method == 2)
			MultiParticipate_Defazzificator(Fuzzy24BinRules, SaturationActivation, ValueActivation, ResultsTable, 4);


	}

	for (int i = 0; i < 3; i++) 
	{
		Fuzzy24BinHisto[i] += ColorValues[i];
	}


	for (int i = 3; i < 10; i++)
	{
		Fuzzy24BinHisto[(i - 2) * 3] += ColorValues[i] * ResultsTable[0];
		Fuzzy24BinHisto[(i - 2) * 3 + 1] += ColorValues[i] * ResultsTable[1];
		Fuzzy24BinHisto[(i - 2) * 3 + 2] += ColorValues[i] * ResultsTable[2];
	}

//	return (Fuzzy24BinHisto);

}
