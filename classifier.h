#ifndef _CLASSIFIER_H
#define _CLASSIFIER_H

#pragma warning(disable: 4786)  //预防warning 太多。。。。
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
#pragma comment(lib, "ICTCLAS50.lib") //ICTCLAS50.lib库加入到工程中

using namespace std;

//这个两个主要完成对文本的分词，然后形成字典myDic.txt;
void testICTCLAS_ParagraphProcess(string folderPath,int folderId);
int isNotChinese(string str);//是否包含非汉字
int myParagraphProcess(string folderPath,string myDicPath,string myTFDicPath);

void chiFeatureSelect(string dicPath);//卡方检验特征选取
void expectedCrossEntrophyFeatureSelect(string dicPath);//期望交叉熵

//文本向量化
int myParagraphProcessToVSM(string folderPath,string desPath);
void testICTCLAS_ParagraphProcessToVSM(string folderPath,int folderId);

int myTextToVSMforNaiveBayes(string folderPath,string desPath);
void testICTCLAS_VSMforNaiveBayes(string folderPath,int folderId);

//分类算法
void KNN(string trainFilePath,string testFilePath);
void naiveBayes(string naiveBayesTestVSM);

//评价分类
void evaluateResult(int artNum[],int P[],int n);


#endif