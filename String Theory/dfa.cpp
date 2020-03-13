#include<bits/stdc++.h>

using namespace std;

void state_machine(char* text,int** delta,int m)
{
	int q=0;
	for(int i=0;i<strlen(text);i++){
		q=delta[q][text[i]-'a'];
		if(q==m)
			cout<<"Pattern found at location: "<<q-m+1<<endl;
	}
}

void dfa(char* text,char* pattern)
{
	int arr[26];
	for(int i=0;i<26;i++)
		arr[i]=0;
	for(int i=0;i<strlen(text);i++)
		arr[tolower(text[i])-'a']++;
	int len=strlen(pattern);
	vector<char> vec;
	for(int i=0;i<26;i++){
		if(arr[i]>0)
			vec.push_back('a'+i);
	}
	
	int** delta=new int*[len+1];
	for(int i=0;i<len+1;i++)
		delta[i]=new int[26];
	for(int i=0;i<=len;i++){
		for(int j=0;j<vec.size();j++){
			int k=min(i+1,m);
			char* dummy=new char[k+1];
			memset(dummy,'\0',k+1);
			strncpy(dummy,text,k-1);
			dummy[k-1]=vec[j];
			dummy[k]='\0';
			for(int p=0;p<strlen(dummy);p++){
				if(strncmp(&dummy[p],&pattern[p],strlen(dummy)-p)==0)
					break;
				k-=1;
			}
			
			delta[i][vec[j]-'a']=k;
		}
	}
	
	state_machine(text,delta,len);
}

int main()
{
	char* text= new char[100];
	char* pattern= new char[20];
	cout<<"Please give the text input:";
	cin<<text;
	cin<<"Please give the pattern input:";
	cin>>pattern;
	dfa(text,pattern);
	return 0;
}