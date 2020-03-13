#include<bits/stdc++.h>

static char* dummy[]={
	"|AMI",
	"|TUMI",
	"|EKHANE",
	"|SEKHANE",
	"|JABO",
	"|ASDS",
	"|FGFG",
	"|AMI",
	"|AMI",
	"|TUMI",
	"|EKHANE",
	"|SEKHANE",
	"|JABO",
	"|ASDS",
	"|FGFG",
	"|AMI",
	"|TUMI",
	"|EKHANE",
	"|SEKHANE",
	"|JABO",
	"|ASDS",
	"|FGFG",
	"|AMI",
	"|TUMI",
	"|EKHANE",
	"|SEKHANE",
	"|JABO",
	"|ASDS",
	"|FGFG",
	"|AMI",
	"|TUMI",
	"|EKHANE",
	"|SEKHANE",
	"|JABO",
	"|ASDS",
	"|FGFG",
	"|TUMI",
	"|EKHANE",
	"|SEKHANE",
	"|JABO",
	"|ASDS",
	"|FGFG",
};

#define SIZE 32 //sizeof(dummy)/sizeof(char*)
using namespace std;


int main()
{
	long long int a=pow(2,31);
	std::cout<<a<<std::endl;
	printf("A::%lld\n",a);
	char* str=(char*)malloc(1000);
	for(int i=0;i<SIZE;i++){
		int x=pow(2,i);
		if((x&(1<<i))==(1<<i))
			strncat(str,dummy[i],strlen(dummy[i]));
	}
	str[strlen(str)]='\0';
	cout<<str<<endl;
	return 0;
}
