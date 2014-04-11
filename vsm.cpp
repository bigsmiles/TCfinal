#include "classifier.h"


typedef std::map<string, vector<pair<int,double> > > STRING2VECTOR;
typedef std::map<string, vector<pair<int,int> > > STRING2VECTORBAYES;

extern string myDicPath;
extern string featureDicPath;
extern string myTFDicPath;

map<string,int>IDFDic; //只提取字典中IDF(即最后那对值)的字典
set<string> featureDic;//特征词词词典,没有特征词的权值，区别于myFeatureDic
map<string,vector<pair<int,double> > > txtVSM;
map<string,vector<pair<int,int> > >naiveBayesVSM;
double total = 3903;


void testICTCLAS_ParagraphProcessToSVM(string folderPath,int folderId)  //path开始路径
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
                testICTCLAS_ParagraphProcessToSVM(newPath,folderId+1);
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
				double TF;
				int id;
				//int txtCnt;//文章总词数
				string words;
				istringstream istream(sRst);
				map<string,int>txt;
				vector<pair<int,double> > tmpVSM;
				set<string> txtWords;
				while(istream>>words)
				{
					txtWords.insert(words);
					if(featureDic.count(words))
					{
						txt[words]++;
					}
				}
				//outFile<<FileInfo.name<<endl;
				id = 0;
				for(set<string>::iterator setItor = featureDic.begin(); setItor != featureDic.end(); setItor++)
				{
				
					TF = (1.0*txt[(*setItor)]) / txtWords.size();
					TF *= log(0.01 + total/IDFDic[(*setItor)]);
					if(TF != 0)
					{
						tmpVSM.push_back(make_pair(id,TF));
					}
					id++;
					//outFile<<TF<<" ";
				
				}
				//outFile<<endl;
				txtVSM.insert(STRING2VECTOR::value_type(FileInfo.name,tmpVSM));
				tmpVSM.clear();
				//txtWords.clear();

		 free(sRst);
        }
	
    }while (_findnext(Handle, &FileInfo) == 0);

		_findclose(Handle);
  
	return ;  
}

int myParagraphProcessToVSM(string folderPath,string desPath)
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
	
	ifstream featureDicFile(featureDicPath.c_str());
	ifstream dicFile(myDicPath.c_str());

	string featureWord;
	double featureVal;
	string term;
	int id,cnt,df,i;

	while(featureDicFile>>featureWord>>featureVal)
		featureDic.insert(featureWord);
	cout<<featureDicPath<<endl;

	while(dicFile>>term)
	{
		
		dicFile>>id>>cnt;
		for(i = 0; i < cnt; i++)
		{
			dicFile>>id>>df;
		}
		if(featureDic.count(term))
			IDFDic[term] = df;
	}
	//for(map<string,int>::iterator it = IDFDic.begin(); it != IDFDic.end(); it++)
		//cout<<it->first<<" "<<it->second<<endl;
   //设置词性标注集(0 计算所二级标注集，1 计算所一级标注集，2 北大二级标注集，3 北大一级标注集)
	ICTCLAS_SetPOSmap(2);

    testICTCLAS_ParagraphProcessToSVM(folderPath,0);//分词用例
	
	ICTCLAS_Exit();	//释放资源退出
	ofstream outFile(desPath.c_str());
	//ofstream outFile(VSMtestPath.c_str());
	/*for(map<string,vector<double> > ::iterator txtItor = txtVSM.begin(); txtItor != txtVSM.end(); txtItor++)
	{

		outFile<<txtItor->first<<endl;
		for(i = 0; i < 1000; i++)
		{
			outFile<<txtItor->second[i]<<" ";
		}
		outFile<<endl;
	}
	*/
	/*for(map<string,vector<double> >::iterator txtItor = txtVSM.begin(); txtItor != txtVSM.end(); txtItor++)
	{
		outFile<<txtItor->first<<endl;
		outFile<<txtItor->second.size()<<" ";
		for(i = 0; i < 1000; i++)
		{
			if(txtItor->second[i] != 0)
			{
				outFile<<i<<" "<<txtItor->second[i]<<" ";
			}
		}
	}*/
	for(map<string,vector<pair<int,double> > > ::iterator txtItor = txtVSM.begin(); txtItor != txtVSM.end(); txtItor++)
	{

		outFile<<txtItor->first<<endl;
		outFile<<txtItor->second.size()<<" ";
		for(i = 0; i < txtItor->second.size(); i++)
		{
			outFile<<txtItor->second[i].first<<" "<<txtItor->second[i].second<<" ";
		}
		outFile<<endl;
	}

	outFile.close();
	txtVSM.clear();
	IDFDic.clear();
	featureDic.clear();
	return 1;
}



