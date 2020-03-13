#include<bits/stdc++.h>

using namespace std;

void quick(int* arr,int first, int last)
{
	int low,high;
	low=first;
	high=last;
	int pivot=arr[(first+last)/2];
	do{
		while(arr[low]< pivot)
			low++;
		while(arr[high] > pivot)
			high--;
		if(low <= high){
			swap(arr[low],arr[high]);
			low++;
			high--;
		}
	}while(low<=high);

	if(low < last)
		quick(arr,low,last);
	if(high > first)
		quick(arr,first,high);
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
	
	quick(arr,0,N-1);

	cout<<"After Sorting:\n";
	for(int i=0;i<N;i++)
		cout<<arr[i]<<"\t";
	cout<<endl;
	
	return 0;
}
