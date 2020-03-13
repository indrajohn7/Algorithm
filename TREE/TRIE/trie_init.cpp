#include<bits/stdc++.h>

using namespace std;
#define NUM 26
#define size 20

class trie{
	public:
	char c;
	int words;
	int prefix;
	int child;
	bool visited;
	trie* edges[NUM];
	trie* parent;
	trie(char w,trie* par){
		words=0;
		prefix=0;
		c=w;
		child=0;
		parent=par;
		visited=false;
		for(int i=0;i<NUM;i++)
			edges[i]=NULL;
	}
};

void create_word(trie** head,char* str)
{
	int i;
	trie* temp=*head;
	for(i=0;i<strlen(str);i++){
		if(temp->edges[str[i]-'A']==NULL){
			temp->edges[str[i]-'A'] = new trie(str[i],temp);
			temp->child++;
			temp=temp->edges[str[i]-'A'];
		}
		else {
			temp=temp->edges[str[i]-'A'];
		}
	}
	temp->words=1;
}


void search_word(trie** head,char* str)
{
	int i;
	trie* temp=*head;
	for(i=0;i<strlen(str);i++){
		if(temp->edges[str[i]-'A']==NULL){
			cout<<"CASE #\t"<<"NOT FOUND\n";
			return;
		}
		else {
			temp=temp->edges[str[i]-'A'];
		}
	}
	cout<<"CASE #\t"<<"FOUND\n";
}

void search_prefix(trie* head ,char* str)
{
	int i;
	trie* temp=head;
	for(int iter=0;iter<NUM;iter++){
		
	for(i=0;i<NUM;i++){		
		if(temp->edges[i]!=NULL){
			temp=temp->edges[i];
			trie* parent=temp;
			trie* par=parent;
			int l=0;
			for(int j=0;j<NUM && temp;j++){
				if(temp!=NULL && temp->edges[j]!=NULL && temp->c!=str[0] && temp->child>0 && temp->edges[j]->visited==false){
					parent=temp;
					temp->visited=true;
					temp=temp->edges[j];
					temp->visited=true;
					parent->visited=true;
					j=0;
				}
				else if(temp!=NULL && temp->child==0){
					//j=0;
					temp=parent;
					parent=parent->parent;
				}
				else if(temp!=NULL && temp->c==str[0]){// && temp->edges[str[1]-'A']!=NULL && temp->edges[str[1]-'A']->visited==false){
					trie* t=temp;
					int flag=0,k;
					t->visited=true;
					for(k=1;k<strlen(str);k++){
						if(t->edges[str[k]-'A']==NULL){
							flag=1;
							break;
						}
						else{
							t=t->edges[str[k]-'A'];
							t->visited=true;
						}
					}
					if(flag==0){
						cout<<str<<"\tFOUND\n";     //backtracing needs to be done
						j=l++;
						temp=head->edges[j];
					//	break;
						    if(parent!=par){
								temp=temp->parent;
								parent=parent->parent;
							}
						} 
					else{
						if(temp->edges[j]!=NULL && temp->edges[j]->visited==false){
							parent=temp;
							temp=temp->edges[j];
						}
							
					}
				/*	else{
						for(int l=0;l<(k-1);l++){
							temp=temp->parent;
							parent=parent->parent;
						}
					} */
				}
				else if(temp!=NULL && temp->edges[j]!=NULL && temp->edges[j]->visited==true)
					continue;
				else if(j==NUM-1 && temp->edges[j]==NULL){
			//		cout<<str<<"\n";
					temp=temp->parent;
					parent=parent->parent;
				}
			}
		}
	}
			if(head->edges[iter]!=NULL)
				temp=head->edges[iter];
	}
}

int main()
{
//	trie* head=NULL; //Header will be null and then will be modified to 0
	trie* Tr=new trie('0',NULL);
//	Tr.push_back(new trie(0));
	ifstream fin;
	fin.open("trie.in");
	int N,S,P,i;
	fin>>N>>S>>P;
	char** create=new char*[N];
	for(i=0;i<N;i++)
		create[i]=new char[size];
	for(i=0;i<N;i++){
		char* a= new char[size];
		fin>>a;
		strncpy(create[i],a,strlen(a));
	}
	for(i=0;i<N;i++)
	    create_word(&Tr,create[i]);
	char** search=new char*[S];
	for(i=0;i<S;i++)
		search[i]=new char[size];
	for(i=0;i<S;i++){
		char* a= new char[size];
		fin>>a;
		strncpy(search[i],a,strlen(a));
	}
	for(i=0;i<S;i++){
		search_word(&Tr,search[i]);
	}
	char** prefix=new char*[P];
	for(i=0;i<P;i++)
		prefix[i]=new char[size];
	for(i=0;i<P;i++){
		char* a= new char[size];
		fin>>a;
		strncpy(prefix[i],a,strlen(a));
	}
	for(i=0;i<S;i++){
		search_prefix(Tr,prefix[i]);
	}
} 