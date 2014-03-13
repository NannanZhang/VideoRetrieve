#include "LSHRetrieve.h"
using namespace std;
LSHRetrieve::LSHRetrieve(){
	m_w = 4.0;
	storeTxtPath = "../yanshi/";
}
LSHRetrieve::~LSHRetrieve(){
	
	map<string,vector<int> >::iterator itit1;
	vector<int> empty_intVector;
	for(itit1 = m_trainBow.begin();itit1!=m_trainBow.end(); itit1 ++){
		itit1->second.swap(empty_intVector);
		itit1->second.clear();
	}
	map<string,vector<int> > empty_trainBow;
	m_trainBow.swap(empty_trainBow);
	m_trainBow.clear();

	multimap<int,string> empty_trainBowIndex;
	for(int i=0;i<hashcount_bow;i++){
		m_trainBowIndex[i].swap(empty_trainBowIndex);
	}
	m_trainBowIndex->clear();

}
double LSHRetrieve::gaussrand(){
	static double V1, V2, S;
	static int phase = 0;
	double X;

	if(phase == 0)
	{
		do{
			double U1 = (double)rand() / RAND_MAX;
			double U2 = (double)rand() / RAND_MAX;

			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S  = V1 * V1 + V2 * V2;
		}while( S >= 1 || S ==0);

		X = V1 * sqrt (-2 * log(S) / S);
	}
	else
	{
		X = V2 * sqrt(-2 * log(S) / S);
	}

	phase = 1 - phase;
	return X;
}
int LSHRetrieve::hashfamily(int f[],double *a_temp,double b_temp,double w_temp)//哈希函数
{
	double result=b_temp;
	for(int i=0;i<dimention_bow;i++)
	{
		result+=f[i]*(*(a_temp+i));
	}
	return (int)(result/w_temp);//返回哈希结果
}
void LSHRetrieve::getLSHfromText(){
	string aRandomFilePath = storeTxtPath + "aRandom.txt";
	ifstream aRandomFile;

	aRandomFile.open(aRandomFilePath.c_str());

	if(!aRandomFile.is_open()){
		cout<< "random a file doesn't exit!"<<endl;
		return;
	}
	for(int j=0;j<hashcount_bow;j++)//产生hashcount个哈希表
	{
		for(int l=0;l<group_bow;l++)
		{
			for(int k=0;k<dimention_bow;k++)
			{
				aRandomFile>>m_a[j][l][k];
				//cout<<a[j][l][k]<<endl;
			}
		}
	}
	aRandomFile.close();

	string bRandomFilePath = storeTxtPath + "bRandom.txt";
	ifstream bRandomFile;

	bRandomFile.open(bRandomFilePath.c_str());

	if(!bRandomFile.is_open()){
		cout<< "random b file doesn't exit!"<<endl;
		return;
	}

	for(int i=0;i<hashcount_bow;i++)
	{
		for(int j=0;j<group_bow;j++)
		{
			bRandomFile>>m_b[i][j];
		}
	}
	bRandomFile.close();


	string ceddFilePath = storeTxtPath + "dataIndex.txt";
	ifstream ceddFile(ceddFilePath.c_str());

	//map<int,vector<int> > m_trainBow;

	string line;
	stringstream ss;
	//int imgNo = 0;
	vector<int> bowValue;
	while ( getline( ceddFile, line ) ) {
		bowValue.clear();
		ss << line;
		string imgName;
		ss >> imgName;
		int m;
		while ( ss >> m ) {
			bowValue.push_back(m);

		}
		bool isInsertSuccess = false;
		isInsertSuccess = m_trainBow.insert(make_pair(imgName,bowValue)).second;
		if(!isInsertSuccess){
			cout<<"insert error"<<endl;
			continue;
		}
		//cout<<"bowValue size: "<<bowValue.size()<<endl;
		//cout<<"m_trainBow: "<<" imgNo: "<<imgNo<<" "<< bowValue.at(0)<<" "<< bowValue.at(1)<<" "<< bowValue.at(2)<<" "<< bowValue.at(3)<<" "<< bowValue.at(4)<<" "<<endl;
		ss.clear();
		//imgNo++;
	}
	ceddFile.close();
	vector<int> empty_bowValue;
	bowValue.swap(empty_bowValue);

	string lshBowFilePath =  storeTxtPath + "lshResult.txt";
	ifstream lshBowFile;

	lshBowFile.open(lshBowFilePath.c_str());

	if(!lshBowFile.is_open()){
		cout<< "lsh file doesn't exit!"<<endl;
		return;
	}

	//imgNo = 0;
	while ( getline( lshBowFile, line ) ) {
		ss << line;
		int temp=0;
		string imgName;
		ss >> imgName;
		int m;
		while ( ss >> m ) {
			//dctValue.push_back(m);

			m_trainBowIndex[temp].insert(make_pair(m, imgName));
			/*bool isInsertSuccess = false;
			isInsertSuccess = m_trainBowIndex[temp].insert(make_pair(m, imgName)).second;
			if(!isInsertSuccess){
			cout<<"insert error"<<endl;
			continue;
			}*/
			//cout<<"hash_count: "<<temp<<" hashkey: "<<m<<" imgNO: "<<imgNo<<endl;
			temp++;
		}
		ss.clear();
		//imgNo++;
	}
	lshBowFile.close();

}
void LSHRetrieve::storLSH2Text(){

	//多hash表

	string bRandomFilePath = storeTxtPath + "bRandom.txt";
	ofstream bRandomFile(bRandomFilePath.c_str());
	if (!bRandomFile){
		cout<< bRandomFilePath << "  can't open or create "<<endl;
	}

	for(int i=0;i<hashcount_bow;i++)
	{
		for(int j=0;j<group_bow;j++)
		{
			m_b[i][j]=(double)rand() / RAND_MAX*m_w; 
			bRandomFile << m_b[i][j]<< " "; 
		}
		
	}
	bRandomFile.close();

	string aRandomFilePath = storeTxtPath + "aRandom.txt";
	ofstream aRandomFile(aRandomFilePath.c_str());

	for(int j=0;j<hashcount_bow;j++)//产生hashcount个哈希表
	{
		for(int l=0;l<group_bow;l++)
		{
			for(int k=0;k<dimention_bow;k++)
			{
				m_a[j][l][k]=gaussrand();;
				aRandomFile << m_a[j][l][k] <<" ";
			}
		}
	}
	aRandomFile.close();

	string lshBowFilePath = storeTxtPath + "lshResult.txt";
	ofstream lshBowFile(lshBowFilePath.c_str());

	string ceddFilePath = storeTxtPath + "dataIndex.txt";
	ifstream ceddFile(ceddFilePath.c_str());
	string m_buffer;
	char* m_p;
//	int imgNameNo = 0;

	//map<int,vector<int> > m_trainBow;

	string line;
	stringstream ss;
	while(getline(ceddFile,line)){
		int* features=new int[dimention_bow];
		//int features[144] = {0};
		//const int len = m_buffer.length();  
		//char* s = new char[len+1]; 
		//strcpy(s,m_buffer.c_str());  
		//m_p = strtok(s,",");//每次将空格去除
		//features[0] = atoi(m_p);
		//for(int i=1;i<144;i++){	
		//	m_p = strtok(NULL,",");//每次将空格去除
		//	features[i] = atoi(m_p);
		//}
		ss << line;
		string imgName;
		ss >> imgName;
		int m;
		int j = 0;
		while ( ss >> m ){
			features[j] = m;
			j++;
		}
		/*for(int i=0;i<144;i++){
			cout<<features[i]<<" ";
		}*/
		lshBowFile << imgName <<" ";
		vector<int> bowValue;
		for(int i=0;i<hashcount_bow;i++)
		{
			int finalHash=0;
			for(int j=0;j<group_bow;j++)
			{
				int hash_num=hashfamily(features,&m_a[i][j][0],m_b[i][j],m_w);//哈希
				finalHash = finalHash + hash_num * factor_bow[j];
			}
			bowValue.push_back(finalHash);
			m_trainBowIndex[i].insert(make_pair(finalHash,imgName));
			lshBowFile << finalHash <<" ";
		}
		//lshBowFile<<endl;
	    lshBowFile<<'\n';

		//imgNameNo ++;
		//delete[] s;
		delete[] features;

		ss.clear();
	}
	lshBowFile.close();
	ceddFile.close();
}
vector<string> LSHRetrieve::query(int features_inquery[dimention_bow],int topNumber)
{
	//int* features_inquery=new int[dimention_bow];

	/*string testCeddFilePath = storeTxtPath + "testImgFeature.txt";
	ifstream testCeddFile(testCeddFilePath.c_str());

	string line;
	stringstream ss;
	if(!getline(testCeddFile,line))
		return;
	ss << line;
	int m;
	int i = 0;
	while ( ss >> m ){
		features_inquery[i] = m;
		i++;
	}*/

	vector<int> bowValue;
	for(int i=0;i<hashcount_bow;i++)
	{
		int finalHash=0;
		for(int j=0;j<group_bow;j++)
		{
			int hash_num=hashfamily(features_inquery,&m_a[i][j][0],m_b[i][j],m_w);//哈希
			finalHash = finalHash + hash_num * factor_bow[j];
		}
		bowValue.push_back(finalHash);
	}	

	//查询有相同索引值的图像
	vector<string> similarImagesIndex;
	multimap<int,string>::iterator itit;
	int counts[hashcount_bow]={0};//记录数目
	for(int i=0;i<hashcount_bow;i++)
	{
		counts[i]=m_trainBowIndex[i].count(bowValue.at(i));//每个哈希表中关键字的个数 
	}

	for(int j=0;j<hashcount_bow;j++)
	{
		if(counts[j]>0)
		{
			itit=m_trainBowIndex[j].find(bowValue.at(j));
			while(counts[j]>0)   
			{   
				similarImagesIndex.push_back((*itit).second);
				itit++;   
				counts[j]--;
				//count_temp--;
			}   
		}	
	}
	//去除重复的值
	sort(similarImagesIndex.begin(), similarImagesIndex.end());
	similarImagesIndex.erase( unique( similarImagesIndex.begin(), similarImagesIndex.end() ), similarImagesIndex.end());

	//cout<<"similar img number : "<< similarImagesIndex.size()<<endl;

	//求与有相同索引值的图之间的欧式距离
	//map<string , int> result;

	//std::vector<int> similarImages;
	//for(int i=0;i<similarImagesIndex.size();i++)
	//{
	//	int distance;
	//	map<int,vector<int> >::iterator it;
	//	it=m_trainBow.find(similarImagesIndex.at(i));
	//	distance=getDistance(features_inquery,(*it).second);
	//	if(distance<10)//10为距离阈值
	//		similarImages.push_back(similarImagesIndex.at(i));
	//	//result.insert(make_pair(similarImagesIndex.at(i),distance));
	//}


	int similarImgNumber = similarImagesIndex.size();
	double* euDistance = new double[similarImgNumber];
	string* id = new string[similarImgNumber];
	for(int i=0;i<similarImagesIndex.size();i++){
	int distance;
	map<string,vector<int> >::iterator it;
	it = m_trainBow.find(similarImagesIndex.at(i));
	euDistance[i] = getDistance(features_inquery,(*it).second);
	id[i] = (*it).first;
	}
	QuickSort(euDistance, id, similarImgNumber);

	/*for(int j = 0; j < topNumber; j++)
	{
	cout<<"the No "<<j<<" most similar image: "<<id[j]<<" distance: "<<euDistance[j]<<endl;
	}*/
	vector<string> topNSimilarImg;
	for(int i = 0;i < topNumber; i++){
		topNSimilarImg.push_back(id[i]);
	}
	delete[] id;
	delete[] euDistance;

	return topNSimilarImg;

	//delete[] features_inquery;

	map<string,vector<int> >::iterator itit1;
	vector<int> empty_intVector;
	for(itit1 = m_trainBow.begin();itit1!=m_trainBow.end(); itit1 ++){
		itit1->second.swap(empty_intVector);
		itit1->second.clear();
	}
	map<string,vector<int> > empty_trainBow;
	m_trainBow.swap(empty_trainBow);
	m_trainBow.clear();

	multimap<int,string> empty_trainBowIndex;
	for(int i=0;i<hashcount_bow;i++){
		m_trainBowIndex[i].swap(empty_trainBowIndex);
	}
	m_trainBowIndex->clear();
}
double LSHRetrieve::getDistance(int feature[dimention_bow], std::vector<int> & dctFeature)
{
	double distance=0;
	for(int i=0;i<dimention_bow;i++)
	{
		distance += (feature[i]-dctFeature.at(i))*(feature[i]-dctFeature.at(i));
	}
	return sqrt(distance);
}
template <typename T>
void LSHRetrieve::QuickSort( T*source, string* id, int length )
{
	if(!source || length < 2)
		return;
	QSort( source, id, 0, length -1);
}
template <typename T>
void LSHRetrieve::QSort( T*source, string* id, int start, int end )
{
	if(start < end)
	{
		int pivot = Partition(source, id, start, end);
		QSort(source, id, start, pivot-1);
		QSort(source, id, pivot+1, end);
	}
}
template <typename T>
size_t LSHRetrieve::Partition( T*source, string* id, int start, int end )
{
	if(start > end || !source)
		throw std::runtime_error("Invalid Input");

	T temp = source[start];
	//size_t tmpID = id[start];
	string tmpID = id[start];
	while(start < end)
	{
		while(start < end && source[end] >= temp)
			end--;
		source[start] = source[end];
		id[start] = id[end];
		while(start < end && source[start] <= temp)
			start++;
		source[end] = source[start];
		id[end] = id[start];
	}
	source[start] = temp;
	id[start] = tmpID;

	return start;
}
