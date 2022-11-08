#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void mouseReleaseEvent(QMouseEvent* ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void paintEvent(QPaintEvent* p);
    ~MainWindow();

private slots:
    void on_radioButton_released();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:

    Graph graph;
    Ui::MainWindow *ui;
    const int nodeRadius = 10;
    bool isFirstNode;
    Node firstNode;
};
#endif // MAINWINDOW_H
