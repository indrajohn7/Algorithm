#include<bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;

int minimum(vector<pii> vec,int** arr,int* root,int start,int end)
{
	unsigned int min=-1;
	for(int i=start;i<=end;i++){
		if(start==end-1){
			if(vec[start].second>vec[end].second){
				*root=start;
				return vec[start].second;
			}else{
				*root=end;
				return vec[end].second;
			}
		}
		int res=0;
		if(i==start)
			res+=arr[i+1][end];
		else{
			res+=arr[start][i-1];
			res+=arr[i+1][end];
		}
		
		if(res<min){
			min=res;
			*root=start;
		}
	}
	
	return min;
}


int main()
{
	int Num_test;
	ifstream fin;
	fin.open("optimal.in");
	fin>>Num_test;
	for(int iter=0;iter<Num_test;iter++){
		int N;
		fin>>N;
		typedef pair<int,int> pii;
		vector<pii> vec;
		
		for(int i=0;i<N;i++){
			int t;
			fin>>t;
			vec.push_back(make_pair(t,0));
		}
		for(int i=0;i<N;i++){
			int t;
			fin>>t;
			vec[i].second=t;
		}
		
		int** arr[]=new int*[N];
		for(int i=0;i<N;i++)
			arr[i]=new int[N];
		
		int** pos[]=new int*[N];
		for(int i=0;i<N;i++)
			pos[i]=new int[N];
		
		for(int i=0;i<N;i++)
			arr[i][i]=vec[i].second;
		
		for(int i=2;i<=N;i++){
			for(int j=0;j<=(len-i);j++){
				int res=0;
				for(int p=j;p<=j+i-1;p++)
					res+=vec[p].second;
				int root;
				int mini=minimum(vec,arr,&root,j,j+i-1);
				res+=mini;
				arr[j][j+i-1]=res;
				pos[j][j+i-1]=root;
			}
		}
		
		
		cout<<"Case #"<<iter+1<<": "<<"COST: "<<arr[0][N-1]<<"ROOT: "<<pos[0][N-1]<<endl;
	}
	
	return 0;
}