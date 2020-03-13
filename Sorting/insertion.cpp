#include<bits/stdc++.h>

using namespace std;


void insertion(int* arr,int N)
{
	for(int i=0;i<N;i++){
			int temp = arr[i];
			int k;
		for(int j=i-1;j>=0;j--){
			if(arr[j]>arr[i]){
				arr[j+1]=arr[j];
			}
			else{
				k=j;
				break;
			}
		}
		arr[k]=temp;
	}
}

int main()
{
	ifstream fin;
	fin.open("sort.in");
	int N;
	fin>>N;
	int* arr=new int[N];
	for(int i=0;i<N;i++){
		fin>>arr[i];
	}
	int* temp=new int[N];
	memcpy(temp,arr,N*sizeof(int));

	insertion(arr,N);

	cout<<"After Sorting:\n";
	for(int i=0;i<N;i++)
		cout<<arr[i]<<"\t";
	cout<<endl;
	
	return 0;
}
