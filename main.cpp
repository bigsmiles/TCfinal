/******************************************************************************* 

*******************************************************************************/

#ifndef OS_LINUX
#include <Windows.h>
#endif

#include <time.h>
#include "classifier.h"

//ѵ�����Ͳ��Լ�
string textTrainDataPath = "E:\\finalData\\1_train";
string textTestDataPath = "E:\\finalData\\2_answer";

//������
string VSMDesPath = "E:\\final\\final\\myData\\VSM.txt";
string VSMtestDesPath = "E:\\final\\final\\myData\\VSMtest.txt";

//�ı���������(ϡ��)��ʾ,һ���ǻ���CHIѡ�������������һ���ǻ���ECE

string VSMDesPathMatrix = "E:\\final\\final\\myData\\VSMMatrix.txt";
string VSMtestDesPathMatrix = "E:\\final\\final\\myData\\VSMtestMatrix.txt";
string VSMDesPathMatrixOnCross = "E:\\final\\final\\myData\\VSMMatrixOnCross.txt";
string VSMtestDesPathMatrixOnCross = "E:\\final\\final\\myData\\VSMtestMatrixOnCross.txt";
/******************************************ΪKNN׼��******************************************************/
string textOfTrainVSMOnCHI = "E:\\final\\final\\myData\\textOfTrainVSMOnCHI.txt";//ѵ����������(CHI)
string textOfTestVSMOnCHI = "E:\\final\\final\\myData\\textOfTestVSMOnCHI.txt";//���Լ�������(CHI)

string textOfTrainVSMOnCross = "E:\\final\\final\\myData\\textOfTrainVSMOnCross.txt";//ѵ����������(ECE)
string textOfTestVSMOnCross = "E:\\final\\final\\myData\\textOfTestVSMOnCross.txt";//���Լ�������(ECE)

/********************************************Ϊ��Ҷ˹׼��*************************************************/
string naiveBayesOfTestVSMOnCHI = "E:\\final\\final\\myData\\naiveBayesOfTestVSMOnCHI.txt";
string naiveBayesOfTestVSMOnCross = "E:\\final\\final\\myData\\naiveBayesOfTestVSMOnCross.txt";
/**********************************************����һЩ�м���*******************************************/
//�������Ͽ�ʵ��·��,ͳ���ĵ�Ƶ��DF
string myDicPath = "E:\\final\\final\\myData\\myDic.txt";
//Ԥ�ϴʵ��·����ͳ�ƴ�ƵTF����(����Bayes)
string myTFDicPath = "E:\\final\\final\\myData\\myTFDic.txt";

//������������������ѡ��
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
	
	//��ѵ�����µ��ı��ִʺ󣬱���ΪmyDic.txt(DF�ʵ�)��myTFDic(TF�ʵ�)
    //myParagraphProcess("E:\\finalData\\1_train",myDicPath,myTFDicPath);

	//������������ѡ��
	//chiFeatureSelect(myDicPath);
	//��������������ѡ�񡪡��Ӵ�Ƶ�ʵ���ѡȡ
	//expectedCrossEntrophyFeatureSelect(myTFDicPath);

	 /*myParagraphProcessToVSM(textTrainDataPath,VSMDesPath);
	myParagraphProcessToVSM(textTestDataPath,VSMtestDesPath);*/

	//����CHI����������ѵ���Ͳ����ı������������ǵ� ȥ�� �궨��_CROSS
	//myParagraphProcessToVSM(textTrainDataPath,textOfTrainVSMOnCHI);
	//myParagraphProcessToVSM(textTestDataPath,textOfTestVSMOnCHI);

	//����ECE����������ѵ���Ͳ����ı������������ǵ� ���� �궨��_CROSS
	//myParagraphProcessToVSM(textTrainDataPath,textOfTrainVSMOnCross);
	//myParagraphProcessToVSM(textTestDataPath,textOfTestVSMOnCross);

	//����CHI����������ѵ���Ͳ����ı�������(Bayes)�����ǵ� ȥ�� �궨��_CROSS
	//myTextToVSMforNaiveBayes(textTestDataPath,naiveBayesOfTestVSMOnCHI);
	//����ECE����������ѵ���Ͳ����ı�������(Bayes)�����ǵ� ���� �궨��_CROSS
	//myTextToVSMforNaiveBayes(textTestDataPath,naiveBayesOfTestVSMOnCross);


	//����CHI����������KNN���ࡪ���ǵ� ȥ�� �궨��_CROSS
	//KNN(textOfTrainVSMOnCHI,textOfTestVSMOnCHI);
	//����ECE����������KNN���ࡪ���ǵ� ���� �궨��_CROSS
	//KNN(textOfTrainVSMOnCross,textOfTestVSMOnCross);

	//����CHI����������NB���ࡪ���ǵ� ȥ�� �궨��_CROSS
	//naiveBayes(naiveBayesOfTestVSMOnCHI);
	//����ECE����������NB���ࡪ���ǵ� ���� �궨��_CROSS
	naiveBayes(naiveBayesOfTestVSMOnCross);

	evaluateResult(artNum,P,8);
	
	 


	 finish = clock();
	 tFinish = time(&tFinish);
	 totaltime = (finish - start) / CLOCKS_PER_SEC;
	 cout<<totaltime-(totaltime/60)*60<<"��   "<<"����ʱ�䣺"<<tFinish - tStart<<endl;

	return 0;
}


