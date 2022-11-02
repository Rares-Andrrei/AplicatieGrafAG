#include "edge.h"

Edge::Edge()
{

}
bool Edge::operator == (const Edge &aux)
{
    return ((firstNode == aux.firstNode && secondNode == aux.secondNode) || (firstNode == aux.secondNode && secondNode == aux.firstNode));
}


Edge::Edge(Node *fN, Node *sN): firstNode{fN}, secondNode{sN} {}

Node* Edge::getFirstNode() const
{
    return  firstNode;
}

Node* Edge::getSecondNode() const
{
    return secondNode;
}

