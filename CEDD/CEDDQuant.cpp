
#include "CEDDQuant.h"
#include <math.h>
using namespace std;
CEDDQuant::CEDDQuant()
{
	static double tmpQuantTable[] = {180.19686541079636, 23730.024499150866, 61457.152912541605, 113918.55437576842, 179122.46400035513, 260980.3325940354, 341795.93301552488, 554729.98648386425};
	static double tmpQuantTable2[] = {209.25176965926232, 22490.5872862417345, 60250.8935141849988, 120705.788057580583, 181128.08709063051, 234132.081356900555, 325660.617733105708, 520702.175858657472};
	static double tmpQuantTable3[] = {405.4642173212585, 4877.9763319071481, 10882.170090625908, 18167.239081219657, 27043.385568785292, 38129.413201299016, 52675.221316293857, 79555.402607004813};
	static double tmpQuantTable4[] = {405.4642173212585, 4877.9763319071481, 10882.170090625908, 18167.239081219657, 27043.385568785292, 38129.413201299016, 52675.221316293857, 79555.402607004813};
	static double tmpQuantTable5[] = {968.88475977695578, 10725.159033657819, 24161.205360376698, 41555.917344385321, 62895.628446402261, 93066.271379694881, 136976.13317822068, 262897.86056221306};
	static double tmpQuantTable6[] = {968.88475977695578, 10725.159033657819, 24161.205360376698, 41555.917344385321, 62895.628446402261, 93066.271379694881, 136976.13317822068, 262897.86056221306};

	QuantTable = tmpQuantTable;
	QuantTable2 = tmpQuantTable2;
	QuantTable3 = tmpQuantTable3;
	QuantTable4 = tmpQuantTable4;
	QuantTable5 = tmpQuantTable5;
	QuantTable6 = tmpQuantTable6;

}

CEDDQuant::~CEDDQuant()
{

}

void CEDDQuant::Apply(double *Local_Edge_Histogram, int *Edge_HistogramElement)
{
	double ElementsDistance[8];

	double Max = 1;

	/*1-24*/
	//////////////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < 24; i++)

	{

		Edge_HistogramElement[i] = 0;

		for (int j = 0; j < 8; j++)

		{

			ElementsDistance[j] = abs(Local_Edge_Histogram[i] - QuantTable[j] / 1000000);

		}

		Max = 1;

		for (int j = 0; j < 8; j++)

		{

			if (ElementsDistance[j] < Max)

			{

				Max = ElementsDistance[j];

				Edge_HistogramElement[i] = j;

			}

		}


	}

	//////////////////////////////////////////////////////////////////////////////////////


	/*25-48*/
	//////////////////////////////////////////////////////////////////////////////////////


	for (int i = 24; i < 48; i++)

	{

		Edge_HistogramElement[i] = 0;

		for (int j = 0; j < 8; j++)

		{

			ElementsDistance[j] = abs(Local_Edge_Histogram[i] - QuantTable2[j] / 1000000);

		}

		Max = 1;

		for (int j = 0; j < 8; j++)

		{

			if (ElementsDistance[j] < Max)

			{

				Max = ElementsDistance[j];

				Edge_HistogramElement[i] = j;

			}

		}


	}

	//////////////////////////////////////////////////////////////////////////////////////


	/*49-72*/
	//////////////////////////////////////////////////////////////////////////////////////


	for (int i = 48; i < 72; i++)

	{

		Edge_HistogramElement[i] = 0;

		for (int j = 0; j < 8; j++)

		{

			ElementsDistance[j] = abs(Local_Edge_Histogram[i] - QuantTable3[j] / 1000000);

		}

		Max = 1;

		for (int j = 0; j < 8; j++)

		{

			if (ElementsDistance[j] < Max)

			{

				Max = ElementsDistance[j];

				Edge_HistogramElement[i] = j;

			}

		}


	}

	//////////////////////////////////////////////////////////////////////////////////////


	/*73-96*/
	//////////////////////////////////////////////////////////////////////////////////////

	for (int i = 72; i < 96; i++)

	{

		Edge_HistogramElement[i] = 0;

		for (int j = 0; j < 8; j++)

		{

			ElementsDistance[j] = abs(Local_Edge_Histogram[i] - QuantTable4[j] / 1000000);

		}

		Max = 1;

		for (int j = 0; j < 8; j++)

		{

			if (ElementsDistance[j] < Max)

			{

				Max = ElementsDistance[j];

				Edge_HistogramElement[i] = j;

			}

		}


	}

	//////////////////////////////////////////////////////////////////////////////////////


	/*97-120*/
	//////////////////////////////////////////////////////////////////////////////////////


	for (int i = 96; i < 120; i++)

	{

		Edge_HistogramElement[i] = 0;

		for (int j = 0; j < 8; j++)

		{

			ElementsDistance[j] = abs(Local_Edge_Histogram[i] - QuantTable5[j] / 1000000);

		}

		Max = 1;

		for (int j = 0; j < 8; j++)

		{

			if (ElementsDistance[j] < Max)

			{

				Max = ElementsDistance[j];

				Edge_HistogramElement[i] = j;

			}

		}


	}

	//////////////////////////////////////////////////////////////////////////////////////


	/*121-144*/
	//////////////////////////////////////////////////////////////////////////////////////

	for (int i = 120; i < 144; i++)

	{

		Edge_HistogramElement[i] = 0;

		for (int j = 0; j < 8; j++)

		{

			ElementsDistance[j] = abs(Local_Edge_Histogram[i] - QuantTable6[j] / 1000000);

		}

		Max = 1;

		for (int j = 0; j < 8; j++)

		{

			if (ElementsDistance[j] < Max)

			{

				Max = ElementsDistance[j];

				Edge_HistogramElement[i] = j;

			}

		}


	}
	//////////////////////////////////////////////////////////////////////////////////////

}
