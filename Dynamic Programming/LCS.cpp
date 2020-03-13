#include<bits/stdc++.h>

using namespace std;

void PRINT_LCS(char b[][100],char X[100],int x, int y)
{
	if(x==0 || y==0)
		return;
	else if(b[x][y]=='$'){
		PRINT_LCS(b,X,x-1,y-1);
		cout<<X[x-1];
	}
	else if(b[x][y]=='^')
		PRINT_LCS(b,X,x-1,y);
	else if(b[x][y]=='<')
		PRINT_LCS(b,X,x,y-1);
}

int main()
{
	char X[100],Y[100],b[100][100];
	int c[100][100];
	int x,y,i,j;
	cout<<"Please enter the length of two char arrays:\n";
	cin>>x>>y;
	cout<<"Enter the Strings:\n"<<"First String:\t";
	for(i=0;i<x;i++)
		cin>>X[i];
	cout<<"Second String:\t";
	for(i=0;i<y;i++)
		cin>>Y[i];
	for(i=0;i<=x;i++){
		for(j=0;j<=y;j++){
		   c[i][j]=0;
		}
	}
	for(i=1;i<=x;i++)
	{
		for(j=1;j<=y;j++){
			if(X[i-1]==Y[j-1]){
				c[i][j]=c[i-1][j-1]+1;
				b[i][j]='$';
			}
			else if(c[i-1][j]>=c[i][j-1]){
				c[i][j]=c[i-1][j];
				b[i][j]='^';
			}
			else{
				c[i][j]=c[i][j-1];
				b[i][j]='<';
			}
		}
	}
	for(i=0;i<=x;i++){
		for(j=0;j<=y;j++){
			cout<<b[i][j]<<","<<c[i][j]<<"\t";
		}
		cout<<"\n";
	}
	PRINT_LCS(b,X,x,y);
	cout<<"\n";
	return 0;
}
