#include<bits/stdc++.h>

using namespace std;
#define Num 100
char stream[Num];

int search_pattern(char* str,int T[][Num],int M)
{
	int state=0;
	for(int i=0;i<strlen(str);i++){
		state=T[state][str[i]-'a']
		if(state==M)
			cout<<"Found at POS: "<<(i-M+1)<<endl;
	}
	cout<<"NOT FOUND\n"
	return -1;
}


int get_next_state(char* pat,int N,int state,int x)
{
	
	static char str[Num]={'\0'};
	int res=0;
	str[0]=pat[0];
	strncat(str,(char*)stream[x],1);
	str[x+1]='\0';
	for(int i=0;i<=state;i++){
		if(str[i]==pat[i])
			res++;
		else
			break;
	}
	str[state]=pat[state];
	return res;
}

void create_state_machine(char* pattern,int N,int T[][Num])
{
	T[0][pat[0]-'a']=1;
	for(int i=1;i<N;i++){
		for(int j=0;j<Num;j++){
			T[i][j]=get_next_state(pattern,N,i,j);
		}
	}
}


int finite_automata(char* str, char* pat)
{
	int m,n,;
	m=strlen(pat);
	n=strlen(str);
	int** T=new int*[m+1];
	for(int i=0;i<m+1;i++){
		T[i]=new int[Num];
		memset(T[i],0,Num);
	}
	create_state_machine(pat,m+1,T);
	int res=search_pattern(str,T,m);
	return res;
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
	for(int i=0;i<Num;i++)
		stream[i]='a'+i;
	int res=finite_automata(str,pattern);
/*	if(res==-1)
		cout<<"NOT FOUND"<<endl;
	else
		cout<<"Found at Pos:"<<res+1<<endl;
*/	return 0;
}