#include<bits/stdc++.h>

using namespace std;
#define TRUE 1
#define FALSE 0

class btreenode{
        public:
        btreenode* lchild;
        int data;
        btreenode* rchild;
		btreenode* parent;
};

void insert(btreenode** tr,btreenode* parent,int num)
{
        if(*tr==NULL)
        {
                *tr=new btreenode;
                (*tr)->lchild=NULL;
                (*tr)->rchild=NULL;
                (*tr)->data=num;
				(*tr)->parent=parent;
                return;
        }
        else{
			if(((*tr)->data) < num){
				(*tr)->parent=parent,
				insert(&(*tr)->rchild,*tr,num);
			}
			else{
				(*tr)->parent=parent;
				insert(&(*tr)->lchild,*tr,num);
			}

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

typedef map<int,btreenode*> vmap;
vmap map1,map2;
typedef vector<btreenode*> vvec;
vvec vec1,vec2;

btreenode* backtrace(btreenode* bt, btreenode* node1, btreenode* node2)
{
	if(node1 == NULL && node2 == NULL){
		/*
		for(vmap::iterator it=map1.begin();it!=map1.end();it++){
			if(map2.find(it->first) != map2.end()){
				return it->second;
			}
		}
		*/
		for(int i=0;i<vec1.size();i++){
			for(int j=0;j<vec2.size();j++){
				if(vec1[i] == vec2[j])
					return vec1[i];
			}
		}
		cout<<"Head is the Lowest common ancestor for these 2 nodes:\n";
		return bt;
	}

	else{
		if(node1 == NULL)
			node1=bt;
		if(node2 == NULL)
			node2=bt;
		if(node1 == node2){
			return node1;
		}else{
			if(node1 && map1.find(node1->data) == map1.end()){
				map1[node1->data]=node1;
				vec1.push_back(node1);
			}
			if(node2 && map2.find(node2->data) != map2.end()){
				map2[node2->data]=node2;
				vec2.push_back(node2);
			}
			
			backtrace(bt,node1->parent,node2->parent);
		}
	}
}


btreenode* search(btreenode* bt,int data)
{
	if(bt==NULL){
		cout<<"Data is not present in the binary tree:\n";
		return NULL;
	}else if(bt->data == data){
		return bt;
	}else if(data > bt->data){
		search(bt->rchild,data);
	}else if(data < bt->data)
		search(bt->lchild,data);
}

int main()
{
        btreenode *bt,**bt_h,*ancestor,*node1,*node2;
        int req,i=1,num,ch,data1,data2;
        bt=NULL;
		bt_h=&bt;
        fflush(stdin);
        while(1)
        {
                cout<<" \nBINARY TREE OPERATIONS:\n"<<" 1. INSERTION:\n 2. DELETION:\n 3. TRAVERSAL:\n 4. Lowest Common Ancestor:\n";
                cout<<"\nEnter the choice of operation:\n";
                cin>>ch;
                switch(ch)
                {
                        case 1: cout<<"\nEnter the value of the tree node to be inserted:\t";
                                        cin>>num;
                                        insert(bt_h,NULL,num);
                                        break;
                        case 2: cout<<"\nEnter the value of the tree node to be deleted:\t";
                                        cin>>num;
                                        bdelete(bt_h,num);
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
						case 4: cout<<"Input 2 elements for whose you need to find the lowest common ancestor:\n";
								cin>>data1>>data2;
								node1=search(bt,data1);
								node2=search(bt,data2);
								if(node1 == NULL || node2 == NULL){
									cout<<"Data not found in the following tree:\n";
								}else{
									ancestor=backtrace(bt,node1,node2);
									cout<<"Lowest Coomon Ancestor node in tree: "<<ancestor<<"::"<<ancestor->data<<endl;
								}

								break;

                        default:
							break;
                }
        }
        return 0;
}

