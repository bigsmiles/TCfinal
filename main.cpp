/******************************************************************************* 

*******************************************************************************/

#ifndef OS_LINUX
#include <Windows.h>
#endif

#include <time.h>
#include "classifier.h"

string textDataPath = "E:\\finalData\\1_train";
string textDataPath2 = "E:\\finalData\\2_answer";

string VSMDesPath = "E:\\final\\final\\myData\\VSM.txt";
string VSMtestDesPath = "E:\\final\\final\\myData\\VSMtest.txt";

extern int artNum[8];
extern int P[8];
int main()
{
	clock_t start,finish;
	time_t tStart,tFinish;
	double totaltime;
	tStart = time(&tStart);
	start = clock();
	
    //myParagraphProcess("E:\\finalData\\1_train");//将目录下的文本分词后，保存为myDic.txt
	//chiFeatureSelect();
	// myParagraphProcessToVSM(textDataPath,VSMDesPath);
	 //myParagraphProcessToVSM(textDataPath2,VSMtestDesPath);

	 KNN();
	 evaluateResult(artNum,P,8);

	 finish = clock();
	 tFinish = time(&tFinish);
	 totaltime = (finish - start) / CLOCKS_PER_SEC;
	 cout<<totaltime-(totaltime/60)*60<<"秒   "<<"运行时间："<<tFinish - tStart<<endl;

	return 0;
}