void testICTCLAS_VSMforNaiveBayes(string folderPath,int folderId)
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
                testICTCLAS_VSMforNaiveBayes(newPath,folderId+1);
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
				int TF;
				int id;
				//int txtCnt;//文章总词数
				string words;
				istringstream istream(sRst);
				map<string,int>txt;
				vector<pair<int,int> > tmpVSM;
				while(istream>>words)
				{
					//cout<<words<<endl;
					if(featureDic.count(words))
					{
						txt[words]++;
						
					}
				}
		
				id = 0;
				for(set<string>::iterator setItor = featureDic.begin(); setItor != featureDic.end(); setItor++)
				{
				
					TF = txt[(*setItor)];
					if(TF != 0)
					{
						tmpVSM.push_back(make_pair(id,TF));
					}
					id++;
					//outFile<<TF<<" ";
					//cout<<TF<<endl;
				
				}
				//outFile<<endl;
				naiveBayesVSM.insert(STRING2VECTORBAYES::value_type(FileInfo.name,tmpVSM));
				tmpVSM.clear();
				txt.clear();

		 free(sRst);
        }
	
    }while (_findnext(Handle, &FileInfo) == 0);

		_findclose(Handle);
  
	return ;  
}
int myTextToVSMforNaiveBayes(string folderPath,string desPath)
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
	
	ifstream featureDicFile(featureDicPath.c_str());
	cout<<featureDicPath<<endl;
	//ifstream dicFile(myTFDicPath.c_str());

	string featureWord;
	double featureVal;
	string term;
	int id,cnt,df,i;

	while(featureDicFile>>featureWord>>featureVal)
		featureDic.insert(featureWord);

	/*while(dicFile>>term)
	{
		
		dicFile>>id>>cnt;
		for(i = 0; i < cnt; i++)
		{
			dicFile>>id>>df;
		}
		if(featureDic.count(term))
			IDFDic[term] = df;
	}
	for(map<string,int>::iterator it = IDFDic.begin(); it != IDFDic.end(); it++)
		cout<<it->first<<" "<<it->second<<endl;
		*/
   //设置词性标注集(0 计算所二级标注集，1 计算所一级标注集，2 北大二级标注集，3 北大一级标注集)
	ICTCLAS_SetPOSmap(2);

    testICTCLAS_VSMforNaiveBayes(folderPath,0);//分词用例
	
	ICTCLAS_Exit();	//释放资源退出
	ofstream outFile(desPath.c_str());
	for(map<string,vector<pair<int,int> > > ::iterator txtItor = naiveBayesVSM.begin(); txtItor != naiveBayesVSM.end(); txtItor++)
	{
		outFile<<txtItor->first<<endl;
		//cout<<"***"<<endl;
		outFile<<txtItor->second.size()<<" ";
		for(i = 0; i < txtItor->second.size(); i++)
		{
			outFile<<txtItor->second[i].first<<" "<<txtItor->second[i].second<<" ";
		}
		outFile<<endl;
	}

	outFile.close();
	naiveBayesVSM.clear();
	//IDFDic.clear();
	featureDic.clear();
	return 1;
}