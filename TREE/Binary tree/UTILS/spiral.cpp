#include <bits/stdc++.h>

using namespace std;

#define TRUE 1
#define FALSE 0

class btreenode{
        public:
        btreenode* lchild;
        int data;
        btreenode* rchild;
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
            if(((*tr)->data) < num)
                insert(&(*tr)->rchild,num);
            else
                insert(&(*tr)->lchild,num);

        }
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
        int *found;
        btreenode *parent,*x,*xsucc,*temp;
        if(*bt==NULL)
        {
                cout<<"Tree is Empty:\n";
                return;
        }
        parent=x=NULL;
        btreenode **par,**x1;
        temp=x;
        par=&parent;
        x1=&x;
        search(bt,num,par,x1,found);
        *bt=temp;
        if(*found==FALSE)
        {
                cout<<"Data not found in BTREE:\n";
                return;
        }
        parent=*par;
        x=*x1;
        if((x)->lchild!=NULL && (x)->rchild!=NULL){
                parent=x;
                xsucc=(x)->rchild;
                while(xsucc->lchild!=NULL){
                        parent=xsucc;
                        xsucc=xsucc->lchild;
                }
                (x)->data=xsucc->data;
                (x)=xsucc;
                delete(xsucc);
        }
        else if((x)->lchild==NULL && (x)->rchild!=NULL){
                if((parent)->rchild==(x))
                        (parent)->rchild=(x)->rchild;
                else
                        (parent)->lchild=(x)->rchild;
                delete(x);
                return;
        }
        else if((x)->lchild!=NULL && (x)->rchild==NULL){
                if((parent)->rchild==(x))
                        (parent)->rchild=(x)->lchild;
                else
                        (parent)->lchild=(x)->lchild;
                delete(x);
                return;
        }
        else if((x)->lchild==NULL && (x)->rchild==NULL){
                if((parent)->rchild==x)
                        (parent)->rchild=NULL;
                else
                        (parent)->lchild=NULL;
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
                preorder(bt->lchild);
                preorder(bt->rchild);
        }
        else
            return;
}

void postorder(btreenode* bt)
{
        if(bt!=NULL){
                postorder(bt->lchild);
                postorder(bt->rchild);
                cout<<bt->data<<"\t";
        }       
        else
            return;
}

int max_height(btreenode* bt)
{
    if(bt==NULL)
        return 0;

    else{
        int lheight=max_height(bt->lchild);
        int rheight=max_height(bt->rchild);

        if(lheight > rheight)
            return lheight+1;
        else
            return rheight+1;
    }
}


void print_level_tree(btreenode* bt,int h)
{
    if(bt==NULL)
        return;
    
    if(h==1)
        cout<<bt->data<<"\t";
    else{
        if(h%2){
            print_level_tree(bt->lchild, h-1);
            print_level_tree(bt->rchild, h-1);
        }else {
            
            print_level_tree(bt->rchild, h-1);
            print_level_tree(bt->lchild, h-1);
        }
    }
    
}


void spiral_taverse(btreenode* root)
{
	stack<btreenode*> st_lchild, st_rchild;
	st_lchild.push(root);
	bool lchild, rchild;
	lchild = true;
	rchild = false;

	while(st_lchild.empty() == false || st_rchild.empty() == false) {
		
		if (lchild && st_lchild.empty() == false) {
			btreenode* elem = st_lchild.top();
			st_lchild.pop();
			cout << elem->data << " ";
			if (elem->rchild) {
				st_rchild.push(elem->rchild);
			}
			if (elem->lchild) {
				st_rchild.push(elem->lchild);
			}
			if (st_lchild.empty()) {
				lchild = false;
				rchild = true;
			}
		} else if (rchild && st_rchild.empty() == false) {
			
			btreenode* elem = st_rchild.top();
			st_rchild.pop();
			cout << elem->data << " ";
			if (elem->lchild) {
				st_lchild.push(elem->lchild);
			}
			if (elem->rchild) {
				st_lchild.push(elem->rchild);
			}
			if (st_rchild.empty()) {
				rchild = false;
				lchild = true;
			}
		}
	}
	cout << endl;
}


int main()
{
        btreenode *bt,**bt_h;
        int req,i=1,num,ch,height;
        bt=NULL;
        bt_h=&bt;
        fflush(stdin);
        while(1)
        {
        	cout<<" \nBINARY TREE OPERATIONS:\n"<<" 1. INSERTION:\n 2. DELETION:\n 3. TRAVERSAL:\n 4.Height Traversal Print:\n 5.Spiral traversal:\n";
            cout<<"\nEnter the choice of operation:\n";
            cin>>ch;
            switch(ch)
            {
                   case 1: 	cout<<"\nEnter the value of the tree node to be inserted:\t";
                           	cin>>num;
                          	insert(bt_h,num);
                            break;
                   case 2: 	cout<<"\nEnter the value of the tree node to be deleted:\t";
                            cin>>num;
                            bdelete(bt_h,num);
                            break;
                   case 3: 	cout<<"\n1.INORDER TRAVERSAL:\n 2. PREORDER TRAVERSAL:\n 3.POSTORDER TRAVERSAL:\n ENTER your choice :";
                            cin>>num;
                            if(num==1)
                            	inorder(bt);
                            else if(num==2)
                            	preorder(bt);
                            else if(num==3)
                            	postorder(bt);
                                break;
                   case 4: 	cout<<"Height Traversal Print of the Tree:\n";
                           	height=max_height(bt);
                            for(int i=1;i<=height;i++){
                            	cout<<i<<":: ";
                                print_level_tree(bt,i);
                                cout<<endl;
                            }
                            break;
					case 5:	cout << "Spiral print of the Tree:\n";
							spiral_taverse(bt);
							break;
                    default:
                           	return 0;
            }
        }
        return 0;
}

