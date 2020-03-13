#include<bits/stdc++.h>

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

// Stack type  
class Stack 
{  
    public: 
    int size;  
    int top;  
    Node** array;  
};  
  
// A utility function to create a new tree node  
Node* newNode(int data)  
{  
    Node* node = new Node(); 
    node->data = data;  
    node->left = node->right = NULL;  
    return node;  
}  


// A utility function to create a stack of given size  
Stack* createStack(int size)  
{  
    Stack* stack = new Stack(); 
    stack->size = size;  
    stack->top = -1;  
    stack->array = new Node*[(stack->size * sizeof(Node*))];  
    return stack;  
}  
  
// BASIC OPERATIONS OF STACK  
int isFull(Stack* stack)  
{  
    return stack->top - 1 == stack->size;  
}  
  
int isEmpty(Stack* stack)  
{  
    return stack->top == -1;  
}  
  
void push(Stack* stack, Node* node)  
{  
    if (isFull(stack))  
        return;  
    stack->array[++stack->top] = node;  
}  
  
Node* pop(Stack* stack)  
{  
    if (isEmpty(stack))  
        return NULL;  
    return stack->array[stack->top--];  
}  
  
// An iterative function to do post order 
// traversal of a given binary tree  
void postOrderIterative(Node* root)  
{  
    if (root == NULL)  
        return;  
  
    // Create two stacks  
    Stack* s1 = createStack(MAX_SIZE);  
    Stack* s2 = createStack(MAX_SIZE);  
  
    // push root to first stack  
    push(s1, root);  
    Node* node;  
  
    // Run while first stack is not empty  
    while (!isEmpty(s1))  
    {  
        // Pop an item from s1 and push it to s2  
        node = pop(s1);  
        push(s2, node);  
  
        // Push left and right children 
        // of removed item to s1  
        if (node->left)  
            push(s1, node->left);  
        if (node->right)  
            push(s1, node->right);  
    }  
  
    // Print all elements of second stack  
    while (!isEmpty(s2)) {  
        node = pop(s2);  
        cout<<node->data<<" ";  
    }  
}  



void iterativePreorder(btreenode *root) 
{ 
    // Base Case 
    if (root == NULL) 
       return; 
  
    // Create an empty stack and push root to it 
    stack<btreenode *> nodeStack; 
    nodeStack.push(root); 
  
    /* Pop all items one by one. Do following for every popped item 
       a) print it 
       b) push its right child 
       c) push its left child 
    Note that right child is pushed first so that left is processed first */
    while (nodeStack.empty() == false) 
    { 
        // Pop the top item from stack and print it 
        struct node *node = nodeStack.top(); 
        printf ("%d ", node->data); 
        nodeStack.pop(); 
  
        // Push right and left children of the popped node to stack 
        if (node->right) 
            nodeStack.push(node->right); 
        if (node->left) 
            nodeStack.push(node->left); 
    } 
} 

void iterativeinorder(btreeode* root) 
{ 
    stack<Node*> s; 
    btreenode* curr = root; 
  
    while (curr != NULL || s.empty() == false) 
    { 
        /* Reach the left most Node of the 
           curr Node */
        while (curr !=  NULL) 
        { 
            /* place pointer to a tree node on 
               the stack before traversing 
              the node's left subtree */
            s.push(curr);
            curr = curr->left; 
        } 
  
        /* Current must be NULL at this point */
        curr = s.top(); 
        s.pop(); 
  
  
        /* we have visited the node and its 
           left subtree.  Now, it's right 
           subtree's turn */
        curr = curr->right; 
  
    } /* end of while */
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
                cout<<" \nBINARY TREE OPERATIONS:\n"<<" 1. INSERTION:\n 2. DELETION:\n 3. TRAVERSAL:\n";
                cout<<"\nEnter the choice of operation:\n";
                cin>>ch;
                switch(ch)
                {
                        case 1: cout<<"\nEnter the value of the tree node to be inserted:\t";
                                        cin>>num;
                                        insert(bt_h,num);
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
                        default:
							break;
                }
        }
        return 0;
}

