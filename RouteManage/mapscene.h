#ifndef MAPSCENE_H
#define MAPSCENE_H

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
#include "indoormanage.h"
class MapScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MapScene(QObject *parent = 0);
    void openFile();
    QList<GraphicsItem* > item_container;
//事件处理
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
public slots:
private:
QString currentPath;
IndoorManage m_indoorWin;
};

#endif // MAPSCENE_H
