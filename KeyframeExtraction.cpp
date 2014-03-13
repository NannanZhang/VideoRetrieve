#include "KeyframeExtraction.h"
using namespace std;
KeyframeExtraction::KeyframeExtraction(){
	RATIO_T = 0.4;
}
KeyframeExtraction::~KeyframeExtraction(){

}
void KeyframeExtraction::init(char *videoPath){
	this->videoPath = videoPath;
	//simpleFrameList.clear();
	//keyframeList.clear();
}
int KeyframeExtraction::simpleExtraction(){
	CvCapture* pCapture = NULL;
	//char *VIDEOPATH = "F:/database/yanshi/访谈类节目 标清.avi";
	int nTotalFrame = 0;           ///<当前视频总帧数*/
	int nFps;                  ///<当前视频默认帧率
	IplImage *pOriFrame = NULL;          ///<原始帧(3通道)
	//IplImage *grayFrame = NULL;

	pCapture = cvCreateFileCapture(videoPath);///<获取视频头指针
	if (pCapture == NULL)
        {
		printf("capture NULL");
		return -1;///<获取失败返回-1
	}
	pOriFrame = cvQueryFrame(pCapture);
	if (!pOriFrame){
		printf("frame == NULL");
		return -1;

	}
	//grayFrame = cvCreateImage(cvSize(pOriFrame->width,pOriFrame->height),IPL_DEPTH_8U,1);
	///视频信息
	nTotalFrame   = (int)cvGetCaptureProperty(pCapture, CV_CAP_PROP_FRAME_COUNT);///<获取视频总帧数
	nFps          = (int)cvGetCaptureProperty(pCapture, CV_CAP_PROP_FPS);///<获取视频帧率
	cvSetCaptureProperty(pCapture, CV_CAP_PROP_POS_FRAMES, 1);///<重置视频当前帧为首帧

	float frameNumPerMinute = 1;
	int perFrameFromframeNum = nFps*60/frameNumPerMinute;
	int nFrmNum = perFrameFromframeNum/2;
	int extractFrameNum = 0;
	//CString framePath = "F:\\database\\yanshi\\frame\\fangtan\\%d.jpg";
	while(1){//!pOriFrame){//nTotalFrame){
		cvSetCaptureProperty(pCapture,CV_CAP_PROP_POS_FRAMES,nFrmNum);
		pOriFrame = cvQueryFrame(pCapture);
		int nCurrentFrame = (int)cvGetCaptureProperty(pCapture, CV_CAP_PROP_POS_FRAMES);
		if (!pOriFrame){
			break;
		}
		//CString frameNoPath;
		//frameNoPath.Format(framePath,extractFrameNum);
		//cvCvtColor(pOriFrame,grayFrame,CV_BGR2GRAY);
		//cvSaveImage(frameNoPath,grayFrame);
		//cvSaveImage(frameNoPath,pOriFrame);
		simpleFrameList.push_back(cvCloneImage(pOriFrame));
		extractFrameNum++;
		nFrmNum += perFrameFromframeNum;
	}
	simpleFrameNum = extractFrameNum;
	if(pCapture!=NULL){
		cvReleaseCapture(&pCapture);
	}
	return 0;
	//return extractFrameNum;
}

