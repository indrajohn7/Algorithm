#include<bits/stdc++.h>

using namespace std;
#define TRUE 1
#define FALSE 0
#define LEFT -1
#define RIGHT 1

class btreenode{
        public:
        btreenode* lchild;
        int data;
        btreenode* rchild;
		btreenode* parent;
		int height;
};

/*
 * All the rotation operations are local to the respective APIs ,
 * since the caller is calling the APIs through only pointers and not by addresses
 * hence the complete tree would noit be reflected the changes.
 *
 * Pls have a global head node of the tree which would be maintained through all these
 * operations and head node would automatically be updated.
 *
 *
 * */


/* Performing a right rotation  operation across the node tr
 * */

void do_ll_rotation(btreenode** head, btreenode* tr)
{
	btreenode *temp_right,*temp_left,*temp_parent;
	temp_right=temp_left=NULL;
	temp_parent=tr->parent->parent;
	
	if(temp_parent->lchild == tr->parent)
		temp_parent->lchild=tr;
	else
		temp_parent->rchild=tr;
	
	temp_right = tr->rchild;
	tr->rchild=tr->parent;
	tr->parent->lchild==temp_right;
	/*Update Parent*/
	tr->parent=temp_parent;
}

/* Performing a left operation across the node tr
 * */
void do_rr_rotation(btreenode** head, btreenode* tr)
{
	btreenode *temp_right,*temp_left,*temp_parent;
	temp_right=temp_left=NULL;
	temp_parent=tr->parent->parent;
	
	if(temp_parent->lchild == tr->parent)
		temp_parent->lchild=tr;
	else
		temp_parent->rchild=tr;
	
	temp_left = tr->lchild;
	tr->lchild=tr->parent;
	tr->parent->rchild==temp_left;
	/*Update Parent*/
	tr->parent=temp_parent;
}


void do_rl_rotation(btreenode** head, btreenode* tr)
{
	do_ll_rotation(head,tr->lchild);
	do_rr_rotation(head,tr->lchild);

}


void do_lr_rotation(btreenode** head, btreenode* tr)
{
	do_rr_rotation(head,tr->rchild);
	do_ll_rotation(head,tr->rchild);

}


void check_balance_type(btreenode** head, btreenode* tr,int type)
{
	if((tr)->lchild == NULL && (tr)->rchild == NULL){
		//do nothing
	}else if(tr->lchild == NULL && tr->rchild->height > 1){
		
		if(type == LEFT)
			do_lr_rotation(head,tr);
		else
			do_rr_rotation(head,tr);

	}else if(tr->rchild == NULL && tr->lchild->height >1){
		
		if(type == LEFT)
			do_ll_rotation(head,tr);
		else
			do_rl_rotation(head,tr);
	
	}else if(abs(tr->lchild->height - tr->rchild->height) > 1){
		

		
		if(tr->lchild->height > tr->rchild->height){
			if(type == LEFT)
				do_ll_rotation(head,tr);
			else
				do_rl_rotation(head,tr);
		}
		else{
			if(type == LEFT)
				do_lr_rotation(head,tr);
			else
				do_rr_rotation(head,tr);
		}
	
	}
}

void check_avl_properties(btreenode** head,btreenode* tr)
{
	if(tr == NULL){
		return;
	}else{
		check_avl_properties(head,(tr)->lchild);
		check_avl_properties(head,(tr)->rchild);
		if((tr)->lchild == NULL && (tr)->rchild == NULL){
			//do nothing
		}else if(tr->lchild == NULL && tr->rchild->height > 1){
			check_balance_type(head,tr->rchild,RIGHT);
		}else if(tr->rchild == NULL && tr->lchild->height >1){
			check_balance_type(head,tr->lchild,LEFT);
		}else if(abs(tr->lchild->height - tr->rchild->height) > 1){
			if(tr->lchild->height > tr->rchild->height)
				check_balance_type(head,tr->lchild,LEFT);
			else
				check_balance_type(head,tr->rchild,RIGHT);
		}
	}
}

int  max_height(btreenode* bt)
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


void maintain_tree_height_property(btreenode* tr)
{
	if((tr)==NULL)
		return;
	else{
		tr->height = max_height(tr);
		maintain_tree_height_property(tr->lchild);
		maintain_tree_height_property(tr->rchild);
	}
}

void insert(btreenode** tr,btreenode* parent,int num, int height)
{
        if(*tr==NULL)
        {
                *tr=new btreenode;
                (*tr)->lchild=NULL;
                (*tr)->rchild=NULL;
                (*tr)->data=num;
				(*tr)->parent=parent;
				if(parent && parent->height < height)
					(*tr)->parent->height=height; // max height of any branch will be overwritten
                check_avl_properties(tr,*tr);
				maintain_tree_height_property(*tr);
				return;

        }
        else{
			if(((*tr)->data) < num){
				(*tr)->parent=parent,
				insert(&(*tr)->rchild,*tr,num,height+1);
			}
			else{
				(*tr)->parent=parent;
				insert(&(*tr)->lchild,*tr,num,height+1);
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
                                        insert(bt_h,NULL,num,1);
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

