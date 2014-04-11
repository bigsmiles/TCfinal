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

string VSMDesPathMatrix = "E:\\final\\final\\myData\\VSMMatrix.txt";
string VSMtestDesPathMatrix = "E:\\final\\final\\myData\\VSMtestMatrix.txt";
string VSMDesPathMatrixOnCross = "E:\\final\\final\\myData\\VSMMatrixOnCross.txt";
string VSMtestDesPathMatrixOnCross = "E:\\final\\final\\myData\\VSMtestMatrixOnCross.txt";

string naiveBayesDesPathMatrix = "E:\\final\\final\\myData\\testBayesMatrix.txt";
string naiveBayesDesPathMatrixOnCross = "E:\\final\\final\\myData\\testBayesMatrixOnCross.txt";
extern int artNum[8];
extern int P[8];
#define _CROSS

#ifndef _CROSS
string featureDicPath = "E:\\final\\final\\myData\\featureDic.txt";
#else
string featureDicPath = "E:\\final\\final\\myData\\crossfeatureDic.txt";
#endif

int main()
{
	clock_t start,finish;
	time_t tStart,tFinish;
	double totaltime;
	tStart = time(&tStart);
	start = clock();
	
    //myParagraphProcess("E:\\finalData\\1_train");//将目录下的文本分词后，保存为myDic.txt
	//chiFeatureSelect();
	//expectedCrossEntrophyFeatureSelect();//期望交叉熵

	// myParagraphProcessToVSM(textDataPath,VSMDesPath);
	 //myParagraphProcessToVSM(textDataPath2,VSMtestDesPath);

	//myParagraphProcessToVSM(textDataPath,VSMDesPathMatrix);
	//myParagraphProcessToVSM(textDataPath2,VSMtestDesPathMatrix);
	//myParagraphProcessToVSM(textDataPath,VSMDesPathMatrixOnCross);
	//myParagraphProcessToVSM(textDataPath2,VSMtestDesPathMatrixOnCross);

	//myTextToVSMforNaiveBayes(textDataPath2,naiveBayesDesPathMatrix);
	//myTextToVSMforNaiveBayes(textDataPath2,naiveBayesDesPathMatrixOnCross);

	 KNN();
	 evaluateResult(artNum,P,8);
	
	 //naiveBayes();
	 //evaluateResult(artNum,P,8);


	 finish = clock();
	 tFinish = time(&tFinish);
	 totaltime = (finish - start) / CLOCKS_PER_SEC;
	 cout<<totaltime-(totaltime/60)*60<<"秒   "<<"运行时间："<<tFinish - tStart<<endl;

	return 0;
}


