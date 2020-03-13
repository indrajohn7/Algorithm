#include<bits/stdc++.h>

using namespace std;


int asum(int* arr,int init,int end)
{
	int res=0;
	for(int i=init;i<=end;i++)
		res+=arr[i];
	return res;
}

int main()
{
	int Num_test,iter;
	ifstream fin;
	fin.open("subset.in");
	fin>>Num_test;
	for(iter=0;iter<Num_test;iter++){
		int N,T,max,sum=0,flt=1;
		fin>>N>>T;
		int* arr=new int[N];
		for(int i=0;i<N;i++){
			fin>>arr[i];
		}
		sort(arr,arr+N);
		for(int i=0;i<N;i++){
			if(arr[i]<=N)
				max=i;
			else
				break;
		}
		typedef vector<int> vin;
	//	vector<int> v;
		vector<vin> vec;
		int k=0,count=1;
		for(int i=max;i>=0;i--){
			sum=0;count=1;
			vector<int> v;
			v.clear();
			if(asum(arr,0,i)<T)
				break;   //Here it breaks for the loop for all the iterations 
			while(count<i){
				int j=0,idx=i,flag=0;
				while(j<count){
					if(sum==T){
						vec[k++].push_back(std::move(v));
						flag=1;
						break;
					}
					if((sum+arr[idx])<=T){
						v.push_back(arr[idx]);
						sum+=arr[idx];
						idx--;
						j++;
					}
					else
						idx--;
				}
				if(flag)
					break;
				for(int j=idx;j>=0;j--){
					if((sum+arr[j])==T){
						v.push_back(arr[j]);
						vec[k++].push_back(std::move(v));
						flag=1;
						break;
					}
					else if((sum+arr[j])<T){
						v.clear();
						break;
					}		
				}
				if(flag)
					break;
				count++;
			}
		}
		int min=99999,idx=0;
		for(int i=0;i<vec.size();i++){
			if(vec[i].size()<min){
				min=vec[i].size();
				idx=i;
			}
		}
		cout<<"CASE #"<<iter+1<<":";
		if(vec.size()==0)
			cout<<"NULL\n";
		else{
			for(int i=0;i<vec[idx].size();i++)
				cout<<"\t"<<vec[idx][i];
		}
	}
	return 0;
} 