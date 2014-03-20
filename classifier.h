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
int myParagraphProcess(string folderPath);
void testICTCLAS_ParagraphProcess(string folderPath,int folderId);
int isNotChinese(string str);//�Ƿ�����Ǻ���

void chiFeatureSelect();//������������ѡȡ

//�ı�������
int myParagraphProcessToVSM(string folderPath,string desPath);
void testICTCLAS_ParagraphProcessToVSM(string folderPath,int folderId);

//�����㷨
void KNN();


#endif