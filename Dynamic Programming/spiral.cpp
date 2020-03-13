#include<bits/stdc++.h>

using namespace std;
int num_ele;

void Do_Spiral(int** arr,int R,int C)
{
	static int temp_r=0,temp_c=0,count=0;
	for(int j=temp_c;j<C;j++){
		cout<<arr[temp_r][j]<<"\t";
		count++;
	}
	temp_r++;
//	count++;
	for(int i=temp_r;i<R;i++){
		cout<<arr[i][C-1]<<"\t";
		count++;
	}
	C--;
	
	for(int j=C-1;j>=temp_c;j--){
		cout<<arr[R-1][j]<<"\t";
		count++;
	}
	R--;
//	count++;
	for(int i=R-1;i>=temp_r;i--){
		cout<<arr[i][temp_c]<<"\t";
		count++;
	}
	temp_c++;
	count++;
	while(count<=num_ele)
		Do_Spiral(arr,R,C);
}


int main()
{
	ifstream fin;
	fin.open("spiral.in");
	int R,C;
	fin>>R>>C;
	num_ele=R*C;
	int** arr=new int*[R];
	for(int i=0;i<R;i++)
		arr[i] = new int[C];
	//int arr[R][C];
	for(int i=0;i<R;i++){
		for(int j=0;j<C;j++)
			fin>>arr[i][j];
	}
	Do_Spiral(arr,R,C);
	cout<<"\n";
}