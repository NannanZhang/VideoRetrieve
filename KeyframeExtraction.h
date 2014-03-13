#include "PublicHeaders.h"
#include <vector>
using namespace std;
class KeyframeExtraction{
public:
	KeyframeExtraction();
	~KeyframeExtraction();
private:
	float RATIO_T;

	char* videoPath;
	int simpleFrameNum;
	int extractionType;
	vector<IplImage*> simpleFrameList;
	vector<IplImage*> keyframeList;
public:
	void init(char *videoPath);
	int simpleExtraction();
	void grayHistExtraction();
	void hsvHistExtraction();

	vector<IplImage*> getKeyframeList();

};
