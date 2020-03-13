#include<bits/stdc++.h>

using namespace std;

typedef struct _paren{
	long long int ans;
	vector<char*> vec;
}paren;

#define SIZE 2

long long int fact(int n)
{
	if(n==0 || n==1)
		return 1;
	else
		return (n*fact(n-1));
}

paren* calculate(int N)
{
	const char PARENTHESIS[SIZE]={'(',')'};
	paren* p=new paren();
	long long int num = fact(2*(N-1));
	long long int deno = (fact(N-1)*fact(N-1));
	long long int max= (num/deno);
	while(p->vec.size()!=max){
		char* stream=new char[2*N];
		stream[0]='(';
		stream[2*N-1]=')';
		long long int flag,open,close;
		open=close=flag=0;
		for(int i=1;i<(2*N-1);i++){
			int t=rand()%SIZE;
			char c=PARENTHESIS[t];
			if(open==N-1 && c=='(')
				c=')';
			else if(close==N-1 && c==')')
				c='(';
			(c=='(')?open++:close++;
			stream[i]=c;
		}
		for(long long int i=0;i<p->vec.size();i++){
			if(!strcmp(p->vec[i],stream)){
				flag=1;
				break;
			}				
		}
		if(!flag)
			p->vec.push_back(stream);
	}
	return p;
}

void validate(paren** p)
{
	long long int open=0,close=0;
	for(long long int i=0;i<(*p)->vec.size();i++){
		for(int j=0;j<strlen((*p)->vec[i]);j++){
		if((*p)->vec[i][j]=='(' && open>=close)
			open++;
		else if((*p)->vec[i][j]==')' && open>close){
			close++;
		}
		else if((*p)->vec[i][j]==')' && open<=close){
			vector<char*>::iterator it=(*p)->vec.begin()+i;
			(*p)->vec.erase(it);
			i--;
			break;
		}
		}
	}
	(*p)->ans=(*p)->vec.size();
}

int main()
{
	cout<<"GIVE THE NUMBER OF PARENTHESIS::";
	int N;
//	cin>>N;
	N = 9;
	paren* p;
	p=calculate(N);
	validate(&p);
	cout<<"NUMBER OF POSSIBLE CASES:"<<p->ans<<endl;
	cout<<"ALL THE POSSIBLE STRINGS ARE:\n";
	for(int i=0;i<p->vec.size();i++){
		for(int j=0;j<2*N;j++)
			cout<<p->vec[i][j];
		cout<<endl;
	}
	return 0;
}
