#include<bits/stdc++.h>

using namespace std;

int main()
{
	int A=0Xdeadbeef;
	cout<<hex<<A<<"\n";
	A=((A>>24)&0X000000FF)| ((A<<8)&0X00FF0000) | ((A>>8)&0X0000FF00) | ((A<<24)&0XFF000000);
	cout<<hex<<A<<"\n";
	printf("A:%X\n",A);
	return 0;
}
