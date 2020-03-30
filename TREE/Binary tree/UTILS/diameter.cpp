#include<bits/stdc++.h>

using namespace std;
#define TRUE 1
#define FALSE 0

class btreenode{
        public:
        btreenode* lchild;
        int data;
        btreenode* rchild;
		int width;
};

void insert(btreenode** tr,int num,int w)
{
        if(*tr==NULL)
        {
                *tr=new btreenode;
                (*tr)->lchild=NULL;
                (*tr)->rchild=NULL;
                (*tr)->data=num;
				(*tr)->width=w;
                return;
        }
        else{
			if(((*tr)->data) < num)
				insert(&(*tr)->rchild,num,w+1);
			else
				insert(&(*tr)->lchild,num,w-1);

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

int get_min_width(btreenode* bt)
{
		int min;
		while(bt->lchild!=NULL){
			bt=bt->lchild;
		}
		min=bt->width;
		return min;
}


int get_max_width(btreenode* bt)
{
		int max;
		while(bt->rchild!=NULL){
			bt=bt->rchild;
		}
		max=bt->width;
		return max;
}

void print_pattern(btreenode* bt,int width)
{
	
        if(bt!=NULL){
                print_pattern(bt->lchild,width);
				if(bt->width == width) 
                	cout<<bt->data<<"\t";
                print_pattern(bt->rchild,width);
        }
        else
			return;
}


void diameter_traverse(btreenode* root)
{
	typedef pair<int, int> pii;
	typedef pair<btreenode*, pii> pbt;
	
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
			}
			if (elem->lchild) {
				st_rchild.push(make_pair(elem->lchild, make_pair(level, width - 1)));
				if (width - 1 < min_width) {
					min_width = width - 1;
				}
			}
			if (st_lchild.empty()) {
				if (st.empty()) {
					st = st_rchild;
					max_level = level;
					max_diff = abs (max_width - min_width);
				} else if (max_diff < abs(max_width - min_width)){
					st = st_rchild;
					max_level = level;
					max_diff = abs (max_width - min_width);
				}
				level += 1;
				lchild = false;
				rchild = true;
				min_width = INT_MAX;
				max_width = INT_MIN;
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
			}
			if (elem->rchild) {
				st_lchild.push(make_pair(elem->rchild, make_pair(level, width + 1)));
				if (width + 1 > max_width) {
					max_width = width + 1;
				}
			}
			if (st_rchild.empty()) {
				if (st.empty()) {
					st = st_lchild;
					max_level = level;
					max_diff = abs (max_width - min_width);
				} else if (max_diff < abs(max_width - min_width)){
					st = st_lchild;
					max_level = level;
					max_diff = abs (max_width - min_width);
				}
				level += 1;
				rchild = false;
				lchild = true;
				min_width = INT_MAX;
				max_width = INT_MIN;
			}
		}
	}
	cout << endl;

	cout << "Diameter at level: " << max_level << " with a length: " << st.size() << endl;
	while (st.empty() == false) {
		cout << st.top().first->data << " ";
		st.pop();
	}

	cout << endl;

}

int main()
{
        btreenode *bt,**bt_h;
        int req,i=1,num,ch,min,max;
        bt=NULL;
		bt_h=&bt;
        fflush(stdin);
        while(1)
        {
                cout<<" \nBINARY TREE OPERATIONS:\n"<<"1. INSERTION:\n 2. DELETION:\n 3. TRAVERSAL:\n 4.Horizontal Traversal:\n 5. Diameter Of Tree:\n";
                cout<<"\nEnter the choice of operation:\n";
                cin>>ch;
                switch(ch)
                {
                        case 1: cout<<"\nEnter the value of the tree node to be inserted:\t";
                                        cin>>num;
                                        insert(bt_h,num,0);
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
						case 4: cout<<"Error Diametric Print of a Tree:\n";
								min=get_min_width(bt);
								max=get_max_width(bt);
								cout<<"MIN: "<<min<<"\tMAX: "<<max<<endl;
								for(int i=min;i<=max;i++){
									print_pattern(bt,i);
									cout<<"\n";
								}
								break;
						case 5:	cout << "Diameter Of a Tree:\n";
								diameter_traverse(bt);
								break;
                        default:
							return 0;;
                }
        }
        return 0;
}

