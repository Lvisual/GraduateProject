#ifndef INDOORSCENE_H
#define INDOORSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QBrush>
#include <QPen>
#include <Qpainter>
#include <QtGui>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenu>
#include <QPointF>
#include <QGraphicsLineItem>
#include <QFont>
#include <QGraphicsTextItem>
#include <QColor>
#include <QPaintEvent>
#include <QGraphicsPolygonItem>
#include "Maps/brushandcolor.h"
#include "Maps/drawtool.h"
#include "Maps/drawobj.h"
#include "astar.h"
#include <QQueue>
#include "targetitem.h"
#include "Maps/route.h"
class IndoorScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit IndoorScene(QObject *parent = 0);
    void openFile();
    QList<GraphicsItem* > item_container;
//事件处理
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
public slots:
    void drawPath();
    void clearRoute();
private:
TargetItem *startItem;
TargetItem *endItem;
QString currentPath;
Astar m_astar;
void initScene(); //初始化场景，设置地图图元
void initAstar();//初始化A*算法
void initIndoorMap();
QVector<QPoint> smooth(QVector<QPoint>vec);
QVector<CPoint> m_startendVec;
QVector<QPoint> m_obstacleVec;
Route *m_route;

};

#endif // INDOORSCENE_H
