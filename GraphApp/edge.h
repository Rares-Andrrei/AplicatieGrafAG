#ifndef EDGE_H
#define EDGE_H
#include "node.h"

class Edge
{
    Node *firstNode, *secondNode;
public:
    Edge();
    Edge(Node* fN, Node* sN);
    Node* getFirstNode() const;
    Node* getSecondNode() const;
    bool operator == (const Edge &aux);
};

#endif // EDGE_H
