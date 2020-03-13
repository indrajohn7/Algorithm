#include<bits/stdc++.h>

using namespace std;

void compute_prefix_function(char* pat,int pi[])
{
	int j=0;
	pi[0]=0;
	for(int i=1;i<strlen(pat);i++){
		while(j>0 && pat[j]!=pat[i]){
			j=pi[j-1];
		}
		if(pat[i]==pat[j]){
			pi[i]=j+1;
			j+=1;
		}
		else{
			pi[i]=pi[j];
		}
	}
}


void kmp_matcher(char* str,char* pat)
{
	int m,n,q=0;
	m=strlen(pat);
	n=strlen(str);
	int* pi=new int[m];
	for(int i=0;i<m;i++)
		pi[i]=0;
	compute_prefix_function(pat,pi);
	for(int i=0;i<n;i++){
		while(q>0 && pat[q]!=str[i]){
			q=pi[q-1];
		}
		if(pat[q]==str[i]){
			q++;
		}
		if(q>= m){  //can check for == condition as well 
			cout<<"Pattern occurs with shift "<<(i-m+1)<<endl;
			q=pi[q];
		}
	}
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
	kmp_matcher(str,pattern);
	return 0;
}
