#include "graph.h"
#include "qevent.h"
#include <iostream>
#include <QFile>
#include <QPainter>
#include <QRandomGenerator>
Graph::Graph()
{
    oriented = false;
}

bool Graph::isoriented()
{
    return oriented;
}
void Graph::updateNodes(int index, Node node)
{
    *nodes[index] = node;
}

void Graph::modifyState(bool aux)
{
    oriented = aux;
    edges.clear();
    for(unsigned long long i = 0; i < matriceAdiacenta.size(); i++)
    {
        for(unsigned long long  j = 0; j < matriceAdiacenta.size(); j++)
        {
            matriceAdiacenta[i][j] = 0;
        }
    }
}

bool Graph::addNode(Node n)
{
    bool verificare = true;
    for(auto aux : nodes)
    {
        QPointF aux2 = n - *aux;
        if(aux2.x() < 2*nodeRadius && aux2.y() < 2*nodeRadius)
        {
           verificare = false;
        }
    }
    if(verificare)
    {
        n.setInfo((int)nodes.size() + 1);
        Node* newNode = new Node;
        *newNode = n;
         nodes.push_back(newNode);
        matriceAdiacentaUpdate();
        matriceAdiacentaAfisare();
        return true;
    }
    return false;
}
bool Graph::addEdge(Edge a)
{
    bool exista = false;
    for(Edge aux : edges)
    {
        if (aux == a)
        {
            exista = true;
            break;
        }
    }
    if(!exista)
    {
        edges.push_back(a);
        matriceAdiacentaUpdate();
        matriceAdiacentaAfisare();
        return true;
    }
    else
    {
        return false;
    }

}
void Graph::matriceAdiacentaAfisare()
{
    QFile file("D:\\GitRepository\\AplicatieGrafAG\\GraphApp\\date.txt");
    if(file.open(QFile::Append | QFile::Text))
    {
            QTextStream out(&file);
            for(unsigned long long i = 0; i <= matriceAdiacenta.size(); i++)
            {
                out << i << " ";
            }
            out << "\n";
            for(unsigned long long i = 0; i < matriceAdiacenta.size(); i++)
            {
                out << i + 1 << " ";
                for(unsigned long long j = 0; j < matriceAdiacenta.size(); j++)
                {
                    out << matriceAdiacenta[i][j] << " ";
                }
                out << "\n";
            }
             out << "\n\n";

    }
    file.close();
}

void Graph::clearEdges()
{
    edges.clear();
}

void Graph::clearNodes()
{
    edges.clear();
    nodes.clear();
}

void Graph::generateRandomNode()
{
    bool added = false;
    while(!added)
    {
    QPointF randomCoords(QRandomGenerator::global()->bounded(10, 650), QRandomGenerator::global()->bounded(10, 550));
    Node newNode(randomCoords);
    if(addNode(newNode))
        added = true;
    }
}

void Graph::generateRandomRoad()
{
    oriented = true;
    if(nodes.size() == 0)
    {
        return;
    }
    int nrEdges = 0;
    Node* start = nodes[0];
    Node* end = nodes[int(nodes.size()-1)];
    std::vector<bool> pathNode(nodes.size(), false);
    pathNode[0] = true;
    int size = nodes.size();
    while(nrEdges != size - 1)
    {
        Node* auxNode = start;
        int k = QRandomGenerator::global()->bounded(1, size);
        if(!pathNode[k])
        {
          Node* v = nodes[k];
          Edge auxEdge(auxNode, v);
          addEdge(auxEdge);
          pathNode[k] = true;
          nrEdges++;
          start = v;
          if(v == end)
          {
              break;
          }
        }
    }
}

void Graph::generateRandomCycle()
{
    oriented = true;
    if(nodes.size() == 0)
    {
        return;
    }
    int size = nodes.size();
    int start = QRandomGenerator::global()->bounded(0, size - 1);
    int nrEdges = 0;
    std::vector<bool> pathNode(nodes.size(), false);
    pathNode[start] = true;
    Node* startNode = nodes[start];
    while(nrEdges != size)
    {
        Node* auxNode = startNode;
        int k = QRandomGenerator::global()->bounded(0, size);
        if(!pathNode[k])
        {
          Node* v = nodes[k];
          Edge auxEdge(auxNode, v);
          addEdge(auxEdge);
          pathNode[k] = true;
          nrEdges++;
          startNode = v;
        }
        if(k == start && nrEdges >= 2)
        {
            Edge auxEdge(auxNode, nodes[start]);
            addEdge(auxEdge);
            break;
        }
    }
}
void Graph::matriceAdiacentaUpdate()
{
    if(nodes.size() != matriceAdiacenta.size())
    {
        matriceAdiacenta.resize(nodes.size());
        for(unsigned long long i = 0; i < nodes.size(); i++)
        {
            matriceAdiacenta[i].resize(nodes.size());
        }

    }
    else
    {
        if(oriented)
        {
            matriceAdiacenta[edges.back().getFirstNode()->getInfo()-1][edges.back().getSecondNode()->getInfo()-1] = 1;
        }
        else
        {
            matriceAdiacenta[edges.back().getFirstNode()->getInfo()-1][edges.back().getSecondNode()->getInfo()-1] = 1;
            matriceAdiacenta[edges.back().getSecondNode()->getInfo()-1][edges.back().getFirstNode()->getInfo()-1] = 1;
        }
    }
}
int Graph::getNumberOfNodes() const {return (int)nodes.size();}
vector<Node*> Graph::getNodes() const {return nodes;}
vector<Edge> Graph::getEdges() const {return edges;}
Graph::~Graph()
{
    for (unsigned long long i = 0; i < nodes.size(); ++i)
    {
           delete nodes[i];
    }
}
Node *Graph::getPointerToNode(Node n)
{
    for(unsigned long long i = 0; i < nodes.size(); i++)
    {
        if(*nodes[i] == n)
        {
            return *(nodes.begin() + i);
        }
    }
    return nullptr;
}
