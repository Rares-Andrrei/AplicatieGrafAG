#include "node.h"
#include <math.h>

Node::Node(int info): m_info{info}
{}

Node::Node(QPointF coord, int info): m_info{info}, m_coord{coord}
{}

void Node::setInfo(int info)
{
    m_info = info;
}

QPointF Node::getCoordinate() const
{
    return m_coord;
}

void Node::updateCoords(QPointF coords)
{
    m_coord = coords;
}

int Node::getInfo() const
{
    return m_info;
}

const QPointF Node::operator - (const Node &n)
{
    QPointF aux = m_coord - n.getCoordinate();
    aux.setX(abs(aux.x()));
    aux.setY(abs(aux.y()));
    return aux;
}

bool Node::operator ==(const Node &aux)
{
    return (m_info == aux.m_info && m_coord == aux.m_coord);
}

void Node::operator =(const Node &aux)
{
    this->m_info = aux.m_info;
    this->m_coord = aux.m_coord;
}

Node::Node(const Node &n)
{
    this->m_info = n.m_info;
    this->m_coord = n.m_coord;
}


