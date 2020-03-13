#include<bits/stdc++.h>

using namespace std;


class btreenode{
        public:
        btreenode* lchild;
        int data;
        btreenode* rchild;
};

void sorted(vector<btreenode> mytree,int num)
{
	for(int i=0;i<num;i++){
		for(int j=0;j<num-i-1;j++){
			if(mytree[j].data>mytree[j+1].data){
				vector<btreenode> dummy(1);
				dummy[0]=mytree[j];
				mytree[j]=mytree[j+1];
				mytree[j+1]=dummy[0];
			}
		}
	}
}


void inorder(btreenode* bt)
{
        if(bt!=NULL){
                inorder(bt->lchild);
                cout<<bt->data<<"\t";
                inorder(bt->rchild);
        }
        else
			return;
}

void preorder(btreenode* bt)
{
        if(bt!=NULL){
                cout<<bt->data<<"\t";
                inorder(bt->lchild);
                inorder(bt->rchild);
        }
        else
			return;
}

int main()
{
		int i,num,a[100];
		btreenode *bt,**bt_h;
		bt=NULL;
		bt_h=&bt;
		cout<<"Enter the number of Tree element:"<<"\n";
		cin>>num;
		for(i=0;i<num;i++)
			cin>>a[i];
		list<int> mylist(a,a+num);
		vector<btreenode> mytree(num);
		for(i=0;i<num;i++){
			mytree[i].data=a[i];
			mytree[i].lchild=NULL;
			mytree[i].rchild=NULL;
		}
		for(i=1;i<=num-1;i++){
		//	sorted(mytree,mytree.size());
			for(int k=0;k<mytree.size();k++){
				 for(int j=0;j<mytree.size()-k-1;j++){
					if(mytree[j].data>mytree[j+1].data){
				vector<btreenode> dummy(1);
				dummy[0]=mytree[j];
				mytree[j]=mytree[j+1];
				mytree[j+1]=dummy[0];
			}
		}
	}
			int flag=mytree.begin()->data;
			vector<btreenode> :: iterator it= mytree.begin();
			
			btreenode* r=new btreenode;
			r->data=flag+mytree[1].data;
			btreenode* rlchild=new btreenode;
			btreenode* rrchild=new btreenode;
			rlchild->data=flag;
			rrchild->data=mytree[1].data;
		//	rlchild=&mytree[0];
		//	rrchild=&mytree[1];
			if(mytree[0].lchild!=NULL || mytree[0].rchild!=NULL){
				rlchild->lchild=mytree[0].lchild;
				rlchild->rchild=mytree[0].rchild;
			}
			else{
				rlchild->lchild=NULL;
				rlchild->rchild=NULL;
			}
			if(mytree[1].lchild!=NULL || mytree[1].rchild!=NULL){
				rrchild->lchild=mytree[1].lchild;
				rrchild->rchild=mytree[1].rchild;
			}
			else{
				rrchild->lchild=NULL;
				rrchild->rchild=NULL;
			}
			r->lchild=rlchild;
			r->rchild=rrchild;
			mytree.erase(it);
			it=mytree.begin();
			mytree.erase(it);
			
			
			
			mytree.push_back(*r);
		}
		inorder(&mytree[0]);
		cout<<"\n";
		preorder(&mytree[0]);
		cout<<"\n";
		return 0;
}