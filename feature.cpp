#include "classifier.h"

#define Cate 8  //总共有8个类别

#define FEATURELEN 1000

extern string myDicPath;

extern map<string,map<int,int> > myDic;

extern string featureDicPath;

vector<pair<string,double> > myFeature;

double num[9] = {0,516,447,471,492,491,488,500,498};
double num_D = 3903;

bool cmp(const pair<string,double> & m1, const pair<string,double> & m2) 
{
        return m1.second > m2.second;
}


void chiFeatureSelect(string dicPath)
{
	ifstream ifile (dicPath.c_str());
    ofstream ofile (featureDicPath.c_str());
    string str;
    int id,df;
    int len;
   
    double A,B,C,D;
    double n[10],n_9;
	int i ;
    while(ifile>>str)
    {
        for(i = 0; i < 10; i++)
			n[i] = 0;
        ifile>>id>>len;
        
        for(int i = 1; i <= len; i++)
        {
          ifile>>id>>df;
              n[id] = (double)df;//n接受第i类别的DF
          if(id == 9)
              n_9 = (double)df;
        }
        double chiValue = 0;
        double tmpchiValue = 0;
        for(i = 1; i <= 8; i++)
        {
                A = n[i];
                B = n_9 - n[i];
                C = num[i]- n[i];
                D = num_D - n_9 - C;
                tmpchiValue = num_D*pow(A*D-C*B,2) / ((A+C)*(B+D)*(A+B)*(C+D));
                if(tmpchiValue > chiValue)
                            chiValue = tmpchiValue;
                            
        }
        myFeature.push_back(make_pair(str,chiValue));
        
    }
    stable_sort(myFeature.begin(),myFeature.end(),cmp);

    for(vector<pair<string,double> >::size_type j=0;j < FEATURELEN;j++)
    {
        ofile<<myFeature[j].first<<" "<<myFeature[j].second<<endl;
    }
	myFeature.clear();
	myDic.clear();
}

void expectedCrossEntrophyFeatureSelect(string dicPath)
{
	ifstream iFile (dicPath.c_str());
    ofstream oFile (featureDicPath.c_str());
	string words;
	int flag,len;
	int id,df;
	double termDF[10];
	int i;
	while(iFile>>words)
	{
		iFile>>flag>>len;
		for(i = 0; i < 10; i++)termDF[i] = 0;
		for(i = 0; i < len; i++)
		{
			iFile>>id>>df;
			termDF[id] = (double)df;
		}
		
		double crossValue = 0;
		for(i = 1; i <= 8; i++)
		{
			if(termDF[i] == 0)continue;
			crossValue += (termDF[i]/termDF[9]) * log(termDF[i] / (termDF[9] * num[i]/num_D));
		}
		crossValue *= (termDF[9] / num_D);
		myFeature.push_back(make_pair(words,crossValue));
	}

	stable_sort(myFeature.begin(),myFeature.end(),cmp);

    for(vector<pair<string,double> >::size_type j=0;j < FEATURELEN;j++)
    {
        oFile<<myFeature[j].first<<" "<<myFeature[j].second<<endl;
    }
	myFeature.clear();
	iFile.close();
	oFile.close();
	//myDic.clear();

}