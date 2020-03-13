/**********************************************        plaindromin_subsequence.cpp   **************************************/

/* For a given string finding palindromic subsequence
 * */


#include<bits/stdc++.h>

using namespace std;

void plaindromic_subsequence(char* str,int** arr,int r)
{
	for(int i=0;i<r;i++){
		for(int j=i;j<r;j++){
			if(i==j)
				arr[i][j]=1;
		}
	}

	int len=1;
	for(len=2;len<=r;len++){
		for(int i=0;i<r-1;i++){
			if((i+len)>r)
				break;
			if(str[i] == str[i+len-1]){
				arr[i][i+len-1]=2+max(arr[i][i+len-2],arr[i+1][i+len-1]);
			}else{
				arr[i][i+len-1]=max(arr[i][i+len-2],arr[i+1][i+len-1]);
			}

		}
	}
}


char* print_string(char* str,int** arr,int r,int c,char* res,int start,int end)
{
	if(r==c){
		res[start]=str[r];
		return res;
	}
	else{
		int maxi=max(arr[r+1][c],arr[r][c-1]);
		if(maxi == arr[r+1][c]){
			if(arr[r][c] > maxi){
				res[start++]=str[r];
				res[end--]=str[r];
			}
			r+=1;
		}else if(maxi == arr[r][c-1] ){
			if(arr[r][c] > maxi){
				res[start++]=str[r];
				res[end--]=str[r];
			}
			c-=1;
		}
		print_string(str,arr,r,c,res,start,end);
	}
}


int main()
{
	char* str=new char[100];
	memset(str,'\0',100);

	cout<<"Input:";
	cin>>str;
	
	int row,col;
	row=col=strlen(str);
	
	int** arr=new int*[row];
	for(int i=0;i<strlen(str);i++)
		arr[i]=new int[row];
	
	plaindromic_subsequence(str,arr,row);
	
	int r,c,max=-1;
	for(int i=0;i<row;i++){
		for(int j=i;j<row;j++){
			if(arr[i][j] > max){
				r=i;
				c=j;
				max=arr[i][j];
			}
		}
	}
	char* res=new char[max+1];
	memset(res,'\0',max+1);
	res=print_string(str,arr,r,c,res,0,max-1);
	cout<<"Longest Palindromic Subsequence:"<<res<<endl;
	return 0;
}
