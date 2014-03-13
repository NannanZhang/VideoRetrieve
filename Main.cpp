// ImgRetrieveTest1.cpp : Defines the entry point for the console application.
#include "CEDD/CEDDFeature.h"
#include "LSHRetrieve.h"
#include "KeyframeExtraction.h"
using namespace std;
void test();

void testOnePic()
{

	IplImage* image = cvLoadImage("0.jpg");
	if( image == NULL)
		return;

	LSHRetrieve myLshRetrieve;
	myLshRetrieve.getLSHfromText();

	vector<string> similarImgPaths;
	string imgDataFilePath = "extractImg/";

	int imgNumberToShow = 50;

	CEDDFeature myCeddFeature;
	myCeddFeature.extract(image);
	similarImgPaths = myLshRetrieve.query(myCeddFeature.qCEDD,imgNumberToShow);

	string videoMD5filePath = "md5.txt";
	ofstream videoMD5file(videoMD5filePath.c_str());
	for(int i=0;i<imgNumberToShow;i++){
		int dotPostion = similarImgPaths.at(i).find(".");
		string md5 = similarImgPaths.at(i).substr(0,dotPostion);
		cout << md5 << endl;
		videoMD5file << md5 << endl;
	}
	videoMD5file.close();

}
int main(int argc, char *argv[])
{
	//测试
//	testOnePic();
//	return 0;
	///////////////////////////////////////////////////////
	
	char *VIDEOPATH = "fangtan.avi";
	if(argc>1){
		VIDEOPATH = argv[1];
	}

	KeyframeExtraction keyframeExtract;
	keyframeExtract.init(VIDEOPATH);
	if(keyframeExtract.simpleExtraction()<0)
		return -1;
	keyframeExtract.hsvHistExtraction();
	vector<IplImage*> keyframeList = keyframeExtract.getKeyframeList();
	//clock_t start, finish;
	//double  duration;

	//start = clock();
	LSHRetrieve myLshRetrieve;
	myLshRetrieve.getLSHfromText();
	
	//for test
	//finish = clock();
	//duration = (double)(finish - start) / CLOCKS_PER_SEC;
	//cout<< "read txt costs : "<< duration <<" seconds" <<endl;

	IplImage* image = NULL;
	CEDDFeature myCeddFeature;

	cvNamedWindow("keyframe");

	char* windowName = "showSimImg%d";
	int windowHeight = 200;
	int windowWidth = 200;
	for(int i=0;i<5;i++){
		char imgWindowName[1000];
		sprintf(imgWindowName,windowName,i);
		cvNamedWindow(imgWindowName,0);
		cvResizeWindow(imgWindowName,windowWidth,windowHeight);
		cvMoveWindow(imgWindowName,i*250,100);
	}

	IplImage* simImgs[5] = {NULL};

	
	int imgNumberToShow = 5;

	char* testImgFilePath = "%d.jpg";

	char* imgRetrievalResultFilePath = "./retriResult/tvShow/%d.jpg";
	vector<string> similarImgPaths;
	string imgDataFilePath = "../extractImg/";
	//while(1){
		similarImgPaths.clear();

		cout<< "input the img No to retrieve:"<<endl;
		int imgNo = 0;
		cin >> imgNo;
		if(imgNo == -1){
			//break;
			return -1;
		}
		char testImgPath[1000];
		sprintf(testImgPath,testImgFilePath,imgNo);

		if(!(image = cvLoadImage(testImgPath))){
			cout<< testImgPath << " doesn't exit or can't be opened !"<<endl;
	//		continue;
		}
		if(imgNo > keyframeList.size()){
			cout << "key frame No " << imgNo << "doesn't exist" << endl;
			return -1;
		}

		image = keyframeList.at(imgNo);
		//IplImage* image = cvLoadImage("0.jpg");		
	
     
		//cvShowImage("keyframe",image);
		
		//start = clock();
		myCeddFeature.extract(image);
		
		similarImgPaths = myLshRetrieve.query(myCeddFeature.qCEDD,imgNumberToShow);

		///for test
	/*	finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		cout<< "img retrieve  costs : "<< duration <<" seconds" <<endl;*/

/*
		for(int i=0;i<5;i++){
			string simImgPath = imgDataFilePath + similarImgPaths.at(i);
			simImgs[i] = cvLoadImage(simImgPath.c_str());
			char imgWindowName[1000];
			sprintf(imgWindowName,windowName,i);
//			cvShowImage(imgWindowName,simImgs[i]);
		}*/
		IplImage* simImg = NULL;
		for(int i=0;i<imgNumberToShow;i++){
			string simImgPath = imgDataFilePath + similarImgPaths.at(i);
			if(!(simImg = cvLoadImage(simImgPath.c_str()))){
				cout<< simImgPath <<"can't load"<<endl;
				continue;
			}
			char imgRetrievalResultPath[1000];
			sprintf(imgRetrievalResultPath,imgRetrievalResultFilePath,i);
		//	cvSaveImage(imgRetrievalResultPath,simImg);
		}
		
		if(simImg != NULL){
			cvReleaseImage(&simImg);
		}
		string videoMD5filePath = "md5.txt";
		ofstream videoMD5file(videoMD5filePath.c_str());
		for(int i=0;i<imgNumberToShow;i++){
			int dotPostion = similarImgPaths.at(i).find(".");
			string md5 = similarImgPaths.at(i).substr(0,dotPostion);
			cout << md5 << endl;
			videoMD5file << md5 << endl;
		}
		videoMD5file.close();
	/*	int key = cvWaitKey(2000);
		if(key == 27){
			break;
		}*/
		//system("PAUSE");
	//}
	if(image != NULL){
		cvReleaseImage(&image);
	}

	vector<string> emptySimilarImgs;
	similarImgPaths.swap(emptySimilarImgs);
	similarImgPaths.clear();
	cvWaitKey(-1);
	//system("pause");
	return 0;

}
void test(){
	//cvNamedWindow("keyframe");
	
	/*IplImage* simImg1 = NULL;
	IplImage* simImg2 = NULL;
	IplImage* simImg3 = NULL;
	IplImage* simImg4 = NULL;
	IplImage* simImg5 = NULL;*/
	char* testImgFilePath = "../%d.jpg";
	char* windowName = "showSimImg%d";
	int windowHeight = 200;
	int windowWidth = 200;
	for(int i=0;i<1;i++){
		char imgWindowName[1000];
		sprintf(imgWindowName,windowName,i);
		cvNamedWindow(imgWindowName,0);
		cvResizeWindow(imgWindowName,windowWidth,windowHeight);
		cvMoveWindow(imgWindowName,i*250,100);
	}
	IplImage* simImgs[5] = {NULL};
	string imgDataFilePath = "extractImg/";
	for(int i=0;i<1;i++){
		char simImgPath[1000];// = imgDataFilePath +i+ ".jpg";
		sprintf(simImgPath,testImgFilePath,i);
		simImgs[i] = cvLoadImage(simImgPath);
		char imgWindowName[1000];
		sprintf(imgWindowName,windowName,i);
		cvShowImage(imgWindowName,simImgs[i]);
	}
	cvWaitKey(-1);
}
