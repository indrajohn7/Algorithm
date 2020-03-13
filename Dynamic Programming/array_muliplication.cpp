#include<bits/stdc++.h>

using namespace std;

const char lookup[10]={'0','1','2','3','4','5','6','7','8','9'};

int length(int N)
{
	int count=0;
	while(N!=0){
		N/=10;
		count++;
	}
	return count;
}

char* cal_fact(int n)
{
	char* str=new char[1000];
	int t=1;
	str[0]='1';
	for(int i=1;i<=n;i++){
			t=0;
			for(int j=strlen(str)-1;j>=0;j--){
				int temp=(str[j]-'0');
				str[j]=lookup[(temp*i+t)%10];
				t=((temp*i)+t)/10;
			}
			int len=strlen(str);
			for(int j=len-1;j>=0;j--)
				str[j+length(t)]=str[j];
			while(t!=0){
				str[length(t)-1]=lookup[t%10];
				t/=10;
			}
	}
	return str;/*
	cout<<"ANS:: ";
	for(int i=0;i<strlen(str);i++)
		cout<<str[i];
	cout<<endl;*/
}

char* cal_pow(int x,int n)
{
	char* str=new char[1000];
	int t=1;
	str[0]='1';
	for(int i=1;i<=n;i++){
			t=0;
			for(int j=strlen(str)-1;j>=0;j--){
				int temp=(str[j]-'0');
				str[j]=lookup[(temp*x+t)%10];
				t=((temp*x)+t)/10;
			}
			int len=strlen(str);
			for(int j=len-1;j>=0;j--)
				str[j+length(t)]=str[j];
			while(t!=0){
				str[length(t)-1]=lookup[t%10];
				t/=10;
			}
	}
	return str;
}

int main()
{
	int x,n,ch;
	char* str=new char[2000];
	while(1){
		cout<<"1.FACTORIAL:\n2.POWER:\nWhich OPERATION you want to do:";
		cin>>ch;
		switch(ch){
			case 1: cout<<"Enter a NUM for factorial: ";
			        cin>>n;
					str=cal_fact(n);
					cout<<"ANS:: ";
	                for(int i=0;i<strlen(str);i++)
		                cout<<str[i];
	                cout<<endl;
					break;
			case 2: cout<<"Enter the number and power co-efficient respectively:";
			        cin>>x>>n;
					str=cal_pow(x,n);
					cout<<"ANS:: ";
	                for(int i=0;i<strlen(str);i++)
		                cout<<str[i];
	                cout<<endl;
					break;
		    default: exit(1);
		}
	}
	return 0;
}