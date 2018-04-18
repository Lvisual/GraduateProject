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
private:
TargetItem *startItem;
TargetItem *endItem;

QString currentPath;
Astar m_astar;
void initAstar();
void initIndoorMap();
QVector<CPoint> m_startendVec;
};

#endif // INDOORSCENE_H
