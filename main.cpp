/******************************************************************************* 

*******************************************************************************/

#ifndef OS_LINUX
#include <Windows.h>
#endif

#include <time.h>
#include "classifier.h"

//训练集和测试集
string textTrainDataPath = "E:\\finalData\\1_train";
string textTestDataPath = "E:\\finalData\\2_answer";

//无用了
string VSMDesPath = "E:\\final\\final\\myData\\VSM.txt";
string VSMtestDesPath = "E:\\final\\final\\myData\\VSMtest.txt";

//文本向量化的(稀疏)表示,一个是基于CHI选出来的特征项，另一个是基于ECE

string VSMDesPathMatrix = "E:\\final\\final\\myData\\VSMMatrix.txt";
string VSMtestDesPathMatrix = "E:\\final\\final\\myData\\VSMtestMatrix.txt";
string VSMDesPathMatrixOnCross = "E:\\final\\final\\myData\\VSMMatrixOnCross.txt";
string VSMtestDesPathMatrixOnCross = "E:\\final\\final\\myData\\VSMtestMatrixOnCross.txt";
/******************************************为KNN准备******************************************************/
string textOfTrainVSMOnCHI = "E:\\final\\final\\myData\\textOfTrainVSMOnCHI.txt";//训练集向量化(CHI)
string textOfTestVSMOnCHI = "E:\\final\\final\\myData\\textOfTestVSMOnCHI.txt";//测试集向量化(CHI)

string textOfTrainVSMOnCross = "E:\\final\\final\\myData\\textOfTrainVSMOnCross.txt";//训练集向量化(ECE)
string textOfTestVSMOnCross = "E:\\final\\final\\myData\\textOfTestVSMOnCross.txt";//测试集向量化(ECE)

/********************************************为贝叶斯准备*************************************************/
string naiveBayesOfTestVSMOnCHI = "E:\\final\\final\\myData\\naiveBayesOfTestVSMOnCHI.txt";
string naiveBayesOfTestVSMOnCross = "E:\\final\\final\\myData\\naiveBayesOfTestVSMOnCross.txt";
/**********************************************保存一些中间结果*******************************************/
//保存语料库词典的路径,统计文档频率DF
string myDicPath = "E:\\final\\final\\myData\\myDic.txt";
//预料词典的路径，统计词频TF——(用于Bayes)
string myTFDicPath = "E:\\final\\final\\myData\\myTFDic.txt";

//用于期望交叉熵特征选择
#define _CROSS

#ifndef _CROSS
string featureDicPath = "E:\\final\\final\\myData\\featureDic.txt";
#else
string featureDicPath = "E:\\final\\final\\myData\\crossfeatureDic.txt";
#endif


extern int artNum[8];
extern int P[8];
int main()
{
	clock_t start,finish;
	time_t tStart,tFinish;
	double totaltime;
	tStart = time(&tStart);
	start = clock();
	
	//将训练集下的文本分词后，保存为myDic.txt(DF词典)和myTFDic(TF词典)
    //myParagraphProcess("E:\\finalData\\1_train",myDicPath,myTFDicPath);

	//卡方检验特征选择
	//chiFeatureSelect(myDicPath);
	//期望交叉熵特征选择——从词频词典中选取
	//expectedCrossEntrophyFeatureSelect(myTFDicPath);

	 /*myParagraphProcessToVSM(textTrainDataPath,VSMDesPath);
	myParagraphProcessToVSM(textTestDataPath,VSMtestDesPath);*/

	//基于CHI特征向量将训练和测试文本向量化——记得 去掉 宏定义_CROSS
	//myParagraphProcessToVSM(textTrainDataPath,textOfTrainVSMOnCHI);
	//myParagraphProcessToVSM(textTestDataPath,textOfTestVSMOnCHI);

	//基于ECE特征向量将训练和测试文本向量化——记得 加上 宏定义_CROSS
	//myParagraphProcessToVSM(textTrainDataPath,textOfTrainVSMOnCross);
	//myParagraphProcessToVSM(textTestDataPath,textOfTestVSMOnCross);

	//基于CHI特征向量将训练和测试文本向量化(Bayes)——记得 去掉 宏定义_CROSS
	//myTextToVSMforNaiveBayes(textTestDataPath,naiveBayesOfTestVSMOnCHI);
	//基于ECE特征向量将训练和测试文本向量化(Bayes)——记得 加上 宏定义_CROSS
	//myTextToVSMforNaiveBayes(textTestDataPath,naiveBayesOfTestVSMOnCross);


	//基于CHI特征向量的KNN分类——记得 去掉 宏定义_CROSS
	//KNN(textOfTrainVSMOnCHI,textOfTestVSMOnCHI);
	//基于ECE特征向量的KNN分类——记得 加上 宏定义_CROSS
	//KNN(textOfTrainVSMOnCross,textOfTestVSMOnCross);

	//基于CHI特征向量的NB分类——记得 去掉 宏定义_CROSS
	//naiveBayes(naiveBayesOfTestVSMOnCHI);
	//基于ECE特征向量的NB分类——记得 加上 宏定义_CROSS
	naiveBayes(naiveBayesOfTestVSMOnCross);

	evaluateResult(artNum,P,8);
	
	 


	 finish = clock();
	 tFinish = time(&tFinish);
	 totaltime = (finish - start) / CLOCKS_PER_SEC;
	 cout<<totaltime-(totaltime/60)*60<<"秒   "<<"运行时间："<<tFinish - tStart<<endl;

	return 0;
}


