#include <iostream>
#include <vector>
#include <map>
#include <string>
#include<bits/stdc++.h>
#define N 10
using namespace std;

#define inf  -99999999
#define ODD_NODE_EULER 2

struct edge{
	int cost;
	string color;
	edge(int c, string s) {
		cost = c;
		color = s;
	}
};

struct vertex{
    typedef pair<struct edge, vertex*> ve;
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
		int total_edges;
		vector<string> odd_adj_nodes;
		vector<string> zero_adj_nodes;
		vector<string> even_adj_nodes;
		typedef vector<string> vec_str;
		vector<vec_str> euler_path;
		vector<vec_str> euler_circuit;
        void addvertex(const string&,const string&,int , vertex*);
        void addedge(const string& from, const string& to, struct edge);
		void display();
		vertex* Find_Node(const string&);
		void BFS(vertex*,int);
		void Print_Path(vertex*,vertex*);
		void DFS();
		void DFS_VISIT(vertex* );
		bool is_eulerian_path_exist();
		bool is_eulerian_circuit_exist();
		void get_all_euler_path();
		void DFS_count(vertex*, int*);
		int print_euler_tour(vertex* source, vector<string>*, int);
		void revive_all_node_color();
		void revive_all_edges();
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

void graph::addedge(const string& from, const string& to, struct edge ed)
{
    vertex *f=(work.find(from)->second);
    vertex *t=(work.find(to)->second);
    pair<struct edge, vertex *> adj_edge = make_pair(ed, t);
    f->adj.push_back(adj_edge);
 }
 
