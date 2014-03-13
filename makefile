OBJS = util.o  CEDDQuant.o Fuzzy10Bin.o Fuzzy24Bin.o CompactCEDDQuant.o RGB2HSV.o CEDDFeature.o  KeyframeExtraction.o LSHRetrieve.o Main.o 
LIBS = /usr/local/lib/libopencv_video.so  /usr/local/lib/libopencv_core.so  /usr/local/lib/libopencv_core.so.2.4  /usr/local/lib/libopencv_highgui.so /usr/local/lib/libopencv_imgproc.so
INCLUDE = -lm -I/usr/local/include -I/usr/local/include/opencv -I/usr/local/include/opencv2

Main:${OBJS}
	gcc -g -o Main  ${LIBS} ${OBJS} ${INCLUDE}
util.o:./CEDD/util.cpp
	gcc -g -c ./CEDD/util.cpp
CEDDQuant.o:./CEDD/CEDDQuant.cpp
	gcc -g -c ./CEDD/CEDDQuant.cpp 
Fuzzy10Bin.o:./CEDD/Fuzzy10Bin.cpp
	gcc -g -c ./CEDD/Fuzzy10Bin.cpp 
Fuzzy24Bin.o:./CEDD/Fuzzy24Bin.cpp
	gcc -g -c ./CEDD/Fuzzy24Bin.cpp
CompactCEDDQuant.o:./CEDD/CompactCEDDQuant.cpp
	gcc -g -c ./CEDD/CompactCEDDQuant.cpp
RGB2HSV.o:./CEDD/RGB2HSV.cpp
	gcc -g -c ./CEDD/RGB2HSV.cpp
CEDDFeature.o:./CEDD/CEDDFeature.cpp
	gcc -g -c ./CEDD/CEDDFeature.cpp
#utils.o:utils.cpp
#	gcc -c utils.cpp
KeyframeExtraction.o:KeyframeExtraction.cpp
	gcc -g -c KeyframeExtraction.cpp 
LSHRetrieve.o:LSHRetrieve.cpp
	gcc -g -c LSHRetrieve.cpp -Wno-deprecated
Main.o:Main.cpp
	gcc -g -c Main.cpp -Wno-deprecated

clean:
	rm *.o
