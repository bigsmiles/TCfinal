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
    myParagraphProcess("E:\\finalData\\1_train");//��Ŀ¼�µ��ı��ִʺ󣬱���ΪmyDic.txt
	//chiFeatureSelect();
	 //myParagraphProcessToVSM(textDataPath,VSMPath);
	 //myParagraphProcessToVSM(textDataPath);
	//myParagraphProcessToVSM(textDataPath2);
	 //KNN();

	return 0;
}


