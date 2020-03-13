#include<stdio.h>
#include<string.h>
#include<bits/stdc++.h>

#define N 1000
using namespace std;

#define inf  -99999999
#define infi  99999999

struct vertex{
    typedef pair<int,vertex*> ve;
    vector<ve> adj; //cost of edge, destination vertex
    int name;
    string colour;
    int distance;
    vertex* parent;
	int weight;
	bool block;
    vertex(int s,string c,int d,vertex* v,int w,bool b)
    {
        name=s;
        colour=c;
        parent=v;
        distance=d;
		weight=w;
		block=b;
    }
};

class graph
{
    public:
        typedef map<int, vertex *> vmap;
        vmap work;
        void addvertex(int ,const string&,int , vertex*,int,bool);
        void addedge(int from, int to, double cost);
                void display();
                vertex* Find_Node(int);
                int BFS(vertex*,vertex*,vector<int>);
                bool Print_Path(vertex*,vertex*);
				int minRoads(char**);
				int combo(int ,int );
				int fact(int );
				void getnum(char*,int*,int*);
			//	void dijkstra(vertex*);
			//	void obstruct(vertex*,int);
};


int graph::fact(int n)
{
	if(n==0 || n==1)
		return 1;
	else
		return n*fact(n-1);
}

int graph::combo(int n,int r)
{
	return (fact(n)/(fact(n-r)*fact(r)));
}


void graph::addvertex(int name,const string &colour,int distance,vertex* par,int weight,bool block)
{
    vmap::iterator itr=work.begin();
    itr=work.find(name);
    if(itr==work.end())
    {
        vertex *v;
        v= new vertex(name,colour,distance,par,weight,block);
        work[name]=v;
        return;
    }
        cout<<"\nVertex already exists!";
}

void graph::addedge(int from, int to, double cost)
{
    vertex *f=(work.find(from)->second);
    vertex *t=(work.find(to)->second);
    pair<int,vertex *> edge = make_pair(cost,t);
    f->adj.push_back(edge);
 }
 
 

bool graph::Print_Path(vertex* Source,vertex* ver)
 {
        if(ver==Source){
                 cout<<Source->name<<"\n";
				 return true;
		}
         else if(ver->parent==NULL || ver->block==true){
                 cout<<"No Path from "<<Source->name<<" to destination: "<<ver->name<<endl;
				 return false;
		 }
         else{
                 Print_Path(Source,ver->parent);
                 cout<<ver->name;
         }

}


vertex* graph::Find_Node(int Node)
 {
         vertex *f=(work.find(Node)->second);
         return f;
 }

 int graph::BFS(vertex* Source,vertex* Destination,vector<int> a)
 {
         Source->colour="GREY";
         Source->distance=0;
         Source->parent=NULL;
         list<vertex*> ver;
		 list<vertex*> ver1;
         ver.push_back(Source);       //ENQUEUE
		 int min=infi;
		 ver1.push_back(Source);
         while(ver.size()>0){
                 vertex* u=ver.front();
                 ver.pop_front();     //DEQUEUE
				 ver1=ver;
                 for(int i=0;i<u->adj.size();i++){
                         if(u->adj[i].second->colour=="WHITE"){
                                 u->adj[i].second->colour="GREY";
                                 u->adj[i].second->distance=u->distance+1;
                                 u->adj[i].second->parent=u;
                                 ver.push_back(u->adj[i].second);       //ENQUEUE
                         }
                         u->colour="BLACK";
					}
						 int count=0,p=0;
						 ver1=ver;
						 vector<int> v(ver.size());
						 while(ver1.size()!=0){
							 v[p++]=ver1.front()->name;
							 ver1.pop_front();
						 }
						 while(count!=ver.size()){
							// min=infi;
							int arr[N][N]={0},dummy=0;;    //can be a dynamic initialisation
							for(int i=0;i<combo(ver.size(),count+1);i++){
								for(int j=0;j<count+1;j++){
									int flag=0;
									int t=rand()%ver.size();
									 for(int l=0;l<j;l++){										 
										 if(arr[i][l]==v[t]){
											 flag=1;
											 break;
										 }
									 }
									 if(flag==1)
										j--;
									else
										arr[i][j]=v[t];
								}
								for(int k=0;k<i;k++){
									dummy=0;
									for(int l=0;l<count+1;l++){
										if(arr[i][l]==arr[k][l])
											dummy++;
									}
									if(dummy==count+1){
										i--;
										break;
									}
								}							
								dummy=0;
							}
							for(int i=0;i<combo(ver.size(),count+1);i++){
								for(int j=0;j<count+1;j++){
									vertex *node=Find_Node(arr[i][j]);
									node->block=true;
								}
							//	vertex* S=Find_Node(a[0]);
							//    vertex* D=Find_Node(a[a.size()-1]);
							    if(!Print_Path(Source,Destination)){
									if(min>count)
										min=count;
								}
								if(min==1)
									return min;
								for(int j=0;j<count+1;j++){
									vertex *node=Find_Node(arr[i][j]);
									node->block=false;
								}
							}
							/*
							for(int i=0;i<combo(ver.size(),count+1);i++){
								for(int j=0;j<count+1;j++){
									vertex *N=Find_Node(arr[j]);
									N->block=false;
								}
							}
							*/
							count++;
						// }
					}
			}
			return min;
 }

 
 void graph::getnum(char* a,int* x,int*y)
 {
	 int sum1=0,sum[2],k=0;
	 for(int i=0;i<strlen(a);i++){
		 sum1=0;
		 while(i<strlen(a) && isdigit(a[i])){
			 sum1=sum1*10+(a[i++]-'0');
		 }
		 sum[k++]=sum1;
	 }
	 *x=sum[0];
	 *y=sum[1];
 }


int graph::minRoads(char* input1[])
{
	//Write code here
	int node1=0,node2=0,arr[N][2],min;
	vector<int> a;
	for(int i=0;input1[i]!=NULL;i++){
	//	for(j=0;j<strlen(input1[i]);j++){
			//sprintf(input1[i],"%d#%d",node1,node2);
			//graph g;
			getnum(input1[i],&node1,&node2);
			addvertex(node1,"WHITE",inf,(vertex*)NULL,infi,false);
			addvertex(node2,"WHITE",inf,(vertex*)NULL,infi,false);
			a.push_back(node1);
			a.push_back(node2);
			addedge(node1,node2,0);
			addedge(node2,node1,0);
	//	}
	}
	/*
	for(int i=0;i<sizeof(input1)/sizeof(char*);i++){
		addedge(arr[i][0],arr[i][1],0);
	}
	*/
	sort(a.begin(),a.end());
	vertex* f=Find_Node(a[0]);
	vertex* l=Find_Node(a[a.size()-1]);
	if(f->adj.size()>l->adj.size())
		min=BFS(l,f,a);
	else
		min=BFS(f,l,a);
	return min;	
}




int main()
{
	char* in[]={"1#2","1#5","2#5","2#3","3#4","4#5","4#6","3#6"};
	int min;
	graph g;
	min=g.minRoads(in);
	cout<<endl<<min<<endl;
	return 0;
}