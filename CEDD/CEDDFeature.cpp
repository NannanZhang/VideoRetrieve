#include "CEDDFeature.h"
#include "Fuzzy10Bin.h"
#include "Fuzzy24Bin.h"
#include "RGB2HSV.h"

#include <vector>
using namespace std;

#include <math.h>

#include "CEDDQuant.h"
#include "CompactCEDDQuant.h"

CEDDFeature::CEDDFeature(): T0(14), T1(0.68), T2(0.98), T3(0.98), Compact(false)
{
//	data = NULL;

}

CEDDFeature::~CEDDFeature()
{
// 	if(data)
// 	{
// 		delete []data;
// 		data = NULL;
// 	}

}

int CEDDFeature::extract(IplImage* image)
{

	Fuzzy10Bin Fuzzy10(false);
	Fuzzy24Bin Fuzzy24(false);
	RGB2HSV HSVConverter;

	int HSV[3];

	double Fuzzy10BinResultTable[10];
	double Fuzzy24BinResultTable[24];
	double CEDD[144];

	int width = image->width;
	int height = image->height;

	
//	double[][] ImageGrid = new double[width][height];
//	vector<vector<int> > ImageGrid(width, vector<int>(height));
	int *tmpArray   = new int[width*height];   
	int **ImageGrid = new int*[width];  
	for(int i=0;i<width;i++){
		ImageGrid[i] = new int[height];
	}
	/*for(int i=0; i<width; ++i)   
		ImageGrid[i] = tmpArray + i*height;  */

	double PixelCount[2][2];

//  int[][] ImageGridRed = new int[width][height];
//	vector<vector<int> > ImageGridRed(width, vector<int>(height));
	int *tmpArrayR   = new int[width*height];   
	int **ImageGridRed = new int *[width];   
	//ImageGridRed = new int *[width]; 
	for(int i=0; i<width; i++){
		ImageGridRed[i] = new int[height];
		/*for(int j=0; j<width; j++){   
			ImageGridRed[i][j] = tmpArrayR+i*height+j;
		}*/
	}
	

//  int[][] ImageGridGreen = new int[width][height];
//	vector<vector<int> > ImageGridGreen(width, vector<int>(height));
	int *tmpArrayG   = new int[width*height];   
	int **ImageGridGreen = new int*[width];   
	//ImageGridGreen = new int *[width];   
	for(int i=0; i<width; i++){
		ImageGridGreen[i] = new int[height];
	}
	//for(int i=0; i<width; ++i)   
		//ImageGridGreen[i] = tmpArrayG + i*height;

//	int[][] ImageGridBlue = new int[width][height];
//	vector<vector<int> > ImageGridBlue(width, vector<int>(height));
	int *tmpArrayB   = new int[width*height];   
	int **ImageGridBlue = new int*[width];   
	//ImageGridBlue = new int *[width]; 
	for(int i=0; i<width; i++){
		ImageGridBlue[i] = new int[height];
	}
	/*for(int i=0; i<width; ++i)   
	ImageGridBlue[i] = tmpArrayB + i*height;*/

	int NumberOfBlocks = 1600;

	/*分块，确定每块步长*/
	////////////////////////////////////////////////////////////////////////////////
	int Step_X = (int) floor(width / sqrt((double)NumberOfBlocks));
	int Step_Y = (int) floor(height / sqrt((double)NumberOfBlocks));

	if ((Step_X % 2) != 0) 
	{
		Step_X = Step_X - 1;
	}

	if ((Step_Y % 2) != 0) 
	{
		Step_Y = Step_Y - 1;
	}


	if (Step_Y < 2)
		Step_Y = 2;

	if (Step_X < 2)
		Step_X = 2;

	/////////////////////////////////////////////////////////////////////////////////

	int Edges[6];

	MaskResults MaskValues;
	Neighborhood PixelsNeighborhood;

	for (int i = 0; i < 144; i++) 
	{
		CEDD[i] = 0;
	}

	/*取得各像素点的RGB值，按列取*/
	///////////////////////////////////////////////////////////////////////////////////
	CvScalar pixel;
	for (int x = 0; x < width; x++) 
	{
		for (int y = 0; y < height; y++) 
		{
			//int pixel = image.getRGB(x, y);

			pixel = cvGet2D(image, y, x);   //获得像素的RGB值, 注意内存中存储顺序是BGR

			ImageGridRed[x][y] = pixel.val[2];
			ImageGridGreen[x][y] = pixel.val[1];
			ImageGridBlue[x][y] = pixel.val[0];

			int mean = (int) (0.114 * ImageGridBlue[x][y] + 0.587 * ImageGridGreen[x][y] + 0.299 * ImageGridRed[x][y]);

			ImageGrid[x][y] = mean;
		}

	}
   ///////////////////////////////////////////////////////////////////////////////////

	int* CororRed = new int[Step_Y * Step_X];
	int* CororGreen = new int[Step_Y * Step_X];
	int* CororBlue = new int[Step_Y * Step_X];

	int* CororRedTemp = new int[Step_Y * Step_X];
	int* CororGreenTemp = new int[Step_Y * Step_X];
	int* CororBlueTemp = new int[Step_Y * Step_X];

	int MeanRed, MeanGreen, MeanBlue = 0;

	/*Extract CEDD Feature, 各块按行处理*/
	//////////////////////////////////////////////////////////////////////////////////
	for (int y = 0; y < height - Step_Y; y += Step_Y)
	{
		for (int x = 0; x < width - Step_X; x += Step_X)
		{
			/*Extract Texture Feature*/
			//////////////////////////////////////////////////////////////////////////////////
			MeanRed = 0;
			MeanGreen = 0;
			MeanBlue = 0;
			PixelsNeighborhood.Area1 = 0;
			PixelsNeighborhood.Area2 = 0;
			PixelsNeighborhood.Area3 = 0;
			PixelsNeighborhood.Area4 = 0;
			Edges[0] = -1;
			Edges[1] = -1;
			Edges[2] = -1;
			Edges[3] = -1;
			Edges[4] = -1;
			Edges[5] = -1;

			for (int i = 0; i < 2; i++) 
			{
				for (int j = 0; j < 2; j++) 
				{
					PixelCount[i][j] = 0;
				}

			}

			int TempSum = 0;

			/*块内按行处理*/
			for (int i = y; i < y + Step_Y; i++) 
			{
				for (int j = x; j < x + Step_X; j++) 
				{

					CororRed[TempSum] = ImageGridRed[j][i];
					CororGreen[TempSum] = ImageGridGreen[j][i];
					CororBlue[TempSum] = ImageGridBlue[j][i];

					CororRedTemp[TempSum] = ImageGridRed[j][i];
					CororGreenTemp[TempSum] = ImageGridGreen[j][i];
					CororBlueTemp[TempSum] = ImageGridBlue[j][i];

					TempSum++;

					if (j < (x + Step_X / 2) && i < (y + Step_Y / 2))
						PixelsNeighborhood.Area1 += 4 * ImageGrid[j][i] / (Step_X * Step_Y);
					if (j >= (x + Step_X / 2) && i < (y + Step_Y / 2))
						PixelsNeighborhood.Area2 += 4 * ImageGrid[j][i] / (Step_X * Step_Y);
					if (j < (x + Step_X / 2) && i >= (y + Step_Y / 2))
						PixelsNeighborhood.Area3 += 4 * ImageGrid[j][i] / (Step_X * Step_Y);
					if (j >= (x + Step_X / 2) && i >= (y + Step_Y / 2))
						PixelsNeighborhood.Area4 += 4 * ImageGrid[j][i] / (Step_X * Step_Y);
				}
			}

			MaskValues.Mask1 = fabs(PixelsNeighborhood.Area1 * 2 + PixelsNeighborhood.Area2 * -2 + PixelsNeighborhood.Area3 * -2 + PixelsNeighborhood.Area4 * 2);	//non-direction
			MaskValues.Mask2 = fabs(PixelsNeighborhood.Area1 * 1 + PixelsNeighborhood.Area2 * 1 + PixelsNeighborhood.Area3 * -1 + PixelsNeighborhood.Area4 * -1);	//horizontal
			MaskValues.Mask3 = fabs(PixelsNeighborhood.Area1 * 1 + PixelsNeighborhood.Area2 * -1 + PixelsNeighborhood.Area3 * 1 + PixelsNeighborhood.Area4 * -1);	//vertical
			MaskValues.Mask4 = fabs(PixelsNeighborhood.Area1 *  sqrt((double)2) + PixelsNeighborhood.Area2 * 0 + PixelsNeighborhood.Area3 * 0 + PixelsNeighborhood.Area4 * - sqrt((double)2));	//45 diagonal
			MaskValues.Mask5 = fabs(PixelsNeighborhood.Area1 * 0 + PixelsNeighborhood.Area2 *  sqrt((double)2) + PixelsNeighborhood.Area3 * - sqrt((double)2) + PixelsNeighborhood.Area4 * 0);	//135 diagonal

			double Max = max(MaskValues.Mask1, max(MaskValues.Mask2, max(MaskValues.Mask3, max(MaskValues.Mask4, MaskValues.Mask5))));

			MaskValues.Mask1 = MaskValues.Mask1 / Max;
			MaskValues.Mask2 = MaskValues.Mask2 / Max;
			MaskValues.Mask3 = MaskValues.Mask3 / Max;
			MaskValues.Mask4 = MaskValues.Mask4 / Max;
			MaskValues.Mask5 = MaskValues.Mask5 / Max;

			int T = -1;

			if (Max < T0) 
			{
				Edges[0] = 0;
				T = 0;
			} 
			else 
			{
				T = -1;

				if (MaskValues.Mask1 > T1) 
				{
					T++;
					Edges[T] = 1;
				}
				if (MaskValues.Mask2 > T2) 
				{
					T++;
					Edges[T] = 2;
				}
				if (MaskValues.Mask3 > T2) 
				{
					T++;
					Edges[T] = 3;
				}
				if (MaskValues.Mask4 > T3) 
				{
					T++;
					Edges[T] = 4;
				}
				if (MaskValues.Mask5 > T3) 
				{
					T++;
					Edges[T] = 5;
				}
			}
			//////////////////////////////////////////////////////////////////////////////////

			/*Extract Color Feature*/
			//////////////////////////////////////////////////////////////////////////////////
// 			int TempColor = 0;
// 			double* ColorGreaterThanThress = new double[Step_Y * Step_X];
// 
// 			for (int i = 0; i < (Step_Y * Step_X); i++) 
// 			{
// 				TempColor = i;
// 
// 				for (int j = 0; j < (Step_Y * Step_X); j++) 
// 				{
// 					if (CororRedTemp[j] == CororRed[i] && CororGreenTemp[j] == CororGreen[i] && CororBlueTemp[j] == CororBlue[i]) 
// 					{
// 
// 						ColorGreaterThanThress[i] += (double) 1 / (double) (Step_Y * Step_X);
// 						CororRedTemp[j] = -1;
// 						CororGreenTemp[j] = -1;
// 						CororBlueTemp[j] = -1;
// 
// 					}
// 
// 				}
// 
// 			}
// 
// 			TempColor = 0;
// 
// 			for (int i = 0; i < (Step_Y * Step_X); i++) 
// 			{
// 				if (ColorGreaterThanThress[i] >= 0.5) 
// 				{
// 					TempColor++;
// 					MeanRed = CororRed[i];
// 					MeanGreen = CororGreen[i];
// 					MeanBlue = CororBlue[i];
// 				}
// 
// 			}
// 
// 			if (TempColor == 0) 
// 			{
// 				for (int i = 0; i < (Step_Y * Step_X); i++) 
// 				{
// 					MeanRed += CororRed[i] / (Step_Y * Step_X);
// 					MeanGreen += CororGreen[i] / (Step_Y * Step_X);
// 					MeanBlue += CororBlue[i] / (Step_Y * Step_X);
// 				}
// 			}
// 
// 			//释放内存
// 			delete []ColorGreaterThanThress;
// 			ColorGreaterThanThress = NULL;

			for (int i = 0; i < (Step_Y * Step_X); i++)
			{
				MeanRed += CororRed[i];
				MeanGreen += CororGreen[i];
				MeanBlue += CororBlue[i];
			}

			MeanRed = (int)(MeanRed / (Step_Y * Step_X));
			MeanGreen = (int)(MeanGreen / (Step_Y * Step_X));
			MeanBlue = (int)(MeanBlue / (Step_Y * Step_X));

			
			HSVConverter.ApplyFilter(MeanRed, MeanGreen, MeanBlue, HSV);

			if (Compact == false) 
			{
				//Fuzzy10BinResultTable = Fuzzy10.ApplyFilter(HSV[0], HSV[1], HSV[2], 2);
				//Fuzzy24BinResultTable = Fuzzy24.ApplyFilter(HSV[0], HSV[1], HSV[2], Fuzzy10BinResultTable, 2);
				Fuzzy10.ApplyFilter(HSV[0], HSV[1], HSV[2], 2, Fuzzy10BinResultTable);
				
// 				double tmpFuzzy10BinResultTable[10];
// 				for (int i = 0; i< 10; i++)
// 				{
// 					tmpFuzzy10BinResultTable[i] = Fuzzy10BinResultTable[10];
// 				}

				Fuzzy24.ApplyFilter(HSV[0], HSV[1], HSV[2], Fuzzy10BinResultTable, 2, Fuzzy24BinResultTable);

				for (int i = 0; i <= T; i++) 
				{
					for (int j = 0; j < 24; j++) 
					{

						if (Fuzzy24BinResultTable[j] > 0) 
							CEDD[24 * Edges[i] + j] += Fuzzy24BinResultTable[j];

					}

				}
			} 
			else 
			{

				//Fuzzy10BinResultTable = Fuzzy10.ApplyFilter(HSV[0], HSV[1], HSV[2], 2);
				Fuzzy10.ApplyFilter(HSV[0], HSV[1], HSV[2], 2, Fuzzy10BinResultTable);

				for (int i = 0; i <= T; i++) 
				{
					for (int j = 0; j < 10; j++) 
					{

						if (Fuzzy10BinResultTable[j] > 0) 
							CEDD[10 * Edges[i] + j] += Fuzzy10BinResultTable[j];

					}

				}
			}

			//////////////////////////////////////////////////////////////////////////////////
		}
	}

	//释放内存
	delete []ImageGrid;
	ImageGrid = NULL;

	delete []ImageGridRed;
	ImageGridRed = NULL;

	delete []ImageGridGreen;
	ImageGridGreen = NULL;

	delete []ImageGridBlue;
	ImageGridBlue = NULL;

	//释放内存
	delete []CororRed;
	CororRed = NULL;

	delete []CororGreen;
	CororGreen = NULL;

	delete []CororBlue;
	CororBlue = NULL;

	delete []CororRedTemp;
	CororRedTemp = NULL;

	delete []CororGreenTemp;
	CororGreenTemp = NULL;

	delete []CororBlueTemp;
	CororBlueTemp = NULL;

	//////////////////////////////////////////////////////////////////////////////////

	/*量化*/
	//////////////////////////////////////////////////////////////////////////////////
	/*归一化*/
	//////////////////////////////////////////////////////////////////////////////////
	double Sum = 0;

	for (int i = 0; i < 144; i++) 
	{
		Sum += CEDD[i];
	}

	for (int i = 0; i < 144; i++) 
	{
		CEDD[i] = CEDD[i] / Sum;
	}
	//////////////////////////////////////////////////////////////////////////////////

	if (Compact == false) 
	{
		CEDDQuant quants;

		quants.Apply(CEDD, qCEDD);	// 抽取特征

//		data = qCEDD; 
	}
	else 
	{
		CompactCEDDQuant quants;

		quants.Apply(CEDD, qCEDD);  // 抽取特征（Compact）

//		data = qCEDD;
	}

	//        for (int i = 0; i < qCEDD.length; i++)
	//            System.out.println(qCEDD[i]);

	//////////////////////////////////////////////////////////////////////////////////


	delete []tmpArray;
	delete []tmpArrayB;
	delete []tmpArrayG;
	delete []tmpArrayR;
	
	return 0;

}
