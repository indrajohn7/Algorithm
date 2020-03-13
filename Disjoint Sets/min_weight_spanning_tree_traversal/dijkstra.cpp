#include <iostream>
#include <vector>
#include <map>
#include <string>
#include<bits/stdc++.h>
#define N 10
using namespace std;

#define inf  -99999999
#define infi  99999999


struct vertex{
    typedef pair<int,vertex*> ve;
    vector<ve> adj; //cost of edge, destination vertex
    string name;
    string colour;
    int distance;
    vertex* parent;
	int weight;
    vertex(string s,string c,int d,vertex* v,int w)
    {
        name=s;
        colour=c;
        parent=v;
        distance=d;
		weight=w;
    }
};

// extern int global_cost=0;

class graph
{
    public:
        typedef map<string, vertex *> vmap;
        vmap work;
        void addvertex(const string&,const string&,int , vertex*,int);
        void addedge(const string& from, const string& to, double cost);
                void display();
                vertex* Find_Node(const string&);
          //      void BFS(vertex*,int);
                void Print_Path(vertex*,vertex*);
				void dijkstra();
};

void graph::addvertex(const string &name,const string &colour,int distance,vertex* par,int weight)
{
    vmap::iterator itr=work.begin();
    itr=work.find(name);
    if(itr==work.end())
    {
        vertex *v;
        v= new vertex(name,colour,distance,par,weight);
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
	    //NODE DETAILS
		 for(vmap::iterator itr=work.begin(); itr!=work.end();itr++){
                 cout<<itr->first <<"        :Node Details: \n";
                 cout<<"Node Name               Node Weight                 Node Colour        Node's Parent Name\n";
				 if(itr->second->parent==NULL)
					cout<<itr->second->name<<"      "<<itr->second->weight<<"      "<<itr->second->colour<<"      "<<"NULL \n";
				 else
					 cout<<itr->second->name<<"      "<<itr->second->weight<<"      "<<itr->second->colour<<"      "<<itr->second->parent->name<<"\n";
		 }
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

void graph::dijkstra()
{
	 vmap::iterator it=work.begin();
	 vertex* Source=it->second;
	 Source->colour="GREY";
     Source->distance=0;
	 Source->weight=0;
     Source->parent=NULL;
     list<vertex*> ver;
     ver.push_back(Source);       //ENQUEUE
     while(ver.size()>0){
		vertex* u=ver.front();
        ver.pop_front();     //DEQUEUE
        for(int i=0;i<u->adj.size();i++){
                if(u->adj[i].second->colour=="WHITE" || ((u->weight+u->adj[i].first) < u->adj[i].second->weight)){
                    u->adj[i].second->colour="GREY";
                    u->adj[i].second->distance=u->distance+1;
                    u->adj[i].second->parent=u;
					u->adj[i].second->weight = u->weight+u->adj[i].first;
                    ver.push_back(u->adj[i].second);       //ENQUEUE
                    }
                u->colour="BLACK";
        }

    }
	/*
	 for(vmap::iterator itr=work.begin(); itr!=work.end();itr++){
		 for(int i=0;i<itr->second->adj.size();i++){
			 if(itr->second->weight==infi)
				 itr->second->weight=0;
			 if((itr->second->adj[i].first + itr->second->weight) < itr->second->adj[i].second->weight){
				 itr->second->adj[i].second->weight = itr->second->adj[i].first + itr->second->weight;
				 itr->second->adj[i].second->parent=itr->second;
			 }
		 }
	 }
	 */
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
                 g.addvertex(Node[i],"WHITE",inf,(vertex*)NULL,infi);
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
       //  g.display();
		 char Source[10],Dest[10];
         vertex* source=g.Find_Node("ONE");
		 g.dijkstra();
		 g.display();
		// cout<<"After Prims Traversal total cost of path is:"<<global_cost<<"\n";
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
