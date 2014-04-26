#include "classifier.h"
#include <map>
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


double bayes[1000][8];
string trainBayes = "E:\\final\\final\\myData\\myTFDic.txt";

extern string featureDicPath;
map<string,int> featureDic;
map<string,map<int,int> >bayesDic;

bool cmp(const pair<int,double> & m1, const pair<int,double> & m2) 
{
        return m1.second > m2.second;
}
/*
516 447 471 492 491 488 500 498
*/

void KNN(string trainFilePath,string testFilePath)
{
	//ifstream iFile1("E:\\final\\final\\myData\\VSM.txt");
    //ifstream iFile2("E:\\final\\final\\myData\\VSMtest.txt");

	//ifstream iFile1("E:\\final\\final\\myData\\VSMMatrix.txt");
    //ifstream iFile2("E:\\final\\final\\myData\\VSMtestMatrix.txt");

	//ifstream iFile1("E:\\final\\final\\myData\\VSMMatrixOnCross.txt");
    //ifstream iFile2("E:\\final\\final\\myData\\VSMtestMatrixOnCross.txt");
	ifstream iFile1(trainFilePath.c_str());
	ifstream iFile2(testFilePath.c_str());

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

void naiveBayes(string naiveBayesTestVSM)
{
	ifstream iFile(trainBayes.c_str()); //TF词典"E:\\final\\final\\myData\\myTFDic.txt";
	ifstream featureFile(featureDicPath.c_str());
	cout<<featureDicPath<<endl;
	double featureVal;
	string featureStr;
	string words;
	int TF;
	int cnt;
	int flag;
	int i,j;
	while(featureFile>>featureStr>>featureVal)
		featureDic[featureStr]++;
	while(iFile>>words)
	{
		iFile>>flag>>cnt;
		for(i = 0; i < cnt; i++)
		{
			iFile>>flag>>TF;
			if(featureDic.count(words))
				bayesDic[words][flag] = TF;
		}
	}
	i = j = 0;
	cout<<"******"<<bayesDic.size()<<endl;
	for(map<string,map<int,int> >::iterator itor = bayesDic.begin(); itor != bayesDic.end();itor++)
	{
		//cout<<itor->first<<endl;
		for(int k = 0; k < 8; k++)
			bayes[j][k] = 1.0 / (1000 + bayesDic[itor->first][9]);
		for(map<int,int>::iterator it = itor->second.begin(); it != itor->second.end();it++)
		{
			i = it->first - 1;
			if(i == 8) break;
					bayes[j][i] = 1.0 * (1 + it->second) / (1000.0 + bayesDic[itor->first][9]);
		}
		j++;
	}
	
	ofstream out("mydata\\bayesOnECE.txt");
	for( i = 0; i < 8; i++)
	{
		for(j = 0 ; j < 1000; j++)
				out<<bayes[j][i]<<" ";
		out<<endl;
	}
	double p[8];
	int c,pos,v,b;
	string kk;
	//ifstream in("testBayesOnCross.txt");
	ifstream in(naiveBayesTestVSM.c_str());
	//ofstream myout("ans.txt");
	int result[3117 + 3];
	int reCnt = 0;
	while(in>>kk)
	{
		//in>>kk;
		in>>c;
		for(i = 0; i < 8; i++)p[i] = 0;
		for( i = 0; i < c ;i++)
		{
			in>>pos>>v;
			for(j = 0; j < 8; j++)
			{
				p[j] += v * log(bayes[pos][j]);
				//p[j] += v * log(bayes[j][pos]);
			}
		}
	
		double max = -999999999;
		int ans;
		for(i = 0; i < 8; i++)
		{
			//cout<<p[i]<<endl;
			if(max < p[i])
			{
				max = p[i];
				ans = i;
			}
		}
		//myout<<ans+1<<endl;
		result[reCnt++] = ans;
	}

	for(i = 0; i < reCnt; i++)
    {
            int flag = result[i];
            b = i;
      switch(flag)
		{
		case 2:
			if(b >= 0 && b < 362)artNum[0]++;
			else P[0]++;
			break;
		case 3:
			if(b >= 362 && b < 753)artNum[1]++;
			else P[1]++;
			break;
		case 0:
			if(b >= 753 && b < 1166)artNum[2]++;
			else P[2]++;
			break;
		case 4:
			if(b >= 1166 && b < 1568)artNum[3]++;
			else P[3]++;
			break;
		case 5:
			if(b >= 1568 && b < 1967)artNum[4]++;
			else P[4]++;
			break;
		case 6:
			if(b >= 1967 && b < 2367)artNum[5]++;
			else P[5]++;
			break;
		case 7:
			if(b >= 2367 && b < 2768)artNum[6]++;
			else P[6]++;
			break;
		case 1:
			if(b >= 2768 && b < 3117)artNum[7]++;
			else P[7]++;
			break;
		}
     //b++;
    }
	
}

void evaluateResult(int artNum[],int P[],int n)
{
	int test[8] = {362,391,413,402,399,400,401,349};
	//宏平均
	double MacroR,MacroP;
	double MacroA = 0,MacroB = 0,MacroC = 0;
	double MacroF1;
	double f1;
	for(int i = 0; i < n; i++)
	{
		MacroA += artNum[i];
		MacroB += P[i];
		MacroC += test[i] - artNum[i];
		f1 = (2*(1.0*artNum[i]/test[i])*(1.0*artNum[i]/(artNum[i]+P[i])))/((1.0*artNum[i]/(artNum[i]+P[i])) + (1.0*artNum[i]/test[i]) );
		cout<<"类别"<<i<<"召回："<<artNum[i]<<"正确:"<<P[i]<<"召回率："<<1.0*artNum[i]/test[i]<<"正确率： "<<1.0*artNum[i]/(artNum[i]+P[i])<<"F1："<<f1<<endl;
	}
	MacroR = 1.0 * MacroA/(MacroA + MacroC);//召回率
	MacroP = MacroA/(MacroA + MacroB);//准确率
	MacroF1 = (2 * MacroR * MacroP) / (MacroR + MacroP);
	cout<<"微平均评估："<<MacroF1<<endl;

}