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
                bool Print_Path(vertex*,vertex*);
				void Maximum_Flow(vertex*,vertex*,int [][10]);
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

 void graph::BFS(vertex* Source,int ver_num)
 {
         Source->colour="GREY";
         Source->distance=0;
         Source->parent=NULL;
         list<vertex*> ver;
         ver.push_back(Source);       //ENQUEUE
         while(ver.size()>0){
                 vertex* u=ver.front();
                 ver.pop_front();     //DEQUEUE
                 for(int i=0;i<u->adj.size();i++){
                         if(u->adj[i].second->colour=="WHITE"){
                                 u->adj[i].second->colour="GREY";
                                 u->adj[i].second->distance=u->distance+1;
                                 u->adj[i].second->parent=u;
                                 ver.push_back(u->adj[i].second);       //ENQUEUE
                         }
                         u->colour="BLACK";
                 }

         }
 }

 bool graph::Print_Path(vertex* Source,vertex* sink)
 {
        if(sink==Source)
		{
			   //  cout<<Source->name<<"\n";
				 return true;
		}
         else if(sink->parent==NULL)
		 {
               //  cout<<"No Path from "<<Source->name<<" to destination: "<<sink->name;
				 return false;
		 }
		 else{
			    for(int i=0;i<sink->adj.size();i++){
					if(sink->adj[i].first <0)
				         Print_Path(Source,sink->parent);
                  //   cout<<sink->name;	
				}
                
         }
		 return false;

}

int* find_min(int cost[][10],int num)
{
	int i,j,arr[3],min=100,temp_i,temp_j;;
	for(i=0;i<num;i++){
		for(j=0;j<num;j++){
			if(cost[i][j]>0 && min>cost[i][j]){
					min=cost[i][j];
					temp_i=i;
					temp_j=j;
			}			
		}
	}
	arr[0]=temp_i;
	arr[1]=temp_j;
	arr[2]=min;
	return arr;
}

void Maximum_Flow(vertex* S,vertex* T,int cost[][10],int num,char Node[][10])
{
	int* node= find_min(cost,num);
	int i,j;
	bool ret_source,ret_destination;
	vertex* Source=Find_Node(Node[node[0]]);
	ret_source=Print_Path(S,Source);
	vertex* sink=Find_Node(Node[node[1]]);
	ret_destination=Print_Path(sink,T);
	if(ret_source && ret_destination){
		while(T!=S){

			   for(i=0;i<num;i++){
				  if(strcmp(Node[i],T->parent->name.c_str())==0)
				   break;
			   }
               for(j=0;j<num;j++){
				   if(strcmp(Node[j],T->name.c_str())==0)
					   break;
			   }
               cost[i][j]=cost[i][j]-node[2];
               T=T->parent;
                                   			   
                  //   cout<<sink->name;	
                
		}
        if(T==S)
		   {
			   cost[node[0]][node[1]]=cost[node[0]][node[1]]-node[2];
			   cost[node[1]][node[0]]=cost[node[1]][node[0]]+node[2];
		   }
    }
	
	//RECURSION logic has to be put here for complete traversal and to get maximum flow of a network.
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
         g.BFS(source,Num);
         g.display();
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
		 cout<<"Give the Source Node:\n";
         cin>>Source;
         cout<<"Give the Destination Node:\n";
         cin>>Dest;
         vertex* s=g.Find_Node(Source);
         vertex* d=g.Find_Node(Dest);
		 Maximum_Flow(s,d,vertices,Num,Node);

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
