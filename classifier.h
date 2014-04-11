#ifndef _CLASSIFIER_H
#define _CLASSIFIER_H

#pragma warning(disable: 4786)  //Ԥ��warning ̫�ࡣ������
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <io.h>
#include <windows.h>
#include <fcntl.h>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <cmath>
#include "ICTCLAS50.h"
#pragma comment(lib, "ICTCLAS50.lib") //ICTCLAS50.lib����뵽������

using namespace std;

//���������Ҫ��ɶ��ı��ķִʣ�Ȼ���γ��ֵ�myDic.txt;
void testICTCLAS_ParagraphProcess(string folderPath,int folderId);
int isNotChinese(string str);//�Ƿ�����Ǻ���
int myParagraphProcess(string folderPath,string myDicPath,string myTFDicPath);

void chiFeatureSelect(string dicPath);//������������ѡȡ
void expectedCrossEntrophyFeatureSelect(string dicPath);//����������

//�ı�������
int myParagraphProcessToVSM(string folderPath,string desPath);
void testICTCLAS_ParagraphProcessToVSM(string folderPath,int folderId);

int myTextToVSMforNaiveBayes(string folderPath,string desPath);
void testICTCLAS_VSMforNaiveBayes(string folderPath,int folderId);

//�����㷨
void KNN(string trainFilePath,string testFilePath);
void naiveBayes(string naiveBayesTestVSM);

//���۷���
void evaluateResult(int artNum[],int P[],int n);


#endif