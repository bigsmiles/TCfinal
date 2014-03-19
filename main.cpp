/******************************************************************************* 

*******************************************************************************/

#ifndef OS_LINUX
#include <Windows.h>
#endif

#include "classifier.h"

string textDataPath = "E:\\finalData\\1_train";
string textDataPath2 = "E:\\finalData\\2_answer";
int main()
{
    myParagraphProcess("E:\\finalData\\1_train");//将目录下的文本分词后，保存为myDic.txt
	//chiFeatureSelect();
	 //myParagraphProcessToVSM(textDataPath,VSMPath);
	 //myParagraphProcessToVSM(textDataPath);
	//myParagraphProcessToVSM(textDataPath2);
	 //KNN();

	return 0;
}


