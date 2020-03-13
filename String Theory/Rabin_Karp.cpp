#include<bits/stdc++.h>

using namespace std;
#define prime_key 101

long long int hash(char* str,int start,int end)
{
	long long int res=0;
	for(int i=start;i<=end;i++){
		res+=(str[i]-'0')*(pow((int)prime_key,(end-i)));
	}
	return res;
}


bool rabin_karp(char* str,char* pattern)
{
	int n,m;
	bool flag = false;
	n=strlen(str);
	m=strlen(pattern);
	long long int h_pattern=hash(pattern,0,m-1);
	for(int i=0;i<(n-m+1);i++){
		long long int h_str=hash(str,i,i+m-1);
		if(h_str==h_pattern){
			if(strncmp(&str[i],pattern,m) == 0){
				cout << "Pattern found at index: " << i << endl;
				flag = true;
			}
		}
	}
	return flag;
}

int main()
{
	cout<<"Pls provide the Test string input :";
	char* str=new char[1000];
	memset(str,'\0',1000);
	cin>>str;
	cout<<"Pls provide the Pattern string input :";
	char* pattern=new char[1000];
	memset(pattern,'\0',1000);
	cin>>pattern;
	bool res=rabin_karp(str,pattern);
	if(!res)
		cout<<"NOT FOUND"<<endl;
	return 0;
}
