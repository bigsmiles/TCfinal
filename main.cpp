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
    //myParagraphProcess("E:\\finalData\\1_train");//��Ŀ¼�µ��ı��ִʺ󣬱���ΪmyDic.txt
	//chiFeatureSelect();
	// myParagraphProcessToVSM(textDataPath,VSMDesPath);
	 //myParagraphProcessToVSM(textDataPath2,VSMtestDesPath);
	 KNN();

	return 0;
}


