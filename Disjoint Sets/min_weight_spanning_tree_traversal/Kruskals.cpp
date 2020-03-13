#include <iostream>
#include <vector>
#include <map>
#include <string>
#include<bits/stdc++.h>
#define N 10
#define T 20
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

typedef struct EDGE{
	 int cost;
	 string from;
	 string to;
 }edge;
 
 extern int global_cost=0;
 string global_traverse[T];
 
 vector<edge> v_edge;

class graph
{
    public:
        typedef map<string, vertex *> vmap;
        vmap work;
        void addvertex(const string&);
        void addedge(const string& from, const string& to, double cost);
		void display();
		void kruskals();
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
 
 
 
 void kruskals()
 {
	int i,j;
	for(i=0;i<v_edge.size();i++){
		for(j=0;j<v_edge.size();j++){
			edge e;
			if(v_edge[j].cost > v_edge[j+1].cost){
					e=v_edge[k+1];
					v_edge[k+1]=v_edge[k];
					v_edge[k]=e;
			}
		}
	}
	vector<string> ls;
	vector<ls> arr;
	int l=2;
	for(i=0;i<v_edge.size();i++){
		int from_found_ind=-1, to_found_ind=-1;
		if(arr.size()==0){
			arr[0].push_back(v_edge[i].from);
			arr[0].push_back(v_edge[i].to);
			global_cost+=v_edge[i].cost;
			global_traverse[0]=v_edge[i].from;
			global_traverse[1]=v_edge[i].to;
		}
		else if(arr.size()>0){
			for(j=0;j<arr.size();j++){
				for(int k=0;k<arr[j].size();k++){
					if(arr[j][k]==v_edge[i].from)
						from_found_ind=j;
					if(arr[j][k]==v_edge[i].to)
						to_found_ind=j;
				}
			}
			if(to_found_ind==-1 && from_found_ind==-1){
				vector<string> l;
				l.push_back(v_edge[i].from);
				l.push_back(v_edge[i].to);
				arr.push_back(l);
				global_cost+=v_edge[i].cost;
				global_traverse[l++]=v_edge[i].from;
				global_traverse[l++]=v_edge[i].to;
			}
			else if(to_found_ind==-1 || from_found_ind==-1){
				if(to_found_ind==-1){
					arr[from_found_ind].push_back(v_edge[i].to);
					global_cost+=v_edge[i].cost;
					global_traverse[l++]=v_edge[i].to;
				}
			}
			else if(to_found_ind>=0 && from_found_ind>=0){
				for(int m=0;m<arr[to_found_ind].size();m++){
					arr[from_found_ind].pushback(arr[to_found_ind][m]);
				}
				arr[to_found_ind].erase)();
				global_cost+=v_edge[i].cost;
				global_traverse[l++]=v_edge[i].from;
				global_traverse[l++]=v_edge[i].to;
			}
				
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
	 for(i=0;i<Num;i++)
	 {
		 for(j=0;j<Num;j++){
			  int flag1=0;
			 if(v_edge.size()>=0 && vertices[i][j]>0){
				 for(int k=0;k<v_edge.size();k++){
					 if((v_edge[k].cost==vertices[i][j] && v_edge[k].from==Node[j] && v_edge[k].to==Node[i])){
						flag1=1;
						break; 
					 }					 
				 }
				 if(flag1==0){
					 v_edge[k].cost=vertices[i][j];
					 v_edge[k].from=Node[i];
					 v_edge[k].to=Node[j];
				 }
			 }
		 }
	 }
	 g.display();
	 g.kruskals();
	 cout<<"After Kruskal traversal:\n";
	 for(i=0;i<T,global_traverse[i]!='\0';i++)
		 cout<<global_traverse[i]<<"\t";
	 cout<<"\n Total cost of traversal:	"<<global_cost<<"\n";
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
