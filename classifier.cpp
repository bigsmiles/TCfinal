#include "classifier.h"

typedef std::map<string, vector<double> > STRING2VECTOR;
#define LEN 1000  //向量长度
#define M 100   //KNN的中比较前K个
#define TRAINLEN 3903
#define TEST
double y[LEN],x;
vector<double> tmpX;
vector<pair<int,double> > knn;
int myKNN[8];
int artNum[9];
double trainSet[TRAINLEN+2][1000];
bool cmp(const pair<int,double> & m1, const pair<int,double> & m2) 
{
        return m1.second > m2.second;
}
/*
516 447 471 492 491 488 500 498
*/

void KNN()
{
	ifstream iFile1("E:\\final\\final\\myData\\VSM.txt");
    ifstream iFile2("E:\\final\\final\\myData\\VSMtest.txt");
    string trainTerm,testTerm;
    map<string,double> result;
    double ans,val,r1,r2;
    int b = 0;
    int cnt = 0;
	int i;
    while(iFile1>>trainTerm)
    {
       for( i = 0; i < LEN; i++)
       {
               iFile1>>trainSet[cnt][i];
       }
       cnt++;
    }
    cout<<"***"<<endl;
    while(iFile2>>testTerm)
    {
        b++;
        memset(myKNN,0,sizeof(myKNN));
        for(int i = 0; i < LEN; i++)
             iFile2>>y[i];
      
        for(int k = 0; k < TRAINLEN; k++)
        {
             ans = 0;
             val = 0;
             r1 = 0; r2 = 0;
             for(int i = 0; i < LEN; i++)
             {
                     val += trainSet[k][i] * y[i];
                     r1 += trainSet[k][i] * trainSet[k][i];
                     r2 += y[i] * y[i];
             }
             ans = val/(sqrt(r1)*sqrt(r2));
             knn.push_back(make_pair(k,ans)); 
        }
        //cout<<testTerm<<knn.size()<<endl;  
        stable_sort(knn.begin(),knn.end(),cmp);
        //排序之后是：太空 计算机 艺术 环境 农业 经济 体育 历史
        for( i = 0; i < M; i++)
        {
                //cout<<knn[i].first<<knn[i].second<<endl;
                int w = knn[i].first;
                if(w >= 0 && w < 471)
                        myKNN[0]++;
                else if(w >= 471 && w < 963)                    
                        myKNN[1]++;
                else if(w >= 963 && w < 1479) 
                        myKNN[2]++;
                else if(w >= 1479 && w < 1970) 
                        myKNN[3]++;
                else if(w >= 1970 && w < 2458) 
                        myKNN[4]++;
                else if(w >= 2458 && w < 2958) 
                        myKNN[5]++;
                else if(w >= 2958 && w < 3456) 
                        myKNN[6]++;
                else
                        myKNN[7]++;
        }
        
        int flag = 0;
        int tmp = 0;
        for( i = 0; i < 8; i++)
        {
                //cout<<myKNN[i]<<" ";
                if(myKNN[i] > tmp)
                {
                            tmp = myKNN[i];
                            flag = i;
                }
        }
        //cout<<endl;
		//排序之后是：太空 计算机 艺术 环境 农业 经济 体育 历史
        if(b >= 0 && b < 362 && flag == 0)
             artNum[0]++;
        else if (b >= 362 && b < 753 && flag == 1)
             artNum[1]++;
        else if (b >= 753 && b < 1166 && flag == 2)
             artNum[2]++;
        else if (b >= 1166 && b < 1568 && flag == 3)
             artNum[3]++;
        else if (b >= 1568 && b < 1967 && flag == 4)
             artNum[4]++;
        else if (b >= 1967 && b < 2367 && flag == 5)
             artNum[5]++;
        else if (b >= 2367 && b < 2768 && flag == 6)
             artNum[6]++;
        else if(b >= 2768 && b < 3117 && flag == 7)
             artNum[7]++;
        else
            artNum[8]++;
        knn.clear();
       //break;
    }
	int test[8] = {362,391,413,402,399,400,401,349};
    for( i = 0; i <= 8; i++)// 413 349 362 391 402 399 400 401
    cout<<"属于该类别文章数："<<artNum[i]<<"正确率："<<artNum[i]/test[i]<<endl;
}