#include<bits/stdc++.h>
#define N 10
using namespace std;

void Insert_Max_heap(int tree[],int n,int data)
{
	int ptr,par;
	ptr=n;
	while(ptr>1){
		par=ptr/2;
		if(data<=tree[par]){
			tree[ptr]=data;
			return;
		}
		tree[ptr]=tree[par];
		ptr=par;
	}
	tree[1]=data;
}


void Insert_Min_heap(int tree[],int n,int data)
{
	int ptr,par;
	ptr=n;
	while(ptr>1){
		par=ptr/2;
		if(data>tree[par]){
			tree[ptr]=data;
			return;
		}
		tree[ptr]=tree[par];
		ptr=par;
	}
	tree[1]=data;
}


void Delete_Min_heap(int tree[],int n)
{
	int ptr,left,right,last;
	ptr=1;
	left=2;
	right=3;
	tree[n]=tree[1];
	last=tree[n--];
	while(right<=n){
		if(last<tree[left] && last<tree[right]){
			tree[ptr]=last;
		//	cout<<tree[ptr]<<"\t";
			return;
		}
		if(tree[left]<tree[right]){
			tree[ptr]=tree[left];
			ptr=left;
		}
		else{
			tree[ptr]=tree[right];
			ptr=right;
		}
		left=2*ptr;
		right=left+1;
	}
	if(left==n && tree[left]<last){
		tree[ptr]=tree[left];
		ptr=left;
	}
	tree[ptr]=last;
	//cout<<tree[ptr]<<"\t";
} 


void Delete_Max_heap(int tree[],int n)
{
	int ptr,left,right,last;
	ptr=1;
	left=2;
	right=3;
	tree[n]=tree[1];
	last=tree[n--];
	while(right<=n){
		if(last>=tree[left] && last>=tree[right]){
			tree[ptr]=last;
			return;
		}
		if(tree[left]>=tree[right]){
			tree[ptr]=tree[left];
			ptr=left;
		}
		else{
			tree[ptr]=tree[right];
			ptr=right;
		}
		left=2*ptr;
		right=left+1;
	}
	if(left==n && tree[left]>=last){
		tree[ptr]=tree[left];
		ptr=left;
	}
	tree[ptr]=last;
} 
void display(int tree[])
{
	for(int i=1;i<=N;i++)
		cout<<tree[i]<<"\t";
	cout<<"\n";
}


int main()
{
	int i,a_min[N],a_max[N];
	srand (time(NULL));
  /* generate secret number between 1 and 1000: */
	for(i=1;i<=N;i++)
		a_min[i]=a_max[i]= rand() % 1000;
	for(i=1;i<N;i++)
		Insert_Max_heap(a_max,i+1,a_max[i+1]);
	display(a_max);
	for(i=N;i>N;i--)
		Delete_Max_heap(a_max,i);
	display(a_max);
	for(i=1;i<N;i++)
		Insert_Min_heap(a_min,i+1,a_max[i+1]);
	display(a_min);
	for(i=N;i>N;i--)
		Delete_Min_heap(a_min,i);
	//cout<<"\n";
	display(a_min);
	return 0;
		
}