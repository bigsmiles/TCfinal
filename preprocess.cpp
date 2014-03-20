#include "classifier.h"

#define POS_TAGGER_TEST
#ifdef POS_TAGGER_TEST
bool g_bPOSTagged=true;
#else
bool g_bPOSTagged=false;
#endif	
string stopWordsPath = "E:\\final\\final\\myData\\stopwords.txt"; //记录停用词词典的路径
string myDicPath = "E:\\final\\final\\myData\\myDic.txt"; //语料库词典的路径
map<string,map<int,int> >myDic; 
/*
词典格式：如，计算机
计算机
0 3 1 3 4 5 9 8
表示有三个数对,第1类别中出现"计算机"的文档频数(DF)是3
第4类别中出现"计算机"的DF是 5
第9类别就是 "计算机"在语料库的总DF
*/
set<string>stopDic;	//停用词词典

ofstream badWordsFile("E:\\final\\final\\myData\\badwords.txt");
map<string,int> badWords;

int isNotChinese(string str)
{
	int codeHigh = 0x9fa0;
	int codeLow = 0x4e00;//unicode中汉字的范围
	int iWLen=MultiByteToWideChar( CP_ACP, 0, str.c_str(), str.size(), 0, 0 );// 计算转换后宽字符串的长度。（不包含字符串结束符）
    wchar_t *wstr= new wchar_t [iWLen+1];
    MultiByteToWideChar( CP_ACP, 0, str.c_str(), str.size(), wstr, iWLen ); // 正式转换。
    wstr[iWLen] = L'\0'; 
	for(int i = 0; i < iWLen;i++)
	{
            if(wstr[i] < codeLow || wstr[i] > codeHigh)
			{
				return 0;//字符串中含有非汉字符号
			}
	}
	return 1;
}
void testICTCLAS_ParagraphProcess(string folderPath,int folderId)  //path开始路径
{

	long Handle;
	struct _finddata_t FileInfo;

	string fpath = folderPath + "\\*";
	if((Handle = _findfirst(fpath.c_str(),&FileInfo)) == -1L)  //遍历目录下的文件
	{
		printf("没有找到匹配的项目");
		exit(-1);
	}

	do{
			//判断是否有子目录
			if (FileInfo.attrib & _A_SUBDIR)    
			{
				 //这个语句很重要
				if( (strcmp(FileInfo.name,".") != 0 ) &&(strcmp(FileInfo.name,"..") != 0))   
				{
					string newPath = folderPath + "\\" + FileInfo.name;
					cout<<"目录名"<<newPath<<endl; 
					testICTCLAS_ParagraphProcess(newPath,folderId+1);
					folderId += 1;
				}
			}
			else  
			{
				char* sSentence =  (char*)malloc(FileInfo.size);
				char ch;
				int len = 0;
				string filepath = folderPath + "\\" + FileInfo.name;
				ifstream ifile(filepath.c_str());

				while(ifile>>ch)	//这样读入为了将换行符去掉，ASCII码10、13
				{
					 if(ch == '\n' || ch == '\r')
						 continue;
					 sSentence[len++] = ch;
				}
		
				sSentence[len] = '\0';
				unsigned int nPaLen=strlen(sSentence); // 需要分词的长度
				char* sRst=0;   //用户自行分配空间，用于保存结果；
				sRst=(char *)malloc(nPaLen*6); //建议长度为字符串长度的倍。
				int nRstLen=0; //分词结果的长度
			
				nRstLen = ICTCLAS_ParagraphProcess(sSentence,nPaLen,sRst,CODE_TYPE_UNKNOWN,0);  //字符串处理
				/*收集单词，形成字典*/
			
			
				//cout<<"目录为："<<folderId<<endl;
				string words;
				istringstream istream(sRst);
				set<string> txtDic; //表示一篇文章的词典,为了统计词的文档频率DF
				while(istream>>words)
				{
					if(!isNotChinese(words))
					{
						badWords[words]++;
						continue;
					}

					if((!txtDic.count(words)) && (!stopDic.count(words)))
					{
						++myDic[words][9];
						++myDic[words][folderId];
						txtDic.insert(words);
					}
				}
				free(sRst);
				txtDic.clear();

				/*int rstCount=0;

				LPICTCLAS_RESULT rstVec=ICTCLAS_ParagraphProcessA(sSentence,nPaLen,rstCount,CODE_TYPE_UNKNOWN,g_bPOSTagged);
														//字符串处理
				string str = sSentence;
				string words;
				set<string> txtDic;
				for (int i=0;i< rstCount;i++)
				{//打印分词结果
					words = str.substr(rstVec[i].iStartPos,rstVec[i].iLength);
					if(rstVec[i].iPOS == 93 || rstVec[i].iPOS == 18 || rstVec[i].iPOS == 52) //非语素(英文等)和数词和年月
					{
						badWords<<words<<" "<<rstVec[i].iPOS<<endl;
					}
					if(!txtDic.count(words) && !stopDic.count(words))
					{
						++myDic[words][9];
						++myDic[words][folderId];
						txtDic.insert(words);
					}
					
				}
				ICTCLAS_ResultFree(rstVec);	//调用接口释放内存*/
				
			}
	
    }while (_findnext(Handle, &FileInfo) == 0);

	_findclose(Handle);
	return ;  
}

int myParagraphProcess(string folderPath)
{
	if(!ICTCLAS_Init()) //初始化分词组件。
	{
		printf("Init fails\n");  
		return 0;
	}
	else
	{
		printf("Init ok\n");
	}

	ifstream stopDicFile(stopWordsPath.c_str());//E:\final\final\myData\stopwords.txt
	ofstream ofile(myDicPath.c_str());	//E:\final\final\myData\myDic.txt

	string stopWord;
	while(stopDicFile>>stopWord)
		stopDic.insert(stopWord);

   //设置词性标注集(0 计算所二级标注集，1 计算所一级标注集，2 北大二级标注集，3 北大一级标注集)
	ICTCLAS_SetPOSmap(2);
    testICTCLAS_ParagraphProcess(folderPath,0);//分词用例
	ICTCLAS_Exit();	//释放资源退出
	

	int dic_num = 0;
	int flag = 0;  //第0对,表示数组的大小
	for(map<string,map<int,int> >::iterator mapItor = myDic.begin(); mapItor != myDic.end(); mapItor++)
	{
		ofile<<mapItor->first<<endl;
		ofile<<flag<<" "<<mapItor->second.size();
		dic_num++;
		for(map<int,int>::iterator itor = mapItor->second.begin(); itor != mapItor->second.end(); itor++)
		{
			ofile<<" "<<itor->first<<" "<<itor->second;
		}
		ofile<<endl;
	}
	printf("\n共出现词：%d\n",dic_num);
	for(map<string,int>::iterator itor = badWords.begin(); itor != badWords.end(); itor++)
		badWordsFile<<itor->first<<endl;


	myDic.clear(); //已经保存在硬盘了，可以清空了吧？
	badWords.clear();
	stopDicFile.close();
	ofile.close();
	return 1;
}