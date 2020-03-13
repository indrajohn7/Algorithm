#include <iostream>
#include <vector>
#include <map>
#include <string>
#include<bits/stdc++.h>
#define N 10
using namespace std;

#define inf  -99999999

struct vertex{
    typedef pair<int,vertex*> ve;
    vector<ve> adj; //cost of edge, destination vertex
    string name;
	string colour;
	int distance;
	vertex* parent;
    vertex(string s,string c,int d,vertex* v)
    {
        name=s;
		colour=c;
		parent=v;
		distance=d;
    }
};

class graph
{
    public:
        typedef map<string, vertex *> vmap;
        vmap work;
        void addvertex(const string&,const string&,int , vertex*);
        void addedge(const string& from, const string& to, double cost);
		void display();
		vertex* Find_Node(const string&);
		void BFS(vertex*,int);
		void Print_Path(vertex*,vertex*);
		void DFS();
		void DFS_VISIT(vertex* );
};

void graph::addvertex(const string &name,const string &colour,int distance,vertex* par)
{
    vmap::iterator itr=work.begin();
    itr=work.find(name);
    if(itr==work.end())
    {
        vertex *v;
        v= new vertex(name,colour,distance,par);
        work[name]=v;
        return;
    }
        cout<<"\nVertex already exists!";
}

void graph::addedge(const string& from, const string& to, double cost)
{
    vertex *f=(work.find(from)->second);
    vertex *t=(work.find(to)->second);
    pair<int,vertex *> edge = make_pair(cost,t);
    f->adj.push_back(edge);
 }
 
 void graph::display()
 {
	 for(vmap::iterator itr=work.begin(); itr!=work.end();itr++){
		 cout<<itr->first <<"	:Adjacency list is \n";
		 cout<<"Edge COST		Destination NODE		Destination Node Colour		Distance\n";
		 
		 
		 for(int i=0;i<itr->second->adj.size();i++){
			 cout<<itr->second->adj[i].first<<"		"<<itr->second->adj[i].second->name<<"		"<<itr->second->adj[i].second->colour<<"		"<<itr->second->distance<<"\n";
			// itr->second++;
		 }
	 }
 }
 
 vertex* graph::Find_Node(const string& Node)
 {
	 vertex *f=(work.find(Node)->second);
	 return f;
 }
 
 
 
 void graph::DFS()
 {
	vmap::iterator itr=work.begin();
    while(itr!=work.end()){
		if(itr->second->colour=="WHITE")
			DFS_VISIT(itr->second);
		itr++;
	}
 }
 
 void graph::DFS_VISIT(vertex* v)
 {
	
	 v->colour="GREY";
	 v->distance=v->distance+1;
	 for(int i=0;i<v->adj.size();i++){
		 if(v->adj[i].second->colour=="WHITE"){
			 v->adj[i].second->parent=v;
			 DFS_VISIT(v->adj[i].second);
		 }
		 v->colour="BLACK";
	 }
 }
 
 void graph::Print_Path(vertex* Source,vertex* ver)
 {
	if(ver==Source)
		 cout<<Source->name<<"\n";
	 else if(ver->parent==NULL)
		 cout<<"No Path from "<<Source->name<<" to destination: "<<ver->name;
	 else{
		 Print_Path(Source,ver->parent);
		 cout<<ver->name<<"\t";
	 }
	 cout<<"\n";
		 
}
 
 int main()
 {
	 ifstream fin;
	 fin.open("infile.in");
	// char* Node[N]={"ONE","TWO","THREE","FOUR","FIVE","SIX","SEVEN","EIGHT","NINE","TEN"};
	 int i,j,Num;
	 fin>>Num;
	 char Node[Num][10];
	 for(i=0;i<Num;i++)
		 fin>>Node[i];
	 graph g;
	 int vertices[Num][Num];
	 for(i=0;i<Num;i++)
		 g.addvertex(Node[i],"WHITE",0,(vertex*)NULL);
	 for(i=0;i<Num;i++){
		 for(j=0;j<Num;j++)
			 fin>>vertices[i][j];
	 }
	 srand(time(NULL));
	 for(i=0;i<Num;i++){
		 for(j=0;j<Num;j++){
			 if(vertices[i][j]>0){
				 g.addedge(Node[i],Node[j],vertices[i][j]);
			 }
		 }
	 }
	 g.display();
	 char Source[10],Dest[10];
	 g.DFS();
	 g.display();
	 cout<<"Printing Source to Destiation Nodes:\n";
	 int choice;
	 cout<<"Printing Source to Destiation Nodes:\n";
	 while(1){
		 cout<<"Give the Source Node:\n";
		 cin>>Source;
		 cout<<"Give the Destination Node:\n";
		 cin>>Dest;
		 vertex* s=g.Find_Node(Source);
		 vertex* d=g.Find_Node(Dest);
		 g.Print_Path(s,d);
		 cout<<"Print 1 to continue & 2 to exit:\n";
		 cin>>choice;
		 if(choice==2)
			 break;
	 }
	 /*
	 for(g.vmap::iterator itr=g.work.begin();itr!=g.work.end();itr++){
		 cout<<itr->first <<"	:Adjacency list is \n"<<;
		 cout<<"COST		Destination NODE\n";
		 while(itr->second->adj!=NULL){
			 cout<<itr->second->adj->first<<"		";//<<itr->second->adj->second->first
			 adj++;
		 }
	 }
	 */
	 
	 return 0;
 }
