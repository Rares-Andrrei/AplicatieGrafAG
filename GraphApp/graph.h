#ifndef GRAPH_H
#define GRAPH_H
#include "edge.h"
#include <vector>


using namespace std;
class Graph
{
private:
     const int nodeRadius = 10;
    vector<Node*> nodes;
    vector<Edge> edges;
    vector<vector<int>> matriceAdiacenta;
    bool oriented;
    bool windowErased;
public:
    Graph();
    bool isoriented();
    void updateNodes(int index, Node node);
    void modifyState(bool aux);
    bool addNode(Node n);
    bool addEdge(Edge a);
    void matriceAdiacentaUpdate();
    void matriceAdiacentaAfisare();
    void clearEdges();
    void clearNodes();
    void generateRandomNode();
    void generateRandomRoad();
    void generateRandomCycle();
    int getNumberOfNodes() const;
    vector<Node*> getNodes() const;
    vector<Edge> getEdges() const;
    ~Graph();
    Node* getPointerToNode(Node n);

};

#endif // GRAPH_H
