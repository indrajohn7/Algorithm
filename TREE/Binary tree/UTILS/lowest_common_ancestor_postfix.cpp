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

/* Function to find LCA of n1 and n2.  
The function assumes that both  
n1 and n2 are present in BST */
btreenode *lca(btreenode* root, int n1, int n2)  
{  
    if (root == NULL) return NULL;  
	  
	// If both n1 and n2 are smaller 
	// than root, then LCA lies in left  
	if (root->data > n1 && root->data > n2)  
		return lca(root->lchild, n1, n2);  
						    
	// If both n1 and n2 are greater than  
	// root, then LCA lies in right  
	if (root->data < n1 && root->data < n2)  
		return lca(root->rchild, n1, n2);  
												  
	return root;  
}

btreenode* backtrace2(btreenode* bt, btreenode* node1, btreenode* node2)
{
	map<btreenode*, bool> path1, path2;
	while (node1 != bt) {
		path1[node1] = true;
		node1 = node1->parent;
	}
	while (node2 != bt) {
		path2[node2] = true;
		node2 = node2->parent;
	}
	
	for (map<btreenode*, bool> :: iterator it = path1.begin(); it != path1.end(); it++) {
		if (path2.find(it->first) != path2.end()) {
			return it->first;
		}
	}

	return NULL;
}

btreenode* backtrace(btreenode* bt, btreenode* node1, btreenode* node2)
{
	if(bt != NULL){
    	if (backtrace(bt->lchild, node1, node2) != NULL && backtrace(bt->rchild, node1, node2) != NULL)
			return bt;
       // backtrace(bt->rchild, node1, node2);
		
        cout<< bt->data << "\t";
		if (bt == node1 || bt == node2) {
			return bt;
		} else
			return NULL;
    }       
	else
		return NULL;
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
									ancestor = lca(bt, data1, data2);
									if (ancestor == NULL)
										ancestor = bt;
									cout << "Lowest Coomon Ancestor node in tree Through postorder traversal: " << ancestor << "::" <<ancestor->data << endl;
									
									ancestor = backtrace2(bt,node1,node2);
									if (ancestor == NULL)
										ancestor = bt;
									cout << "Lowest Coomon Ancestor node in tree Through recursion path traversal: " << ancestor << "::" <<ancestor->data << endl;
								}

								break;

                        default:
							break;
                }
        }
        return 0;
}

