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

void topview_traverse(btreenode* root)
{
	btreenode *left, *right;
	cout << root->data << " ";
	left = root->lchild;
	right = root->rchild;

	while (left || right) {
		if (left) {
			cout << left->data << " ";
			left = left->lchild;
		}
		if (right) {
			cout << right->data << " ";
			right = right->rchild;
		}
	}

	cout << endl;
}

void top_view_traverse(btreenode* root)
{
	typedef pair<int, int> pii;
	typedef pair<btreenode*, pii> pbt;
	//pair<btrenode*, pair<level, width>>	object for each node element

	stack<pbt> st_lchild, st_rchild;
	int level, width;
	level = 1;
	width = 0;
	pii p = make_pair(level, width);
	pbt pb = make_pair(root, p);
	st_lchild.push(pb);
	bool lchild, rchild;
	lchild = true;
	rchild = false;
	int min_width, max_width, max_level, max_diff;
	min_width = INT_MAX;
	max_width = max_diff = INT_MIN;
	max_level = level;
	stack<pbt> st;
	stack<btreenode*> top_view;
	top_view.push(root);
	btreenode *max_view, *min_view;
	max_view = min_view = NULL;
	int view_min, view_max;
	view_min = view_max = 0;
	bool right_view, left_view;
	right_view = left_view = false;

	while(st_lchild.empty() == false || st_rchild.empty() == false) {
		
		if (lchild && st_lchild.empty() == false) {
			btreenode* elem = st_lchild.top().first;
			width = st_lchild.top().second.second;
			st_lchild.pop();
			cout << elem->data << " ";
			if (elem->rchild) {
				
				st_rchild.push(make_pair(elem->rchild, make_pair(level, width + 1)));
				if (width + 1 > max_width) {
					max_width = width + 1;
				}
				if (width + 1 > view_max) {
					view_max = width + 1; 
					max_view = elem->rchild;
					right_view = true;
				}
			}
			if (elem->lchild) {
				st_rchild.push(make_pair(elem->lchild, make_pair(level, width - 1)));
				if (width - 1 < min_width) {
					min_width = width - 1;
				}
				if (width - 1 < view_min) {
					view_min = width - 1;
					min_view = elem->lchild;
					left_view = true;
				}
			}
			if (st_lchild.empty()) {
				if (st.empty()) {
					st = st_rchild;
					max_level = level;
					max_diff = max_width - min_width;
				} else if (max_diff < (max_width - min_width)){
					st = st_rchild;
					max_level = level;
					max_diff = (max_width - min_width);
				}
				level += 1;
				lchild = false;
				rchild = true;
				min_width = INT_MAX;
				max_width = INT_MIN;
				if (min_view) {
					top_view.push(min_view);
				}
				if (max_view) {
					top_view.push(max_view);
				}
				max_view = min_view = NULL;
			}
		} else if (rchild && st_rchild.empty() == false) {
			
			btreenode* elem = st_rchild.top().first;
			width = st_rchild.top().second.second;
			st_rchild.pop();
			cout << elem->data << " ";
			if (elem->lchild) {
				st_lchild.push(make_pair(elem->lchild, make_pair(level, width - 1)));
				if (width - 1 < min_width) {
					min_width = width - 1;
				}
				if (width - 1 < view_min) {
					view_min = width - 1;
					min_view = elem->lchild;
					left_view = true;
				}
			}
			if (elem->rchild) {
				st_lchild.push(make_pair(elem->rchild, make_pair(level, width + 1)));
				if (width + 1 > max_width) {
					max_width = width + 1;
				}
				if (width + 1 > view_max) {
					view_max = width + 1; 
					max_view = elem->rchild;
					right_view = true;
				}
			}
			if (st_rchild.empty()) {
				if (st.empty()) {
					st = st_lchild;
					max_level = level;
					max_diff = (max_width - min_width);
				} else if (max_diff < (max_width - min_width)){
					st = st_lchild;
					max_level = level;
					max_diff = (max_width - min_width);
				}
				level += 1;
				rchild = false;
				lchild = true;
				min_width = INT_MAX;
				max_width = INT_MIN;
				if (min_view) {
					top_view.push(min_view);
				}
				if (max_view) {
					top_view.push(max_view);
				}
				max_view = min_view = NULL;
			}
		}
	}
	cout << endl;

	cout << "Diameter at level: " << max_level << " with a length: " << max_diff << " With number of #" << st.size() << " elements" << endl;
	while (st.empty() == false) {
		cout << st.top().first->data << " ";
		st.pop();
	}
	cout << endl;

	cout << "TopView of the Tree: " << endl;
	while (top_view.empty() == false) {
		cout << top_view.top()->data << " ";
		top_view.pop();
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
        	cout<<" \nBINARY TREE OPERATIONS:\n"<<" 1. INSERTION:\n 2. DELETION:\n 3. TRAVERSAL:\n 4.Height Traversal Print:\n 5.Spiral traversal:\n 6. Top View\n";
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
					case 6:	cout << "Top view print of the Tree:\n";
							top_view_traverse(bt);
							break;
                    default:
                           	return 0;
            }
        }
        return 0;
}

