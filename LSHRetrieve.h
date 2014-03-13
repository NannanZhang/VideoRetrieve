

#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <hash_map>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include "utils.h"
#include <stdexcept>

static const int dimention_bow=144;//维度
static const int group_bow=10;//组数
static const int hashcount_bow=5;//哈希表数量
static const int factor_bow[10]={1,2,3,5,7,11,13,17,19,23};
using namespace std;
//using namespace stdext;

class LSHRetrieve{
public:
	LSHRetrieve();
	~LSHRetrieve();
private:
	int hashcount;
	map<string,vector<int> > m_trainBow;
	multimap<int,string> m_trainBowIndex[hashcount_bow];
	string storeTxtPath;

	double m_a[hashcount_bow][group_bow][dimention_bow];
	double m_b[hashcount_bow][group_bow];
	double m_w;

private:
	
	template <typename T>
	size_t Partition( T*source, string* id, int start, int end );

	template <typename T>
	void QSort( T*source, string* id, int start, int end );

	template <typename T>
	void QuickSort( T*source, string* id, int length );

	double gaussrand();//高斯分布
	int hashfamily(int f[],double *a_temp,double b_temp,double w_temp);//f为特征，a_temp为a向量，b_temp为b，w_temp为w
	
	void storLSH2Text();
	//void query();
	double getDistance(int feature[dimention_bow], std::vector<int> & dctFeature);
public:
	void getLSHfromText();
	vector<string> query(int features_inquery[dimention_bow],int topNumber);
};
