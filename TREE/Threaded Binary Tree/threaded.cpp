#include<bits/stdc++.h>

using namespace std;

class btreenode{
        public:
        btreenode* lchild;
        int data;
        btreenode* rchild;
		btreenode* parent;
		char wchild;
};


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
				int left=0,right=0;
                btreenode *temp,*r,*p,*par;
				temp=*tr;
				r=temp;
				while(temp!=NULL)
				{				
					if(num>temp->data)
					{
						par=temp;
						par->lchild=temp->lchild;
						par->rchild=temp->rchild;
						temp=temp->rchild;
						right=1;
						left=0;
					}
					else
					{
						par=temp;
						par->lchild=temp->lchild;
						par->rchild=temp->rchild;
                        temp=temp->lchild;
						right=0;
						left=1;
					}
				}
				p=new btreenode;
				(p)->lchild=NULL;
                (p)->rchild=NULL;
                (p)->data=num;

					if(right==1)
					{
						temp=par;
						temp->rchild=p;
						temp=temp->rchild;
						temp->parent=par;
						temp->wchild='r';
					}
					else if(left==1){
						temp=par;
						temp->lchild=p;
						temp=temp->lchild;
						temp->parent=par;
						temp->wchild='l';
					}
				*tr=r;
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

void Predec(btreenode* bt,int num)
{
	btreenode* cur=NULL;
	btreenode* temp=NULL;
	while(bt!=NULL){
		if(bt->data==num)
			break;
		if(bt->data>num)
		{
			temp=bt;
			bt=bt->lchild;
			bt->parent=temp;	
		}
		else{
			cur=bt;
			bt=bt->rchild;
			bt->parent=cur;
		}
	}
	if(bt==NULL){
		cout<<"Invalid NODE:\n";
		return;
	}
	if(bt->wchild=='l'){
		if(bt->lchild!=NULL)
			cout<<"predecessor of the given node is it's LEFT_CHILD:\t"<<bt->lchild->data<<endl;
		else if(cur!=NULL)
			cout<<"predecessor of the given node is it's right predecessor:\t"<<cur->data<<endl;
		else if(cur==NULL)
			cout<<"Given NODE is minimum SO PREDECESSOR is not posssible:\n";
	}
	else if(bt->wchild=='r'){
		if(bt->lchild!=NULL)
			cout<<"predecessor of the given node is it's LEFT_CHILD:\t"<<bt->lchild->data<<endl;
		else 
			cout<<"predecessor of the given node is it's Parent Node:\t"<<bt->parent->data<<endl;
	}
}

void Successor(btreenode* bt,int num)
{
	btreenode* cur=NULL;
	btreenode* temp=NULL;
	while(bt!=NULL){
		if(bt->data==num)
			break;
		if(bt->data>num){
			cur=bt;
			temp=bt;
			bt=bt->lchild;
			bt->parent=temp;
		}			
		else{
		//	cur=bt;
			temp=bt;
			bt=bt->rchild;
			bt->parent=temp;
		}
	}
	if(bt==NULL){
		cout<<"Invalid NODE:\n";
		return;
	}
	if(bt->wchild=='l'){
		if(bt->rchild!=NULL){
			bt=bt->rchild;
			while(bt->lchild!=NULL)
				bt=bt->lchild;
			cout<<"Successor of the given node is it's right Successor:\t"<<bt->data<<endl;
		}
		else
			cout<<"Successor of the given node is it's Parent:\t"<<bt->parent->data<<endl;
			
	}
	else{
		if(bt->rchild!=NULL){
						bt=bt->rchild;
			while(bt->lchild!=NULL)
				bt=bt->lchild;
			cout<<"Successor of the given node is it's right Successor:\t"<<bt->data<<endl;
		}
		else if(cur==NULL)
			cout<<"Given NODE is the max value, So it does not have any Successor:\n";
		else if(cur!=NULL)
			cout<<"Successor of the given node is it's left recursive NODE:\t"<<cur->data<<endl;
	}
}


void remove(btreenode** bt)
{
	btreenode* temp;
	temp=*bt;
	if(temp!=NULL){
		remove(&(temp->lchild));
		remove(&(temp->rchild));
		*bt=temp->parent;
		delete temp;
	}
	else
		return;
}

int main()
{
        btreenode *bt,**bt_h;
        int req,i=1,num,ch;
        bt=NULL;
		bt_h=&bt;
        fflush(stdin);
        while(1)
        {
                cout<<" \n Threaded BINARY TREE OPERATIONS:\n"<<"1. INSERTION:\n 2. TRAVERSAL:\n 3. PREDECESSOR OF A NODE:\n 4. SUCCESSOR OF A NODE:\n5.Delete the TREE:\n";
                cout<<"\nEnter the choice of operation:\n";
                cin>>ch;
                switch(ch)
                {
                        case 1: cout<<"\nEnter the value of the tree node to be inserted:\t";
                                        cin>>num;
                                        insert(bt_h,num);
                                        break;
                        case 3: cout<<"\nEnter the value of the tree node for which PREDECESSOR will be found:\t";
                                        cin>>num;
                                        Predec(bt,num);
                                        break;
						case 4: cout<<"\nEnter the value of the tree node for which SUCCESSOR will be found:\t";
                                        cin>>num;
                                        Successor(bt,num);
                                        break;
                        case 2: cout<<"\n1.INORDER TRAVERSAL:\n 2. PREORDER TRAVERSAL:\n 3.POSTORDER TRAVERSAL:\n ENTER your choice :";
                                        cin>>num;
                                        if(num==1)
                                        	inorder(bt);
                                        else if(num==2)
                                        	preorder(bt);
                                        else if(num==3)
                                        	postorder(bt);
                                        break;
                        case 5: cout<<"\nDelete the tree:\n";
								remove(bt_h);	
								break;
						default:break;
                }
        }
        return 0;
}
