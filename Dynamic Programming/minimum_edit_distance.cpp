/****************************************          MINIMUM EDIT DISTANCE            ****************************************************/

/* Given 2 strings and operations like delete,edit and add .Then how many operations minimum would be required to 
 * convert string S1 to string S2 and what are the conversion..
 * */

#include<bits/stdc++.h>
#define MAXSZ 100

using namespace std;


void print_conversion(int** arr,char* s1,char*s2,int r,int c)
{

	if(r==0 || c==0)
		return;

	int mini=min(arr[r-1][c-1],arr[r-1][c]);
	mini=min(mini,arr[r][c-1]);

		


	if(mini == arr[r-1][c-1]){
		if(s1[c-1] != s2[r-1])
			cout<<s1[c-1]<<" is converted to "<<s2[r-1]<<endl;
		print_conversion(arr,s1,s2,r-1,c-1);
	}else if(mini == arr[r-1][c]){
		cout<<s1[c-1]<<" is added to target string"<<endl;
		print_conversion(arr,s1,s2,r-1,c);
	
	}else{
		cout<<s1[c-1]<<" is deleted from source string"<<endl;
		print_conversion(arr,s1,s2,r,c-1);
	
	}
}

void minimum_edit(char* s1,char* s2,int** arr,int row, int col)
{
	for(int i=1;i<row;i++){
		for(int j=1;j<col;j++){
			if(s1[j-1] == s2[i-1]){
				arr[i][j]=arr[i-1][j-1];
			}else{
				int mini=min(arr[i-1][j],arr[i][j-1]);
				mini=min(mini,arr[i-1][j-1]);
				arr[i][j]=mini+1;
			}
		}
	}
}


int main()
{
	char* source=new char[MAXSZ];
	char* target=new char[MAXSZ];
	
	memset(source,'\0',MAXSZ);
	memset(target,'\0',MAXSZ);

	cout<<"Source Input:\n";
	cin>>source;

	cout<<"Target Input:\n";
	cin>>target;

	int row,col;
	row=strlen(target)+1;
	col=strlen(source)+1;
	int** arr=new int*[row];
	for(int i=0;i<row;i++)
		arr[i]=new int[col];
	
	for(int i=0;i<row;i++)
		arr[i][0]=i;
	for(int i=0;i<col;i++)
		arr[0][i]=i;
	
	minimum_edit(source,target,arr,row,col);
	int res=arr[row-1][col-1];

	cout<<"To convert source string to target string we need "<<res<<" no of operations:\n";

	print_conversion(arr,source,target,row-1,col-1);

	return 0;
}
