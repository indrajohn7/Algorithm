#include <iostream>
#include <vector>
#include <map>
#include <string>
#include<bits/stdc++.h>
#define N 10
using namespace std;

struct vertex{
    typedef pair<int,vertex*> ve;
    vector<ve> adj; //cost of edge, destination vertex
    string name;
    vertex(string s)
    {
        name=s;
    }
};

class graph
{
    public:
        typedef map<string, vertex *> vmap;
        vmap work;
        void addvertex(const string&);
        void addedge(const string& from, const string& to, double cost);
		void display();
};

void graph::addvertex(const string &name)
{
    vmap::iterator itr=work.begin();
    itr=work.find(name);
    if(itr==work.end())
    {
        vertex *v;
        v= new vertex(name);
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
		 cout<<"COST		Destination NODE\n";
		 
		 
		 for(int i=0;i<itr->second->adj.size();i++){
			 cout<<itr->second->adj[i].first<<"		"<<itr->second->adj[i].second->name<<"\n";//<<itr->second->adj->second->first
			// itr->second++;
		 }
	 }
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
		 g.addvertex(Node[i]);
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
