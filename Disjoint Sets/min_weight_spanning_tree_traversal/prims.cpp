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

extern int global_cost=0;

class graph
{
    public:
        typedef map<string, vertex *> vmap;
        vmap work;
        void addvertex(const string&,const string&,int , vertex*);
        void addedge(const string& from, const string& to, double cost);
                void display();
                vertex* Find_Node(const string&);
          //      void BFS(vertex*,int);
                void Print_Path(vertex*,vertex*);
				void prims(vertex*,int);
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
                 cout<<itr->first <<"   :Adjacency list is \n";
                 cout<<"Edge COST               Destination NODE                Destination Node Colour\n";


                 for(int i=0;i<itr->second->adj.size();i++){
                         cout<<itr->second->adj[i].first<<"             "<<itr->second->adj[i].second->name<<"          "<<itr->second->adj[i].second->colour<<"\n";
                        // itr->second++;
                 }
         }
 }

 vertex* graph::Find_Node(const string& Node)
 {
         vertex *f=(work.find(Node)->second);
         return f;
 }

 
 void graph::Print_Path(vertex* Source,vertex* ver)
 {
        if(ver==Source)
                 cout<<Source->name<<"\n";
         else if(ver->parent==NULL)
                 cout<<"No Path from "<<Source->name<<" to destination: "<<ver->name;
         else{
                 Print_Path(Source,ver->parent);
                 cout<<ver->name;
         }

}

void graph::prims(vertex* Source, int Node_num)
{
	Source->colour="GREY";
    Source->distance=0;
    Source->parent=NULL;
    vector<vertex*> ver;
	int index = 0, max=999,flag=0,node_index=0;
    ver.push_back(Source);
	cout<<Source->name<<"\n";
	while(ver.size() < Node_num){
               //  vertex* u=ver.front();
               //  ver.pop_front();     //DEQUEUE
				 max=999;
				  flag=0;
				 for(int k=0;k<ver.size();k++){
					 vertex* u=ver[k];
					 // max=999;					 
                 	for(int i=0;i<u->adj.size();i++){
						if(u->adj[i].first<max && u->adj[i].second->colour=="WHITE"){
							max=u->adj[i].first;
							index=i;
							node_index=k;
							flag=1;
						}
				 	}
				}
				vertex* u=ver[node_index];
				if(u->adj[index].second->colour=="WHITE"){
                         u->adj[index].second->colour="GREY";
                         u->adj[index].second->distance=u->distance+1;
                         u->adj[index].second->parent=u;
						 global_cost+=u->adj[index].first;
                         ver.push_back(u->adj[index].second);
						 cout<<u->adj[index].second->name<<endl;
                   }
                         u->colour="BLACK"; 
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
                 g.addvertex(Node[i],"WHITE",inf,(vertex*)NULL);
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
         vertex* source=g.Find_Node("ONE");
		 g.prims(source,Num);
		 g.display();
		 cout<<"After Prims Traversal total cost of path is:"<<global_cost<<"\n";
         /*
         for(g.vmap::iterator itr=g.work.begin();itr!=g.work.end();itr++){
                 cout<<itr->first <<"   :Adjacency list is \n"<<;
                 cout<<"COST            Destination NODE\n";
                 while(itr->second->adj!=NULL){
                         cout<<itr->second->adj->first<<"               ";//<<itr->second->adj->second->first
                         adj++;
                 }
         }
         */

         return 0;
 }