 void graph::display()
 {
	 for(vmap::iterator itr=work.begin(); itr!=work.end();itr++){
		 cout<<itr->first <<"	:Adjacency list is \n";
		 cout<<"Edge COST		Destination NODE		Destination Node Colour		Distance\n";
		 
		 
		 for(int i=0;i<itr->second->adj.size();i++){
			 cout<<itr->second->adj[i].first.cost <<"		"<<itr->second->adj[i].second->name<<"		"<<itr->second->adj[i].second->colour<<"		"<<itr->second->distance<<"\n";
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


bool graph :: is_eulerian_path_exist()
{
	
	for (vmap :: iterator it = work.begin(); it != work.end(); it++) {
		if (it->second->adj.size() == 0)
			zero_adj_nodes.push_back(it->first);
		else if (it->second->adj.size() % 2)
			odd_adj_nodes.push_back(it->first);
		else
			even_adj_nodes.push_back(it->first);
	}

	if (odd_adj_nodes.size() != ODD_NODE_EULER && odd_adj_nodes.size() != 0)
		return false;
	
	return true;
}


bool graph :: is_eulerian_circuit_exist()
{
	if (odd_adj_nodes.size() == 0)
		return true;
	
	return false;
}

/**************************************************	Fleury's Algorithm to find out the euler tour   **************************************************************/
/*	Following is C++ implementation of above algorithm. In the following code, it is assumed that the given graph has an Eulerian trail or Circuit. 
	The main focus is to print an Eulerian trail or circuit. We can use isEulerian() to first check whether there is an Eulerian Trail or Circuit in the given graph.

	1>	We first find the starting point which must be an odd vertex (if there are odd vertices) and store it in variable ‘u’. 
	2>	If there are zero odd vertices, we start from vertex ‘0’. We call printEulerUtil() to print Euler tour starting with u. 
	3>	We traverse all adjacent vertices of u, if there is only one adjacent vertex, we immediately consider it. If there are more than one adjacent vertices, 
	4>	we consider an adjacent v only if edge u-v is not a bridge. How to find if a given is edge is bridge? 
		4.1>	We count number of vertices reachable from u. We remove edge u-v and again count number of reachable vertices from u. 
		4.2>	If number of reachable vertices are reduced, then edge u-v is a bridge. To count reachable vertices, we can either use BFS or DFS, we have used DFS in the above code. 
		4.3>	The function DFSCount(u) returns number of vertices reachable from u.
	5>	Once an edge is processed (included in Euler tour), we remove it from the graph. To remove the edge, we replace the vertex entry with -1 in adjacency list. 
	6>	Note that simply deleting the node may not work as the code is recursive and a parent call may be in middle of adjacency list.
*/

void graph :: revive_all_node_color()
{
	for (vmap :: iterator it = work.begin(); it != work.end(); it++) {
		it->second->colour = "WHITE";
	}
}

void graph :: revive_all_edges()
{
	for (vmap :: iterator it = work.begin(); it != work.end(); it++) {
		for (int i = 0; i < it->second->adj.size(); i++) {
			it->second->adj[i].first.color = "WHITE";
			it->second->adj[i].first.cost = 1;
		}
	}
}

void graph :: DFS_count(vertex* v, int* edge_count)
{
	
	 v->colour = "GREY";
	 for(int i = 0; i < v->adj.size(); i++){
		 if(v->adj[i].second->colour == "WHITE" && v->adj[i].first.cost != 0){
			// v->adj[i].second->parent=v;
			 (*edge_count)++;
			 DFS_count(v->adj[i].second, edge_count);
		 }
		 v->colour = "BLACK";
	 }
}

int graph :: print_euler_tour(vertex* source, vector<string> *eu_path, int edges)
{

	string direction = "-->";

	if (source->adj.size() == 1 && source->adj[0].first.cost != -1) {
		if (edges == total_edges)
			return 0;
		eu_path->push_back(source->name);
		source->adj[0].first.cost = -1;
		vertex* dest = source->adj[0].second;
		eu_path->push_back(direction);
		eu_path->push_back(dest->name);
		for (int i = 0; i < dest->adj.size(); i++) {
			if (dest->adj[i].second->name == source->name) {
				dest->adj[i].first.cost = -1;
				dest->adj[i].first.color = "GREY";
			}
		}
		source->adj[0].first.color = "GREY";
		source = source->adj[0].second;
		edges++;
		print_euler_tour(source, eu_path, edges);
	} else {
		int count = 0;
		for (int i = 0; i < source->adj.size(); i++) {
			if (source->adj[i].first.cost == -1)
				count++;
		}
		if (edges == total_edges)
			return 0;
		if (count == source->adj.size())
			return 1;
		
		int init_dfs_count, late_dfs_count;
		init_dfs_count = late_dfs_count = 0;
		revive_all_node_color();
		DFS_count(source, &init_dfs_count);
		int actual_edge_cost;
		for (int i = 0; i < source->adj.size(); i++) {
			if (source->adj[i].first.cost != -1) {
				actual_edge_cost = source->adj[i].first.cost;
				source->adj[i].first.cost = 0;
				revive_all_node_color();
				late_dfs_count = 0;
				DFS_count(source, &late_dfs_count);
				if (late_dfs_count < init_dfs_count) {
					source->adj[i].first.cost = actual_edge_cost;
				} else {
					source->adj[i].first.cost = -1;
					source->adj[i].first.color = "GREY";
					vertex* dest = source->adj[i].second;
					for (int idx = 0; idx < dest->adj.size(); idx++) {
						if (dest->adj[idx].second->name == source->name) {
							dest->adj[idx].first.cost = -1;
							dest->adj[idx].first.color = "GREY";
						}
					}
					eu_path->push_back(source->name);
					eu_path->push_back(direction);
					eu_path->push_back(dest->name);
					source = source->adj[i].second;
					edges++;
					print_euler_tour(source, eu_path, edges);
				}
			}
			
		}
	}

	return 0;
}

void graph :: get_all_euler_path()
{
	
	if (odd_adj_nodes.size()) {
		vector<string> eu_path;
		vertex* source = Find_Node(odd_adj_nodes[0]);
		if (print_euler_tour(source, &eu_path, 0) == 0) {
			euler_path.push_back(eu_path);
		}
		reverse(eu_path.begin(), eu_path.end());
		euler_path.push_back(eu_path);

		//print_euler_tour(odd_adj_nodes[1]);
	} else {
		for (vmap :: iterator it = work.begin(); it != work.end(); it++) {
			vector<string> eu_path;
			revive_all_edges();
			vertex* source = work.find(it->first)->second;
			if (print_euler_tour(source, &eu_path, 0) == 0) {
				euler_path.push_back(eu_path);
			}
		}
	}
}

 int main()
 {
	 ifstream fin;
	 fin.open("infile.in");
	// char* Node[N]={"ONE","TWO","THREE","FOUR","FIVE","SIX","SEVEN","EIGHT","NINE","TEN"};
	 int i, j, Num, edges;
	 edges = 0;
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
			 	struct edge* ed = new edge(vertices[i][j], "WHITE");
				 g.addedge(Node[i],Node[j], *ed);
				 edges++;
			 }
		 }
	 }
	 g.total_edges = edges / 2;
	 g.display();
	 char Source[10],Dest[10];
	 g.DFS();
	 g.display();
/*	 
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
		if(choice != 1)
			 break;
	 }
*/

	 
	 cout << "Checking Whether Eulerian Path Exists or not!" << endl;
	 if (g.is_eulerian_path_exist()) {
	 	cout << "Euler Path Exists!" << endl;
	 	cout << "Retrieve all the Euler paths exist in the Network: \n";
	 	g.get_all_euler_path();
		for (int i = 0; i < g.euler_path.size(); i++) {
			for (int j = 0; j < g.euler_path[i].size(); j++) {
				cout << g.euler_path[i][j] << " ";
			}
			cout << endl;
		}
	 } else {
	 	cout << "Alas! There is no eulerian path :( .." << endl;
	 }
	 
	 cout << "Checking Whether Eulerian Cycle Exists or not!" << endl;
	 if (g.is_eulerian_circuit_exist()) {
	 	cout << "Euler Circuit Exists!" << endl;
	 } else {
	 	cout << "Alas! There is no eulerian Circuit :( .." << endl;
	 }
	 
	 cout << "Odd numbered edge containing Nodes: " << g.odd_adj_nodes.size() << endl;
	 cout << "Even numbered edge containing Nodes: " << g.even_adj_nodes.size() << endl;
	

	 return 0;
 }
