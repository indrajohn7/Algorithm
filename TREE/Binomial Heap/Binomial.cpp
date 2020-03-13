#incude<bits.stdc++.h>

using namespace std;

class Binomial{
	Binomial* head;
	Binomial* parent;
	Binomial* child;
	Binomial* sibling;
	int data;
	int num_sibling;
	int num_child;
	int degree;
};

Binomial Make_Binomial_Heap_Head()
{
	Binomial* bnm=new Binomial;
	bnm->head=NULL;
	return (bnm);
}

Binomial* Binomial_Heap_Marge(Binomial H1, Binomial H2)
{
	Binomial* bnm=Make_Binomial_Heap_Head();
	Binomial* Head=Make_Binomial_Heap_Head();
	bnm->parent=NULL;
	bnm->child=NULL;
	bnm->sibling=NULL;
	bnm->degree=0;
	bnm->head=bnm;
	bnm->num_sibling=0;
	bnm->num_child=0;
	Head=bnm;
	while(H1!=NULL && H2!=NULL){
		if(H1.degree<H2.degree)
			*bnm=H1;
		else
			*bnm=H2;
		H1=H1.sibling;
		H2=H2.sibling;
		bnm=bnm->sibling;
	}
	while(H1!=NULL){
		*bnm=H1;
		H1=H1.sibling;
		bnm=bnm->sibling;
	}
	while(H2!=NULL){
		*bnm=H2;
		H2=H2.sibling;
		bnm=bnm->sibling;
	}
	return Head;
}

void Binomial_link(Binomial* y,Binomial* z)
{
	y->parent=z;
	y->sibling=z->child;
	z->child=y;
	z->degree+=1;
}

Binomial* Binomial_Heap_Union(Binomial H1,Binomial H2)
{
	Binomial* bnm=Make_Binomial_Heap_Head();
	bnm->head=Binomial_Heap_Marge(H1,H2);
	if(bnm->head==NULL)
		return bnm;
	Binomial* x=new Binomial;
	Binomial* prev_x=new Binomial;
	Binomial* next_x=new Binomial;
	prev_x=NULL;
	*x=bnm->head;
	next_x=x->sibling;
	while(next_x!=NULL){
		if((x->degree!=next_x->degree) ||(next_x->sibling!=NULL && next_x->sibling->degree==x->degree)){
			prev_x=x;
			x=next_x;
		}
		else if(x->data<=next_x->data){
			x->sibling=next_x->sibling;
			Binomial_link(next_x,x);
		}
		else if(prev_x==NULL){
			bnm->head=next_x;
		}
		else{
			prev_x->sibling=next_x;
			Binomial_link(x,next_x);
			x=next_x;
		}
		next_x=x->sibling;
		return bnm;
	}
}

void Binomial_Heap_Insert(Binomial** Head,int x)
{
	Binomial* bnm=Make_Binomial_Heap_Head();
	bnm->parent=NULL;
	bnm->child=NULL;
	bnm->sibling=NULL;
	bnm->degree=0;
	bnm->head=bnm;
	bnm->data=x;
	bnm->num_sibling=0;
	bnm->num_child=0;
	if(*Head->head==NULL)
		*Head=bnm;
	else
		*Head=Binomial_Heap_Union(**Head,*bnm);
}



int main()
{
	//////CREATION OF HEAP1////////////
	char str[20];
	cout<<"Please provide the binary pseudocode for Heap1:	";
	cin>>str;
	vector<Binomial> Root(strlen(str));
	int k=0,i;
	srand (time(NULL));
	for(i=strlen(str)-1;i>=0;i--){
		if(str[i]==1){
			Binomial* bnm;
			Binomial** bnm_h;
			bnm=Make_Binomial_Heap_Head();
			bnm_h=&bnm;
			Root[k++]=*bnm;
			for(int j=0;j<pow(2,i);j++){
				Binomial_Heap_Insert(bnm_h,rand()%1000);
			//	bnm->degree=j;
			}
		}			
	}
	
}