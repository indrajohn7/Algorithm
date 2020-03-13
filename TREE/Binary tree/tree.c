#include<stdio.h>
#include<stdlib.h>

//using namespace std;
#define TRUE 1
#define FALSE 0

typedef struct _btreenode{
        struct _btreenode* lchild;
        int data;
        struct _btreenode* rchild;
}btreenode;

void insert(btreenode** tr,int num)
{
        if(*tr==NULL)
        {
                *tr=(btreenode*)malloc(sizeof(btreenode));
                (*tr)->lchild=NULL;
                (*tr)->rchild=NULL;
                (*tr)->data=num;
                return;
        }
        else{
                btreenode *temp,*r,*p,*parent;
				temp=*tr;
				r=temp;
				while(temp!=NULL)
				{				
					if(num>temp->data)
					{
						parent=temp;
						temp=temp->rchild;
					}
					else
					{
						parent=temp;
                        temp=temp->lchild;
					}
				}
				p=(btreenode*)malloc(sizeof(btreenode));
				(p)->lchild=NULL;
                (p)->rchild=NULL;
                (p)->data=num;
					if(temp==parent->rchild)
					{
						temp=parent;
						temp->rchild=p;
					}
					else if(temp==parent->lchild){
						temp=parent;
						temp->lchild=p;
					}
				*tr=r;
				return;
        }
        return;
}

void search(btreenode** bt,int num,btreenode** par,btreenode**x,int *found)
{
         btreenode* q;
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
        btreenode *parent,*temp;
		btreenode *x;
		btreenode *xsucc;
        if(*bt==NULL)
        {
                printf("Tree is Empty:\n");
                return;
        }
        parent=NULL;
		x =NULL;
		temp=x;
		*bt=temp;
        search(bt,num,&parent,&x,&found);
        if(found==FALSE)
        {
                printf("Data not found in BTREE:\n");
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
                free(x);
                return;
        }
        else if(x->lchild!=NULL && x->rchild==NULL){
                if(parent->rchild==x)
                        parent->rchild=x->lchild;
                else
                        parent->lchild=x->lchild;
                free(x);
                return;
        }
        else if(x->lchild==NULL && x->rchild==NULL){
                if(parent->rchild==x)
                        parent->rchild=NULL;
                else
                        parent->lchild=NULL;
                free(x);
                return;
        }
}


void inorder(btreenode* bt)
{
        if(bt!=NULL){
                inorder(bt->lchild);
                printf("%d\t",bt->data);
                inorder(bt->rchild);
        }
        else
			return;
}

void preorder(btreenode* bt)
{
        if(bt!=NULL){
                printf("%d\t",bt->data);
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
                printf("%d\t",bt->data);
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
                printf(" \nBINARY TREE OPERATIONS:\n 1. INSERTION:\n 2. DELETION:\n 3. TRAVERSAL:\n");
                printf("\nEnter the choice of operation:\n");
                scanf("%d",&ch);
                switch(ch)
                {
                        case 1: printf("\nEnter the value of the tree node to be inserted:\t");
                                        scanf("%d",&num);
                                        insert(&bt,num);
                                        break;
                        case 2: printf("\nEnter the value of the tree node to be deleted:\t");
                                        scanf("%d",&num);
                                        bdelete(&bt,num);
                                        break;
                        case 3: printf("\n1.INORDER TRAVERSAL:\n 2. PREORDER TRAVERSAL:\n 3.POSTORDER TRAVERSAL:\n ENTER your choice :");
                                        scanf("%d",&num);
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

