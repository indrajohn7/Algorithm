#include<bits/stdc++.h>

using namespace std;
#define TRUE 1
#define FALSE 0

typedef struct _btreenode{
        public:
        struct _btreenode* lchild;
        int data;
        struct _btreenode* rchild;
}btreenode;

void insert(btreenode** tr,int num)
{
        if(*tr==NULL)
        {
                *tr=new btreenode;
                (*tr)->lchild=NULL;
                (*tr)->rchild=NULL;
                (*tr)->data=num;
                return;
        }
        else{
                if(num>(*tr)->data)
                {
                        (*tr)=(*tr)->rchild;
                        insert(tr,num);
                }
                else{
                        (*tr)=(*tr)->lchild;
                        insert(tr,num);
                }
        }
        return;
}

void search(btreenode** bt,int num,btreenode** par,btreenode**x,int *found)
{
        struct btreenode* q;
        q=*bt;
        *found=FALSE;
        *par=NULL;
        while(q!=NULL){
                if(q->data==num){
                        *found=TRUE;
                        *x=q;
                        return;
                }
                if(q->data>num){
                        *par=q;
                        q=q->lchild;
                }
                else{
                        *par=q;
                        q=q->rchild;
                }
        }
}


void bdelete(btreenode** bt, int num)
{
        int found;
        btreenode *parent;
		btreenode *x;
		btreenode *xsucc;
        if(*bt==NULL)
        {
                cout<<"Tree is Empty:\n";
                return;
        }
        parent=NULL;
		x =NULL;
        search(bt,num,&parent,&x,&found);
        if(found==FALSE)
        {
                cout<<"Data not found in BTREE:\n";
                return;
        }
        if(x->lchild!=NULL && x->rchild!=NULL){
                parent=x;
                xsucc=x->rchild;
                while(xsucc->lchild!=NULL){
                        parent=xsucc;
                        xsucc=xsucc->lchild;
                }
                x->data=xsucc->data;
                x=xsucc;
        }
        else if(x->lchild==NULL && x->rchild!=NULL){
                if(parent->rchild==x)
                        parent->rchild=x->rchild;
                else
                        parent->lchild=x->rchild;
                delete(x);
                return;
        }
        else if(x->lchild!=NULL && x->rchild==NULL){
                if(parent->rchild==x)
                        parent->rchild=x->lchild;
                else
                        parent->lchild=x->lchild;
                delete(x);
                return;
        }
        else if(x->lchild==NULL && x->rchild==NULL){
                if(parent->rchild==x)
                        parent->rchild=NULL;
                else
                        parent->lchild=NULL;
                delete(x);
                return;
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

void postorder(btreenode* bt)
{
        if(bt!=NULL){
                inorder(bt->lchild);
                inorder(bt->rchild);
                cout<<bt->data<<"\t";
        }       
		else
			return;
}


int main()
{
        btreenode* bt;
        int req,i=1,num,ch;
        bt=NULL;
        fflush(stdin);
        while(1)
        {
                cout<<" \nBINARY TREE OPERATIONS:\n"<<"1. INSERTION:\n 2. DELETION:\n 3. TRAVERSAL:\n";
                cout<<"\nEnter the choice of operation:\n";
                cin>>ch;
                switch(ch)
                {
                        case 1: cout<<"\nEnter the value of the tree node to be inserted:\t";
                                        cin>>num;
                                        insert(&bt,num);
                                        break;
                        case 2: cout<<"\nEnter the value of the tree node to be deleted:\t";
                                        cin>>num;
                                        bdelete(&bt,num);
                                        break;
                        case 3: cout<<"\n1.INORDER TRAVERSAL:\n 2. PREORDER TRAVERSAL:\n 3.POSTORDER TRAVERSAL:\n ENTER your choice :";
                                        cin>>num;
                                        if(num==1)
                                                        inorder(bt);
                                        else if(num==2)
                                                        preorder(bt);
                                        else if(num==3)
                                                        postorder(bt);
                                        break;
                        default:break;
                }
        }
        return 0;
}

