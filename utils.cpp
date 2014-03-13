#include "utils.h"
using namespace std;

//获取指定目录下的文件列表 
std::vector<std::string> getfilelist(std::string strSourceDir) 
{ 
	std::vector<std::string> flist; 
	//保存文件列表 
	std::string strFileList = ""; 

	//要查找的目录 
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
			//保存文件名 
			flist.push_back(file.name); 
		} 
	} 
	_findclose(longf); 

	return flist; 
} 

