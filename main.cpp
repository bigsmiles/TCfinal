/******************************************************************************* 

*******************************************************************************/

#ifndef OS_LINUX
#include <Windows.h>
#endif

#include "classifier.h"

string textDataPath = "E:\\finalData\\1_train";
string textDataPath2 = "E:\\finalData\\2_answer";

string VSMDesPath = "E:\\final\\final\\myData\\VSM.txt";
string VSMtestDesPath = "E:\\final\\final\\myData\\VSMtest.txt";
int main()
{
    //myParagraphProcess("E:\\finalData\\1_train");//将目录下的文本分词后，保存为myDic.txt
	//chiFeatureSelect();
	// myParagraphProcessToVSM(textDataPath,VSMDesPath);
	 //myParagraphProcessToVSM(textDataPath2,VSMtestDesPath);
	 KNN();

	return 0;
}


