#include <iostream>
#include <vector>
#include <map>
#include <string>
#include<bits/stdc++.h>

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
	vertex* child;
	int weight;
    vertex(int s,string c,int d,vertex* v,vertex* u,int w)
    {
        name=s;
        colour=c;
        parent=v;
        distance=d;
		weight=w;
		child=u;
    }
};

// extern int global_cost=0;

class graph
{
    public:
        typedef map<int, vertex *> vmap;
        vmap work;
        void addvertex(const int,const string&,int , vertex*,vertex*,int);
        void addedge(const int from, const int to, double cost);
                void display();
                vertex* Find_Node(const int&);
          //      void BFS(vertex*,int);
                void Print_Path(vertex*,vertex*);
				void dijkstra_all(vertex*,int**,int,int[]);
				void init_all();
};

void graph::init_all()
{
	for(vmap::iterator it=work.begin();it!=work.end();it++){
		it->second->colour="WHITE";
		it->second->weight=0;
	}
}

void graph::addvertex(const int name,const string &colour,int distance,vertex* par,vertex* child,int weight)
{
    vmap::iterator itr=work.begin();
    itr=work.find(name);
    if(itr==work.end())
    {
        vertex *v;
        v= new vertex(name,colour,distance,par,child,weight);
        work[name]=v;
        return;
    }
        cout<<"\nVertex already exists!";
}

void graph::addedge(const int from, const int to, double cost)
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
    /*     for(vmap::iterator itr=work.begin(); itr!=work.end();itr++){
                 cout<<itr->first <<"   :Adjacency list is \n";
                 cout<<"Edge COST               Destination NODE                Destination Node Colour\n";


                 for(int i=0;i<itr->second->adj.size();i++){
                         cout<<itr->second->adj[i].first<<"             "<<itr->second->adj[i].second->name<<"          "<<itr->second->adj[i].second->colour<<"\n";
                        // itr->second++;
                 }
         }
		 */
 }

 vertex* graph::Find_Node(const int& Node)
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

void graph::dijkstra_all(vertex* Source, int** shortest,int num,int Node[])
{
	 Source->colour="GREY";
     Source->distance=0;
	 Source->weight=0;
    // Source->parent=NULL;
     list<vertex*> ver;
     ver.push_back(Source);  //ENQUEUE
	 int k,l;	 
	 for(k=0;k<num;k++){
		 if(Node[k]==Source->name)
			 break;
	 }
	 shortest[k][k]=0;
     while(ver.size()>0){
		vertex* u=ver.front();
        ver.pop_front();     //DEQUEUE
        for(int i=0;i<u->adj.size();i++){
                if(u->adj[i].second->colour=="WHITE" || ((u->weight+u->adj[i].first) < u->adj[i].second->weight)){
                    u->adj[i].second->colour="GREY";
                    u->adj[i].second->distance=u->distance+1;
                    u->adj[i].second->parent=u;
					u->child=u->adj[i].second;
					u->adj[i].second->weight = u->weight+u->adj[i].first;
					for(l=0;l<num;l++){
							if(Node[l]==u->adj[i].second->name)
								break;
					}
					shortest[k][l]=u->adj[i].second->weight;
                    ver.push_back(u->adj[i].second);       //ENQUEUE
                    }
                u->colour="BLACK";
        }

    }
}


 

 
 int main()
{
	int iter,Num_Test;
	ifstream fin;
	fin.open("manic_moving.txt");
	fin>>Num_Test;
	for(iter=0;iter<Num_Test;iter++){
		int N,M,K;
		fin>>N>>M>>K;
		int** arr=new int*[M];
		for(int i=0;i<M;i++){
			arr[i]=new int[3];
		}
		for(int i=0;i<M;i++){
			for(int j=0;j<3;j++)
				fin>>arr[i][j];
		}
		int** route=new int*[K];
		for(int i=0;i<K;i++)
			route[i]=new int[2];
		for(int i=0;i<K;i++){
			for(int j=0;j<2;j++)
				fin>>route[i][j];
		}
		
		
		 int Node[N];
		 for(int i=0;i<N;i++)
			 Node[i]=i+1;
         graph g;
         int vertices[N][N];
		 int** shortest=new int*[N];
		 for(int i=0;i<N;i++)
			 shortest[i]=new int[N];
         for(int i=0;i<N;i++)
             g.addvertex(Node[i],"WHITE",inf,(vertex*)NULL,(vertex*)NULL,infi);
         for(int i=0;i<M;i++){
             g.addedge(arr[i][0],arr[i][1],arr[i][2]);
			 g.addedge(arr[i][1],arr[i][0],arr[i][2]);
		 }
                        
		 for(int i=0;i<N;i++){
			g.init_all();
			vertex* source=g.Find_Node(Node[i]);
			g.dijkstra_all(source,shortest,N,Node);
		//	g.display();
		 }
		 
		int load=0,cost=0;
		list<int> vec;
		cost+=shortest[0][route[0][0]-1];
		int last=0,flag=0;
		for(int i=0;i<K;i++){
			if(vec.size()==0){
				vec.push_back(i);
				if(last!=0 && last!=route[i][0])
					cost+=shortest[last-1][route[i][0]-1];
				last=route[i][0];
				
			}
			while(vec.size()){
				int first=vec.front();
				int source,dest;
				source=last;
				if(last!=route[vec.front()][0])
					cost+=shortest[last-1][route[vec.front()][0]-1];
				dest=route[vec.front()][1];
				vertex* s=g.Find_Node(source);
				vertex* e=g.Find_Node(dest);
				bool end=false;
				while(e!=s ){
					vertex* pc=NULL;
					if(s->parent==NULL /*&& e->child==NULL*/){
						flag=1;
						break; //will return -1
					}/*if(e->parent==NULL){
						pc=e;
						e=e->child;						
					}*/
					if(i<K-1 && s->name==route[i+1][0] && vec.size()<=1){
						++i;
						vec.push_back(i);
					}else if(i<K-1 && s->name==route[i+1][1] && vec.size()<=1)
							end=true;
					/*if(pc!=NULL)
						e=e->child;
					else*/
						s=s->parent;
						/*
					if(i<K-1 && s->name==route[i+1][0] && end && vec.size()<=1){
						++i;
						end=false;
					}*/
				}
				last=route[vec.front()][1];
				cost+=shortest[last-1][route[vec.front()][0]-1];
				vec.pop_front();
				if(flag)
					break;
			}
			if(flag)
				break;
		}
		if(flag)
			cost=-1;
		cout<<"Case #"<<iter+1<<": "<<cost<<endl;
	}
	return 0;
}