#include<bits/stdc++.h>

using namespace std;


void simple_merge(int* arr,int first,int second,int third)
{
	int i,j,k;
	i=first;
	j=second;
	k=0;
	int temp[100];
	while(i<second && j<=third){
		if(arr[i] < arr[j])
			temp[k++]=arr[i++];
		else
			temp[k++]=arr[j++];
	}
	while(i < second)
		temp[k++]=arr[i++];
	while(j <= third)
		temp[k++]=arr[j++];

	for(i=0;i<k;i++)
		arr[first+i]=temp[i];
}


void merge(int* arr,int start,int end)
{
	int size=end-start+1;
	if(size<=1)
		return;
	
	int middle=start+(size/2)-1;
	merge(arr,start,middle);
	merge(arr,middle+1,end);

	simple_merge(arr,middle,middle+1,end);
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
	
	merge(arr,0,N);

	cout<<"After Sorting:\n";
	for(int i=0;i<N;i++)
		cout<<arr[i]<<"\t";
	cout<<endl;
	
	return 0;
}
