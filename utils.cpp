#include "utils.h"
using namespace std;

//��ȡָ��Ŀ¼�µ��ļ��б� 
std::vector<std::string> getfilelist(std::string strSourceDir) 
{ 
	std::vector<std::string> flist; 
	//�����ļ��б� 
	std::string strFileList = ""; 

	//Ҫ���ҵ�Ŀ¼ 
	strSourceDir = strSourceDir + "*.*"; 

	_finddata_t file; 
	long longf; 

	if((longf = _findfirst(strSourceDir.c_str(), &file)) == -1l) 
	{ 
		return flist; 
	} 
	else 
	{ 
		std::string tempName; 

		while( _findnext(longf, &file ) == 0) 
		{ 
			tempName = ""; 
			tempName = file.name; 
			if (tempName == "..") 
			{ 
				continue; 
			} 
			//�����ļ��� 
			flist.push_back(file.name); 
		} 
	} 
	_findclose(longf); 

	return flist; 
} 

