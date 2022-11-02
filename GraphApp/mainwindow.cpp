#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QPainter>
#include <vector>
#include <iostream>
#include <math.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isFirstNode = false;
}


void MainWindow::mouseReleaseEvent(QMouseEvent *ev)
{
    if(!ui->checkBox->isChecked())
    {
    if (ev->button() == Qt::RightButton)
    {
        Node n(ev->position());
        if(graph.addNode(n))
        {
            update();
        }
        // verificare suprapunere noduri in addNode
    }
    else if (ev->button() == Qt::LeftButton)
    {
        vector<Node> nodes = graph.getNodes();
        Node selected;
        bool ok = false;
        for(Node& n: nodes)
        {
            QPointF coord = n.getCoordinate();
            float dist = sqrt((ev->position().x() - coord.x())*(ev->position().x() - coord.x())+
                              (ev->position().y() - coord.y())*(ev->position().y() - coord.y()));

            if (dist <= nodeRadius)
            {
                selected = n;
                ok = true;
                break;
            }
        }

        if (ok)
        {
            if (!isFirstNode)
            {
                firstNode = selected;
                isFirstNode = true;
            }
            else
            {
               if(firstNode.getInfo() != selected.getInfo())
                {

                graph.addEdge(Edge(graph.getPointerToNode(firstNode), graph.getPointerToNode((selected))));
                isFirstNode= false;
                update();
                }
            }
        }
        else
        {
            isFirstNode = false;
        }
    }
    }

}


void MainWindow::mouseMoveEvent(QMouseEvent *ev)
{
    if(ui->checkBox->isChecked())
    {
        vector<Node> n = graph.getNodes();
        Node selected;
        int index = -1;
        for(unsigned long long i = 0; i < n.size(); i++)
        {
            QPointF coord = n[i].getCoordinate();
            float dist = sqrt((ev->position().x() - coord.x())*(ev->position().x() - coord.x())+
                              (ev->position().y() - coord.y())*(ev->position().y() - coord.y()));
            if (dist <= nodeRadius)
            {
                selected = n[i];
                index = i;
            }
        }
        if(index != -1)
        {
            selected.updateCoords(ev->pos());
            graph.updateNodes(index, selected);
            update();
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    vector<Node> nodes = graph.getNodes();
    for(Node& n:nodes)
    {
        QPointF coord = n.getCoordinate();
        QRect r(coord.x() - nodeRadius, coord.y()- nodeRadius,
                2*nodeRadius, 2*nodeRadius);
        QPen pen;
        pen.setColor(Qt::red);
        p.setPen(pen);
        p.drawEllipse(r);
        QString num = QString::number(n.getInfo());
        p.drawText(r, Qt::AlignCenter, num);
    }
    const vector<Edge> edges = graph.getEdges();
    if(graph.isoriented())
    {
        for(const Edge& e:edges)
        {
            QPointF second = e.getSecondNode()->getCoordinate();
            QPointF first = e.getFirstNode()->getCoordinate();
            QLineF aux(first, second);
            int dist = sqrt((second.x() - first.x())*(second.x() - first.x()) + (second.y() - first.y())*(second.y() - first.y()));
            aux.setLength(dist - 10);
            QPointF end = aux.pointAt(1);
            p.drawLine(aux);
            aux.setLength(dist - 20);
            QPointF start = aux.pointAt(1);
            QLineF aux2(start, end);
            QLineF perpendiculara = aux2.normalVector();
            perpendiculara.setLength(7);
            QPointF left = perpendiculara.pointAt(1);
            p.drawLine(left, end);
            perpendiculara.setLength(-7);
            QPointF right = perpendiculara.pointAt(1);
            p.drawLine(right, end);

         }
    }
    else
    {
        for(const Edge& e:edges)
        {
            p.drawLine(e.getFirstNode()->getCoordinate(), e.getSecondNode()->getCoordinate());
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radioButton_released()
{
    if(ui->radioButton->isChecked())
    {
        graph.modifyState(true);
        update();
    }
    else
    {
        graph.modifyState(false);
        update();
    }
}
