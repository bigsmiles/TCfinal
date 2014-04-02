#include "classifier.h"

//typedef std::map<string, vector<double> > STRING2VECTOR;
typedef std::map<int, vector<pair<int,double> > > INT2VECTOR;

#define LEN 1000  //向量长度
#define M 100   //KNN的中比较前K个
#define TRAINLEN 3903
#define TESTLEN 3117
#define TEST
//double y[LEN],x;
vector<double> tmpX;
vector<pair<int,double> > knn;
int myKNN[8];

int artNum[8];//正确分到类别ci的文本数
int P[8];//表示不属于类别ci却被分到类别ci的文本数

double trainSet[TRAINLEN+2][1000];
double y[LEN];
//map<int,vector<pair<int,double> > > trainSet;
//vector<pair<int,double> > y;

bool cmp(const pair<int,double> & m1, const pair<int,double> & m2) 
{
        return m1.second > m2.second;
}
/*
516 447 471 492 491 488 500 498
*/

void KNN()
{
	//ifstream iFile1("E:\\final\\final\\myData\\VSM.txt");
    //ifstream iFile2("E:\\final\\final\\myData\\VSMtest.txt");

	ifstream iFile1("E:\\final\\final\\myData\\VSMMatrix.txt");
    ifstream iFile2("E:\\final\\final\\myData\\VSMtestMatrix.txt");

    string trainTerm,testTerm;
    map<string,double> result;
    double ans,val,r1,r2;
    int b = 0;
    int cnt = 0;
	int i;
	int lenth;
	int id;
	//vector<pair<int,double> >tmp;
	memset(trainSet,0,sizeof(trainSet));
    while(iFile1>>trainTerm)
    {
	   iFile1>>lenth;
       for( i = 0; i < lenth; i++)
       {
               //iFile1>>trainSet[cnt][i];
				iFile1>>id>>val;
				//tmp.push_back(make_pair(id,val));
				trainSet[cnt][id] = val;

       }
	   //trainSet.insert(INT2VECTOR::value_type(cnt,tmp));
	   //tmp.clear();
       cnt++;
    }
    cout<<"***"<<endl;
    while(iFile2>>testTerm)
    {
        b++;
        memset(myKNN,0,sizeof(myKNN));
		
		iFile2>>lenth;
		memset(y,0,sizeof(y));
        for(int i = 0; i < lenth; i++)
		{
             iFile2>>id>>val;
			 //y.push_back(make_pair(id,val));
			 y[id] = val;
		}
		//cout<<testTerm<<endl;
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
		/*vector<pair<int,double> >x;
		for(int k = 0; k < TRAINLEN; k++)
		{
			ans = 0,val = 0;
			double r = 0, s = 0, t = 0;
		
			x = trainSet[k];
			int px  = 0,py = 0;
			
			while(px < x.size() && py < y.size())
			{
				//cout<<"UUUU"<<x[px].first<<y[py].first<<"||"<<px<<py<<x.size()<<y.size()<<endl;
				if(x[px].first == y[py].first)
				{
					r += x[px].second * y[py].second;
					s += x[px].second * x[px].second;
					t += y[py].second * y[py].second;
					px++;
					py++;
					//cout<<px<<py<<endl;
				}
				while(x[px].first < y[py].first && px < x.size())
				{
					s += x[px].second * x[px].second; 
					px++;
					//cout<<px<<endl;
				}
				 while(y[py].first < x[px].first && py < y.size())
				{
					t += y[py].second * y[py].second; 
					py++;
					//cout<<py<<endl;
				}
				 //sleep(10);
			}
			while( px < x.size())
			{
					s += x[px].second * x[px].second; 
					px++;
					//cout<<px<<endl;
			}
			while(py < y.size())
			{
					t += y[py].second * y[py].second; 
					py++;
					//cout<<py<<endl;
			}
			x.clear();
			ans = r / (sqrt(s)*sqrt(t));
			knn.push_back(make_pair(k,ans));
		}*/
        //cout<<testTerm<<knn.size()<<endl;  
		cout<<testTerm<<endl;
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
		switch(flag)
		{
		case 0:
			if(b >= 0 && b < 362)artNum[0]++;
			else P[0]++;
			break;
		case 1:
			if(b >= 362 && b < 753)artNum[1]++;
			else P[1]++;
			break;
		case 2:
			if(b >= 753 && b < 1166)artNum[2]++;
			else P[2]++;
			break;
		case 3:
			if(b >= 1166 && b < 1568)artNum[3]++;
			else P[3]++;
			break;
		case 4:
			if(b >= 1568 && b < 1967)artNum[4]++;
			else P[4]++;
			break;
		case 5:
			if(b >= 1967 && b < 2367)artNum[5]++;
			else P[5]++;
			break;
		case 6:
			if(b >= 2367 && b < 2768)artNum[6]++;
			else P[6]++;
			break;
		case 7:
			if(b >= 2768 && b < 3117)artNum[7]++;
			else P[7]++;
			break;
		}
        knn.clear();
    }
}
void evaluateResult(int artNum[],int P[],int n)
{
	int test[8] = {362,391,413,402,399,400,401,349};
	//宏平均
	double MacroR,MacroP;
	double MacroA = 0,MacroB = 0;
	double MacroF1;
	for(int i = 0; i < n; i++)
	{
		MacroA += artNum[i];
		MacroB += P[i];
		cout<<"类别"<<i<<"："<<artNum[i]<<"召回率："<<1.0*artNum[i]/test[i]<<"正确率： "<<1.0*artNum[i]/(artNum[i]+P[i])<<endl;
	}
	MacroR = MacroA/8;//召回率
	MacroP = MacroB/8;//准确率
	MacroF1 = (2 * MacroR * MacroP) / (MacroR + MacroP);
	cout<<"宏平均评估："<<MacroF1<<endl;

}