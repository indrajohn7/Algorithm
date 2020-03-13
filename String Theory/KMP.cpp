                                                            /*  CORMEN LOGIC */
#include<bits/stdc++.h>

using namespace std;


void compute_prefix_function(char* pat,int pi[])
{
	int m,k=0;
	m=strlen(pat);
	pi[0]=0;
	for(int q=1;q<m;q++){
		while(k>=0 && pat[k]!=pat[q]){
			k=pi[k];
		}
		if(pat[k]==pat[q]){
			k+=1;
		}
		pi[q]=k;
	}
}

void kmp_matcher(char* str,char* pat)
{
	int m,n,q=0;
	m=strlen(pat);
	n=strlen(str);
	int* pi=new int[m];
	compute_prefix_function(pat,pi);
	for(int i=0;i<n;i++){
		while(q>=0 && pat[q+1]!=str[i]){
			q=pi[q];
		}
		if(pat[q+1]==str[i]){
			q+=1;
		}
		if(q==m-1){
			cout<<"Pattern occurs with shift "<<(i-m)<<endl;
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