#include<bits/stdc++.h>

using namespace std;

int main()
{
	int Num_test;
	ifstream fin;
	fin.open("snack.in");
	fin>>Num_test;
	for(int iter=0;iter<Num_test;iter++){
		int N,M;
		fin>>N>>M;
		int* weight=new int[N];
		int* val=new int[N];
		for(int i=0;i<N;i++)
			fin>>weight[i];
		for(int i=0;i<N;i++)
			fin>>val[i];
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N-1;j++){
				if(weight[j]>weight[j+1]){
					int temp;
					swap(weight[j],weight[j+1]);
					swap(val[j],val[j+1]);
				}
			}
		}	
		int** arr=new int*[N];
		for(int i=0;i<N;i++){
			arr[i]=new int[M+1];
			for(int j=0;j<M+1;j++)
				arr[i][j]=0;
		}
		
		
		vector<int> vec;
		
		for(int i=0;i<N;i++){
			for(int j=1;j<=M;j++){
				if(j>=weight[i]){
					if(i==0){
						arr[i][j]=val[i];
					}else{
						arr[i][j]=max((val[i]+arr[i-1][j-weight[i]]),arr[i-1][j]);
					}
				}else{
					if(i==0)
						arr[i][j]=arr[i][j-1];
					else
						arr[i][j]=arr[i-1][j];
				}
			}
		}
		
		int i,j;
		i=N-1;
		j=M;
		while(arr[i][j]!=0){		
			if(arr[i][j]==arr[i-1][j]){
				vec.push_back(i-1);
				i=i-1;
				j=j-weight[i];
			}else{
				j=j-weight[i];
			}
		}
		
		cout<<"Case #"<<iter+1<<":\n";
		for(int i=0;i<vec.size();i++)
			cout<<weight[vec[i]]<<"\t"<<val[vec[i]]<<endl;
	}
	
	return 0;
}