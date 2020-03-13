#include<bits/stdc++.h>

using namespace std;


void rotate_matrix(int** arr, int row_start, int row_end, int col_start, int col_end, int row, int col, int max_rotate, int old=-1)
{
	int temp;
	static bool used=false;

	static int spin=0;

	temp=arr[row][col];
	arr[row][col]=old;
	
	if(spin >= max_rotate){
		spin=0;
		used=false;
		return;
	}
	if(used && row == row_start && row == col){
		spin++;
		used=false;
	}
	


	if(row == row_start){
		if (col == col_end){
			row++;
		} else{
			col++;
		}
		used=true;
	} else if (col == col_end){
	
		if (row == row_end){
			col--;
		} else{
			row++;
		}
	} else if(row == row_end){
	
		if (col == col_start){
			row--;
		} else{
			col--;
		}
	} else if(col == col_start){
		
		if (row == row_start){
			col++;
		} else{
			row--;
		}
	}
	

	rotate_matrix(arr, row_start, row_end, col_start, col_end, row, col, max_rotate, temp);	

}

void print_matrix(int** arr, int r,int c)
{
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++)
			cout<<arr[i][j]<<"\t";
		cout<<endl;
	}
}


int main()
{
	int row,col,rotate;
	cout<<"Enter the row and col numbers: ";
	cin >> row >> col;
	cout<<"Enter the number of rotation: ";
	cin>>rotate;
	int  num = 0;
	int** arr = new int*[row];
	for(int i=0;i<row;i++){
		arr[i] = new int[col];
		for(int j=0;j<col;j++)
			arr[i][j] = num++;
	}

	cout<<"ACTUAL MATRIX:\n";
	print_matrix(arr, row, col);
	static int col_start=0;
	static int col_end,row_end;
	col_end=col-1;
	row_end=row-1;
	for(int i=0;i<(row/2);i++){
		int row_start;
		row_start=i;
		
		int max_rotate = rotate%(2*((row_end-row_start)+(col_end-col_start)));
		if(max_rotate)
			rotate_matrix(arr, row_start, row_end, col_start, col_end, row_start, col_start, max_rotate, arr[row_start][col_start]);

		col_start++;
		col_end--;
		row_end--;
	}
	
	cout<<"FINAL RESULT:\n";
	print_matrix(arr,row,col);

	return 0;
}
