#include<bits/stdc++.h>

using namespace std;
#define N 4
int* arr_ret()
{
	int* b=new int[N];
	for(int i=0;i<N;i++)
		b[i]=i;
	return b;
}
int main()

{
	int* a;
	a=arr_ret();
	for(int i=0;i<N;i++)
		cout<<a[i]<<"\t";
	cout<<endl;
	return 0;
}