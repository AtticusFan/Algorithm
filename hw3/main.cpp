#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<vector>
#include<string>
using namespace std;
void set(vector<int> &vecset, vector<int> &setIndex, vector<int> &cycleSet){
    setIndex.push_back(0);
	setIndex.push_back(1);
	vecset.push_back(cycleSet[0]);
	vecset.push_back(cycleSet[1]);
}
bool GospersHack(int k, int n, vector<int> set, int addtoSet)
{	
    int cur = (1 << k) - 1;
    int limit = (1 << n);
    while (cur < limit)
    {
        int lb = cur & -cur;
        int r = cur + lb;
       
        int temp = cur;
        int tempXor=0; 
        int i = 0;
        while(temp>0){
        	if(temp%2!=0)
        		tempXor^=set[i];			
        		
        	temp/=2;
        	i++;
		}    
		
		cur = (((r ^ cur) >> 2) / lb) | r;
		
		if(tempXor==addtoSet)
			return false;			
    }
    return true;
}
//檢查cycle是否有能由任兩個已在basis中的cycle組成 
vector<int> findMinCycle(vector<int> &vecset, vector<int> &setIndex, vector<int> &cycleSet){

	int i, j;
	for(i=2; i<cycleSet.size(); i++){
		bool result = false;
		for(int j=2; j<=vecset.size(); j++){
			result = GospersHack(j, vecset.size(), vecset, cycleSet[i]);
			if(!result)
				break;
		}
		if(result){
			vecset.push_back(cycleSet[i]);
			setIndex.push_back(i);
		}

	}
	return setIndex;
	
}
int main(int argc,char *argv[])
{
    int i,j;

    FILE *fp;
    char newline[10];
    const char *tempch=" ";
    int nodenum, edgenum, cost, begin, end;
	//讀檔 
	fp=fopen("txt1.txt","r");
	fgets(newline,10,fp);

	sscanf(newline,"%i %i",&nodenum,&edgenum);
	
    int A[nodenum][nodenum];//儲存連線的點
    for(i=0;i<nodenum;i++)
        for(j=0;j<nodenum;j++)
            A[i][j]=0;
    while(fgets(newline,10,fp) != NULL)
	{
	   sscanf(newline,"%i %i %i",&begin,&end,&cost);
	   A[begin][end]=1;
	   A[end][begin]=1;
	}
	fclose(fp);

	int bitCount=0;
	int B[nodenum][nodenum];
	for(int i=0;i<nodenum;i++){
		for(int j=0;j<nodenum;j++){
			B[i][j]=0;
		}
	}
	
    int r,f;
    for(r=0;r<nodenum+1;r++)
    {
        for(f=r+1;f<nodenum;f++){
        	
        	B[r][f]=A[r][f];        	
        	if(B[r][f]!=0){
        		B[r][f]+=bitCount++;
			}   
			B[f][r]=B[r][f];     	
		}                
    }

	


    int k,c,pre,no;//第no格
    int b=0;//有b個temp(多出來的排列組合)
    int s=0,e=nodenum,cycle=0;
    int temp[nodenum];
    int order[20000][nodenum];//預設值-1
    int check_re[20000];
    int check_cycle[nodenum];
    for(i=0;i<20000;i++)
        for(j=0;j<nodenum;j++)
            order[i][j]=-1;
    for(i=0;i<nodenum;i++)
        order[i][0]=i;
    int adde;
    int t;//比大小時的temp
    int smallest,compare;
    int m,n;
    
    vector<int> cycleSet;
	vector<string> cycleString;
	vector<int> vecset;
	vector<int> setIndex;
    for(no=1;no<nodenum;no++)//設定no
    {
        adde=0;
        s=0;
        for(k=0;k<e;k++)//做e次加長連線(e預設為nodenum)
        {
           s+=b;
           b=0;
           pre=order[s][no-1];//pre是前一個頂點
           for(i=order[s][0]+1;i<nodenum;i++)//i=pre+1修改修改修改修改修改修改修改修改修改修改修改
           {
              if(A[pre][i]==1)
              {
                for(j=1;j<(no-1);j++)//for迴圈 檢查有沒有重複的頂點
                {
                    if(order[s][j]==i)
                    {
                        j=-1;
                        break;
                    }
                }
                if(j!=-1)
                    temp[b++]=i;//b計算多出來的排列組合
              }
           }
           c=0;


           if(b>0)
           {
               adde=adde+b-1;
               for(i=e+adde;i>s;i--)//往後移 (更改:e->e+adde)
               {
                  for(j=0;j<no;j++)
                      order[i+b-1][j]=order[i][j];
               }
               for(i=s;i<(s+b);i++)//補上&新連線
               {
                   order[i][no]=temp[c++];
                   for(j=0;j<no;j++)
                       order[i][j]=order[s][j];

                   //檢查cycle
                   if(no>1&&A[order[i][no]][order[i][0]]==1)
                   {

                       for(m=0;m<=no;m++)
                           check_cycle[m]=order[i][m];

                       compare=0;//檢查是否為反序

                       for(m=1;m<=no;m++)
                           compare=compare*10+check_cycle[m];
                       compare=compare*10+check_cycle[0];

                       check_re[i]=0;
                       for(m=no;m>=0;m--)
                           check_re[i]=check_re[i]*10+check_cycle[m];

                       for(m=0;m<i;m++)
                       {
                           if(check_re[m]==compare)
                           {
                               m=-1;
                               break;
                           }
                       }
                       if(m!=-1)
                       {
                       		string tempString = "";
                       		//tempString = "" + to_string(cycle+1)+": ";
                            for(j=0;j<=no;j++)
                                tempString += to_string(order[i][j]) + "->";
							tempString+= to_string(order[i][0]);
							cycleString.push_back(tempString);
                            cycle++;           
							
							int temp=0;
							for(j=0;j<no;j++)							  
                                temp += 1 << (edgenum - B[order[i][j]][order[i][j+1]]);
                            temp += 1 << (edgenum - B[order[i][j]][order[i][0]]);    
                            cycleSet.push_back(temp);
                            
                       }

                   }
               }
           }
           else//b==0
           {
               for(i=s;i<e+adde;i++)//往前移1格
               {
                  for(j=0;j<=no;j++)
                      order[i][j]=order[i+1][j];
               }
               adde--;               
           }
           
        }
        
        e=e+adde;

    }

	
    
    
    for(int i=0;i<cycleString.size();i++){
    	cout<<cycleString[i]<<endl;
	}
	cout<< "# of all cycle: " << cycle <<endl;
    cout<< endl;

    
    int basisNum = edgenum - nodenum + 1;
	cout << "# of edge: "<< edgenum << endl;
	cout << "# of node: "<< nodenum << endl;
    cout << "# of cycle can put in basis: " << basisNum << endl;
	
	set(vecset, setIndex, cycleSet);
	findMinCycle(vecset, setIndex, cycleSet);
	
	
	cout<< endl;
	cout<<"Minimum cycle basis is :"<<endl;
	for(int i=0;i<setIndex.size();i++)
		cout<<cycleString[setIndex[i] ]<<endl;
    return 0;
}
