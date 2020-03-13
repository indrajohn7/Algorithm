#include<bits/stdc++.h>

using namespace std;

struct LU{
	int** lower;
	int** upper;
	LU(int R)
	{
		lower=new int*[R];
		for(int i=1;i<=R;i++)
			lower[i]=new int[R];
		upper=new int*[R];
		for(int i=1;i<=R;i++)
			upper[i]=new int[R];
		for(int i=1;i<=R;i++){
			for(int j=1;j<=R;j++){
				lower[i][j]=0;
				upper[i][j]=0;
			}
		}
	}
};

LU* LU_Decompose(int** A,int R)
{
	int i,j,k;
	LU* lu=new LU(R);
	for(i=1;i<=R;i++){
	    lu->upper[i][i]=A[i][i];
		lu->lower[i][i]=1;
		for(j=i+1;j<=R;j++){
			lu->lower[j][i]=A[j][i]/lu->upper[i][i];
			lu->upper[i][j]=A[i][j];
		}
		for(j=i+1;j<=R;j++){
			for(k=i+1;k<=R;k++)
				A[j][k]=A[j][k]-lu->lower[j][i]*lu->upper[i][k];
		}
	}
	return lu;
}

void LUP_Solve(LU* lu,int pi[100],int* B,int R)
{
	int i,j,Y[R];
	float X[R];
	for(i=1;i<=R;i++){
		int sum=0;
		for(j=1;j<=i-1;j++)
			sum+=lu->lower[i][j]*Y[j];
		Y[i]=B[i]-sum;
	}
	for(i=1;i<=R;i++)
		cout<<Y[i]<<"\t";
	cout<<endl;
	for(i=R;i>=1;i--){
		int sum=0;
		for(j=i+1;j<=R;j++)
			sum+=lu->upper[i][j]*X[j];
		X[i]=(float)(Y[i]-sum)/lu->upper[i][i];
	}
	cout<<"ANSWER::\n";
	for(i=1;i<=R;i++){
		cout<<"X["<<i<<"]\t:"<<X[i]<<endl;
	}
}


int main()
{
	int iter,Num_Test;
	ifstream fin;
	fin.open("LUP.in");
	fin>>Num_Test;
	for(iter=0;iter<Num_Test;iter++){
		int R,i,j,k;
		fin>>R;
	//	int A[R][R], B[R];
	    int** A=new int*[R+1];
		for(i=1;i<=R;i++)
			A[i]=new int[R];
		int* B=new int[R];
		for(i=1;i<=R;i++){
			for(j=1;j<=R;j++)
				fin>>A[i][j];
		}
		for(i=1;i<=R;i++)
			fin>>B[i];
		LU* lu=new LU(R);
		lu=LU_Decompose(A,R);
		cout<<"LOWER TRIANGULAR MATRIX:\n";
		for(i=1;i<=R;i++){
			for(j=1;j<=R;j++)
				cout<<lu->lower[i][j]<<"\t";
			cout<<endl<<endl;
		}
		cout<<"UPPER TRIANGULAR MATRIX:\n";
		for(i=1;i<=R;i++){
			for(j=1;j<=R;j++)
				cout<<lu->upper[i][j]<<"\t";
			cout<<endl<<endl;
		}
		int pi[R];
		for(i=0;i<R;i++)
			pi[R]=1;
		LUP_Solve(lu,pi,B,R);
	}
	return 0;
}
 
