#include "classifier.h"

#define POS_TAGGER_TEST
#ifdef POS_TAGGER_TEST
bool g_bPOSTagged=true;
#else
bool g_bPOSTagged=false;
#endif	
string stopWordsPath = "E:\\final\\final\\myData\\stopwords.txt"; //��¼ͣ�ôʴʵ��·��
string myDicPath = "E:\\final\\final\\myData\\myDic.txt"; //���Ͽ�ʵ��·��
map<string,map<int,int> >myDic; 
/*
�ʵ��ʽ���磬�����
�����
0 3 1 3 4 5 9 8
��ʾ����������,��1����г���"�����"���ĵ�Ƶ��(DF)��3
��4����г���"�����"��DF�� 5
��9������ "�����"�����Ͽ����DF
*/
set<string>stopDic;	//ͣ�ôʴʵ�

void testICTCLAS_ParagraphProcess(string folderPath,int folderId)  //path��ʼ·��
{

	long Handle;
	struct _finddata_t FileInfo;

	string fpath = folderPath + "\\*";
	if((Handle = _findfirst(fpath.c_str(),&FileInfo)) == -1L)  //����Ŀ¼�µ��ļ�
	{
		printf("û���ҵ�ƥ�����Ŀ");
		exit(-1);
	}

	do{
			//�ж��Ƿ�����Ŀ¼
			if (FileInfo.attrib & _A_SUBDIR)    
			{
				 //���������Ҫ
				if( (strcmp(FileInfo.name,".") != 0 ) &&(strcmp(FileInfo.name,"..") != 0))   
				{
					string newPath = folderPath + "\\" + FileInfo.name;
					cout<<"Ŀ¼��"<<newPath<<endl; 
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

				while(ifile>>ch)	//��������Ϊ�˽����з�ȥ����ASCII��10��13
				{
					 if(ch == '\n' || ch == '\r')
						 continue;
					 sSentence[len++] = ch;
				}
		
				sSentence[len] = '\0';
				unsigned int nPaLen=strlen(sSentence); // ��Ҫ�ִʵĳ���
				char* sRst=0;   //�û����з���ռ䣬���ڱ�������
				//sRst=(char *)malloc(nPaLen*6); //���鳤��Ϊ�ַ������ȵı���
				//int nRstLen=0; //�ִʽ���ĳ���
			
				//nRstLen = ICTCLAS_ParagraphProcess(sSentence,nPaLen,sRst,CODE_TYPE_UNKNOWN,0);  //�ַ�������
				/*�ռ����ʣ��γ��ֵ�*/
				 int rstCount=0;

				LPICTCLAS_RESULT rstVec=ICTCLAS_ParagraphProcessA(sSentence,nPaLen,rstCount,CODE_TYPE_UNKNOWN,g_bPOSTagged);
				printf("******%d\n",rstCount);											//�ַ�������
				string str = sSentence;
				string words;
				set<string> txtDic;
				for (int i=0;i< rstCount;i++)
				{//��ӡ�ִʽ��
					words = str.substr(rstVec[i].iStartPos,rstVec[i].iLength);
					if(!txtDic.count(words) && !stopDic.count(words))
					{
						++myDic[words][9];
						++myDic[words][folderId];
						txtDic.insert(words);
					}
					printf("start=%d,length=%d type = %s %d\r\n",rstVec[i].iStartPos,rstVec[i].iLength,rstVec[i].szPOS,rstVec[i].iPOS);
				}
			
				//cout<<"Ŀ¼Ϊ��"<<folderId<<endl;
				/*string words;
				istringstream istream(sRst);
				set<string> txtDic; //��ʾһƪ���µĴʵ�,Ϊ��ͳ�ƴʵ��ĵ�Ƶ��DF
				while(istream>>words)
				{

					if((!txtDic.count(words)) && (!stopDic.count(words)))
					{
						++myDic[words][9];
						++myDic[words][folderId];
						txtDic.insert(words);
					}
				}*/
				txtDic.clear();
				ICTCLAS_ResultFree(rstVec);	//���ýӿ��ͷ��ڴ�
				//free(sRst);
			}
	
    }while (_findnext(Handle, &FileInfo) == 0);

	_findclose(Handle);
	return ;  
}

int myParagraphProcess(string folderPath)
{
	if(!ICTCLAS_Init()) //��ʼ���ִ������
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

   //���ô��Ա�ע��(0 ������������ע����1 ������һ����ע����2 ���������ע����3 ����һ����ע��)
	ICTCLAS_SetPOSmap(2);
    testICTCLAS_ParagraphProcess(folderPath,0);//�ִ�����
	ICTCLAS_Exit();	//�ͷ���Դ�˳�
	

	int dic_num = 0;
	int flag = 0;  //��0��,��ʾ����Ĵ�С
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
	printf("\n�����ִʣ�%d\n",dic_num);

	myDic.clear(); //�Ѿ�������Ӳ���ˣ���������˰ɣ�
	stopDicFile.close();
	ofile.close();
	return 1;
}