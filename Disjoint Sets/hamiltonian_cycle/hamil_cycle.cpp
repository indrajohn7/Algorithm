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
	int weight;
	vertex* parent;
    vertex(string s,string c,int d,vertex* v, int w)
    {
        name = s;
		colour = c;
		parent = v;
		distance = d;
		weight = w;
    }
};

class graph
{
    public:
        typedef map<string, vertex *> vmap;
        vmap work;
		int total_nodes;
		vector<string> odd_adj_nodes;
		vector<string> zero_adj_nodes;
		vector<string> even_adj_nodes;
		typedef vector<string> vec_str;
		vector<vec_str> hamil_path;
		vector<vec_str> hamil_circuit;
        void addvertex(const string&,const string&,int , vertex*);
        void addedge(const string& from, const string& to, struct edge);
		void display();
		vertex* Find_Node(const string&);
		void BFS(vertex*,int);
		void Print_Path(vertex*,vertex*);
		void DFS();
		void DFS_VISIT(vertex* );
		int get_all_hamiltonian_path();
		void DFS_count(vertex*, int*);
		int print_hamil_tour(vertex* source, vector<string>*, int);
		void revive_all_node_color();
		void revive_all_node_weight();
};

void graph::addvertex(const string &name,const string &colour,int distance,vertex* par)
{
    vmap::iterator itr=work.begin();
    itr=work.find(name);
    if(itr==work.end())
    {
        vertex *v;
        v= new vertex(name,colour,distance,par, 1);
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



/**************************************************	Indra's Algorithm to find out the euler tour   **************************************************************/
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

void graph :: revive_all_node_weight()
{
	
	for (vmap :: iterator it = work.begin(); it != work.end(); it++) {
		it->second->weight = 1;
	}
}

void graph :: DFS_count(vertex* v, int* node_count)
{
	
	 v->colour = "GREY";
	 for(int i = 0; i < v->adj.size(); i++){
		 if(v->adj[i].second->colour == "WHITE" && v->adj[i].second->weight != 0){
			// v->adj[i].second->parent=v;
			 (*node_count)++;
			 DFS_count(v->adj[i].second, node_count);
		 }
		 v->colour = "BLACK";
	 }
}

int graph :: print_hamil_tour(vertex* source, vector<string> *eu_path, int nodes)
{

	string direction = "-->";

	if (source->adj.size() == 1 && source->adj[0].second->weight != -1) {
		if (nodes == total_nodes)
			return 0;
		eu_path->push_back(source->name);
		source->adj[0].second->weight = -1;
		vertex* dest = source->adj[0].second;
		eu_path->push_back(direction);
		eu_path->push_back(dest->name);
		source = source->adj[0].second;
		nodes++;
		print_hamil_tour(source, eu_path, nodes);
	} else {
		int count = 0;
		for (int i = 0; i < source->adj.size(); i++) {
			if (source->adj[i].second->weight == -1)
				count++;
		}
		if (nodes == total_nodes)
			return 0;
		if (count == source->adj.size())
			return 1;
		
		int init_dfs_count, late_dfs_count;
		init_dfs_count = late_dfs_count = 0;
		int id = -1;
		int max_visit = 0;
		for (int i = 0; i < source->adj.size(); i++) {
			if (source->adj[i].second->weight != -1) {
				source->adj[i].second->weight = 0;
				revive_all_node_color();
				late_dfs_count = 0;
				DFS_count(source, &late_dfs_count);
				if (late_dfs_count > max_visit) {
					id = i;
					max_visit = late_dfs_count;
				}
			}
		}
		if (id != -1) {
		
					source->adj[id].second->weight = -1;
					vertex* dest = source->adj[id].second;
					eu_path->push_back(source->name);
					eu_path->push_back(direction);
					eu_path->push_back(dest->name);
					source = source->adj[id].second;
					nodes++;
					print_hamil_tour(source, eu_path, nodes);
			
		}
	}

	return 0;
}

int graph :: get_all_hamiltonian_path()
{
	
	for (vmap :: iterator it = work.begin(); it != work.end(); it++) {
		vector<string> eu_path;
		revive_all_node_weight();
		vertex* source = work.find(it->first)->second;
		if (print_hamil_tour(source, &eu_path, 0) == 0) {
			hamil_path.push_back(eu_path);
		}
	}

	return hamil_path.size();
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
	 g.total_nodes = Num;
	 g.display();
	 char Source[10],Dest[10];
	 g.DFS();
	 g.display();

	 
	 cout << "Checking Whether Hamiltonian path Exists or not!" << endl;
	 
	 if (g.get_all_hamiltonian_path()) {
	 	cout << "Hamiltonian Path Exists";
	 	for (int i = 0; i < g.hamil_path.size(); i++) {
			for (int j = 0; j < g.hamil_path[i].size(); j++) {
				cout << g.hamil_path[i][j] << " ";
			}
			cout << endl;
	 	}

	 } else {
	 	cout << "Hamiltonian path does not exist!" << endl;
	 }
	 
	 cout << "Checking Whether Hamiltonian Cycle Exists or not!" << endl;

	 return 0;
 }
