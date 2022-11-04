#ifndef NODE_H
#define NODE_H

#include <QPoint>
class Node
{
    int m_info;
    QPointF m_coord;
public:
    Node(int inf = -1);
    Node(QPointF coord, int inf = -1);
    void setInfo(int info);
    QPointF getCoordinate() const;
    void updateCoords(QPointF coords);
    int getInfo() const;
    const QPointF operator - (const Node& n);
    bool operator == (const Node &aux);
    void operator =(const Node &aux);
    Node(const Node& n);
};
#endif // NODE_H