void KeyframeExtraction::hsvHistExtraction(){
	//CString framePath = "F:\\database\\frames\\%d.bmp";
	//CString keyFramePath = "F:\\database\\keyframes\\%d.bmp";
	int keyFrameNo = 0;

	IplImage *frame1 = NULL;          ///
	IplImage *frame2 = NULL;          ///
	IplImage *frame3 = NULL;//交换时使用

	//CString frameNoPath;    
	//string frameNoPath;
	//
	//frameNoPath.Format(framePath,frameNo);
	/*if(!(frame1 = cvLoadImage(frameNoPath,CV_LOAD_IMAGE_COLOR))){
	cout<< frameNoPath <<" can't open "<<endl;
	return;
	}*/
	//CString keyframeNoPath;
	//keyframeNoPath.Format(keyFramePath,keyFrameNo);
	//keyFrameNo++;
	//cvSaveImage(keyframeNoPath,frame1);
	int frameNo = 0;
	frame1 = simpleFrameList.at(frameNo);
	IplImage* hsvframe = cvCreateImage( cvGetSize(frame1), 8, 3 );//用于存放HSV
	IplImage* hFrame = cvCreateImage( cvGetSize(frame1), 8, 1 );
	IplImage* sFrame = cvCreateImage( cvGetSize(frame1), 8, 1 );
	IplImage* vFrame = cvCreateImage( cvGetSize(frame1), 8, 1 );
	IplImage* planes[] = { hFrame, sFrame,vFrame};
	/** H 分量划分为16个等级，S分量划分为8个等级 */
	int hBins = 32, sBins = 16,vBins = 20;
	int histSize[] = {hBins, sBins,vBins};
	/** H 分量的变化范围 */
	float hRange[] = { 0, 180 }; 
	/** S 分量的变化范围*/
	float sRange[] = { 0, 255 };
	float vRange[] = {0.0, 1.0};
	//float* HSVRanges[] = { hRange, sRange, vRange};
	float* hRanges[]={hRange};
	float* sRanges[]={sRange};
	float* vRanges[] = {vRange};
	//CvHistogram * hist1 = cvCreateHist( 3, hist_size, CV_HIST_ARRAY, ranges, 1 );
	//CvHistogram * hist2 = cvCreateHist( 3, hist_size, CV_HIST_ARRAY, ranges, 1 );
	CvHistogram *hHist1 = cvCreateHist( 1, &hBins, CV_HIST_ARRAY, hRanges, 1 );
	CvHistogram *sHist1 = cvCreateHist( 1, &sBins, CV_HIST_ARRAY, sRanges, 1 );
	CvHistogram *vHist1 = cvCreateHist( 1, &vBins, CV_HIST_ARRAY, vRanges, 1 );
	CvHistogram *hHist2 = cvCreateHist( 1, &hBins, CV_HIST_ARRAY, hRanges, 1 );
	CvHistogram *sHist2 = cvCreateHist( 1, &sBins, CV_HIST_ARRAY, sRanges, 1 );
	CvHistogram *vHist2 = cvCreateHist( 1, &vBins, CV_HIST_ARRAY, vRanges, 1 );
	/** 输入图像转换到HSV颜色空间 */
	cvCvtColor( frame1, hsvframe, CV_BGR2HSV );
	cvCvtPixToPlane( hsvframe, hFrame, sFrame, vFrame, 0 );//分割多通道数组成几个单通道数组或者从数组中提取一个通道

	//cvCalcHist( planes, hist1, 0, 0 );
	cvCalcHist(&hFrame,hHist1,0,0);
	cvCalcHist(&sFrame,sHist1,0,0);
	cvCalcHist(&vFrame,vHist1,0,0);

	//hsvframe = NULL;
	//int frameNo = 0;
	frame2 = simpleFrameList.at(frameNo);
	keyframeList.push_back(cvCloneImage(frame2));
	for(frameNo=1;frameNo<simpleFrameNum;frameNo++)
	{
		//CString frameNoPath;
		/*frameNoPath.Format(framePath,frameNo);
		if(!(frame2 = cvLoadImage(frameNoPath,CV_LOAD_IMAGE_COLOR))){
			cout<< frameNoPath <<" can't open "<<endl;
			return;
		}*/
		frame2 = simpleFrameList.at(frameNo);
		cvCvtColor( frame2, hsvframe, CV_BGR2HSV );
		cvCvtPixToPlane( hsvframe, hFrame, sFrame, vFrame, 0 );
		//cvCalcHist(planes,hist2,0,0);
		cvCalcHist(&hFrame,hHist2,0,0);
		cvCalcHist(&sFrame,sHist2,0,0);
		cvCalcHist(&vFrame,vHist2,0,0);

		float hRatio = cvCompareHist(hHist1,hHist2,CV_COMP_CORREL);
		float sRatio = cvCompareHist(sHist1,sHist2,CV_COMP_CORREL);
		float vRatio = cvCompareHist(sHist1,sHist2,CV_COMP_CORREL);
		float ratio =( hRatio+sRatio+vRatio)/3.0;
		if(ratio < RATIO_T){
			/*CString keyframeNoPath;
			keyframeNoPath.Format(keyFramePath,keyFrameNo);
			keyFrameNo++;
			cvSaveImage(keyframeNoPath,frame2);*/
			//IplImage* tempImg = cvCloneImage(frame2);
			keyframeList.push_back(cvCloneImage(frame2));
		}
		cvCopyHist(hHist2,&hHist1);
		cvCopyHist(sHist2,&sHist1);
		cvCopyHist(vHist2,&vHist1);
	}
	if(frame1!=NULL){
		cvReleaseImage(&frame1);
	}
	if(frame2!=NULL){
		cvReleaseImage(&frame2);
	}
	if (hsvframe!=NULL){
		cvReleaseImage(&hsvframe);
	}
	if (hFrame!=NULL){
		cvReleaseImage(&hFrame);
	}
	if (sFrame!=NULL){
		cvReleaseImage(&sFrame);
	}
	if (vFrame!=NULL){
		cvReleaseImage(&vFrame);
	}
	if(hHist1!=NULL){
		cvReleaseHist(&hHist1);
	}
	if(sHist1!=NULL){
		cvReleaseHist(&sHist1);
	}
	if(vHist1!=NULL){
		cvReleaseHist(&vHist1);
	}
	if(hHist2!=NULL){
		cvReleaseHist(&hHist2);
	}
	if(sHist2!=NULL){
		cvReleaseHist(&sHist2);
	}
	if(vHist2!=NULL){
		cvReleaseHist(&vHist2);
	}
}
vector<IplImage*> KeyframeExtraction::getKeyframeList(){
	return keyframeList;
}
