#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Vertex;

class Edge
{
public:
    Edge(Vertex *org, Vertex *dest, int dist)
    {
        origin = org;
        destination = dest;
        distance = dist;
    }

    Vertex* getOrigin() {return origin;}
    Vertex* getDestination() {return destination;}
    int getDistance() {return distance;}
private:
    Vertex* origin;
    Vertex* destination;
    int distance;
};


class Vertex
{
public:
    Vertex(string id)
    {
        name = id;
    }

    void addEdge(Vertex *v, int dist)
    {
        Edge newEdge(this, v, dist);
        edges.push_back(newEdge);
    }

    void printEdges()
    {
        cout << name << ":" << endl;
        for (int i = 0; i < edges.size(); i++)
        {
        Edge e = edges[i];
        cout << e.getDestination()->getName() <<
            " - " << e.getDistance() << endl;
        }
        cout << endl;
    }

    string getName() {return name;} 
    vector<Edge> getEdges() {return edges;}

private:
    string name;
    vector<Edge> edges;
};


class Graph
{
public:
    Graph() {}

    void insert(Vertex *v)
    {
        vertices.push_back(v);
    }

    void printGraph()
    {
        for (int i = 0; i < vertices.size(); i++)
            vertices[i]->printEdges();
    }

private:
    vector<Vertex*> vertices;
};

int main()
{
Graph g;

Vertex v1 = Vertex("Seattle");
Vertex v2 = Vertex("Portland");
Vertex v3 = Vertex("Everett");
Vertex v4 = Vertex("Lynnwood");
Vertex v5 = Vertex("Northgate");
Vertex v6 = Vertex("Bellevue");
Vertex v7 = Vertex("Arlington");
Vertex v8 = Vertex("Bellingham");


Vertex *vp1 = &v1;
Vertex *vp2 = &v2;
Vertex *vp3 = &v3;
Vertex *vp4 = &v4;
Vertex *vp5 = &v5;
Vertex *vp6 = &v6;
Vertex *vp7 = &v7;
Vertex *vp8 = &v8;


v1.addEdge(vp2, 100);
v1.addEdge(vp6, 20);
v2.addEdge(vp1, 100);
v3.addEdge(vp1, 30);
v3.addEdge(vp4, 10);
v3.addEdge(vp7, 20);
v4.addEdge(vp5, 15);
v5.addEdge(vp1, 10);
v6.addEdge(vp1, 20);
v8.addEdge(vp7, 45);


g.insert(vp1);
g.insert(vp2);
g.insert(vp3);
g.insert(vp4);
g.insert(vp5);
g.insert(vp6);
g.insert(vp7);
g.insert(vp8);


g.printGraph();

//system("PAUSE");

return 1;
}