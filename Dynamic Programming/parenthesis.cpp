#include<bits/stdc++.h>

using namespace std;

void print_optimal_paren(int s[][100],int R,int C)
{
	if(R==C)
		cout<<"A"<<R;
	else
	{
		cout<<"(";
		print_optimal_paren(s,R,s[R][C]);
		print_optimal_paren(s,s[R][C]+1,C);
		cout<<")";
	}
	cout<<"\n";
}


int main()
{
	int Test,iter;
	ifstream fin;
	fin.open("infile.in");
	fin>>Test;
	for(iter=1;iter<=Test;iter++)
	{
		int length,l,i,j,k,flag,ROW,COL;
		fin>>length;
		fin>>ROW>>COL;
		long long p[length],m[length][length],q;
		int s[100][100];
		for(i=1;i<=length;i++)
		{
			fin>>flag;
			fin>>p[i];
		}
		for(i=1;i<length;i++)
			m[i][i]=0;
		for(l=2;l<=length-1;l++){
			for(i=1;i<=length-l+1;i++){
				j=i+l-1;
				m[i][j]=99999999999999999;
				for(k=i;k<=j-1;k++){
					q=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
					if(q<m[i][j]){
						m[i][j]=q;
						s[i][j]=k;
					}
				}
			}
		}
		cout<<"CASE #"<<iter<<":	";
	//	print_optimal_paren(s,ROW,COL);
	    for(i=1;i<length;i++){
			for(j;j<length;j++){
				cout<<m[i][j]<<",";
				cout<<s[i][j]<<"\t";
			}
			cout<<"\n";
		}
			
	}
	return 0;
}