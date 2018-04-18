#include "lomoview.h"
#include <QRectF>
#include <QtGui/QPainter>
#include <QPolygonF>
#include <QPointF>
#include <QLineF>
#include <QPen>
#include <QDebug>
qreal bilis=5;
qreal jiange=50;
qreal penwidth=1;
LoMoView::LoMoView()
{
   // m_grid = new GridTool();
   // painter=new QPainter();

    drawGridBackground(jiange,penwidth);
    connect(this,SIGNAL(newjiange(double,double)),this,SLOT(drawGridBackground(double,double)));
   // connect(this,SIGNAL(newpenwidth(double)),this,SLOT(setnewpenwidth(double)));

}

void LoMoView::wheelEvent(QWheelEvent *event)
{
    setMouseTracking(true);
    qreal sc,sc1;
    if(event->delta()>0) //鼠标滚轮向外
    {
        int numSteps = event->delta()/15/8;
        sc = pow(1.01,numSteps);
        sc1= pow(1/1.01,numSteps);
        this->scale(sc,sc);
       //m_grid->scale(sc2,sc2);
        bilis*=sc1;
        jiange*=sc1;
        penwidth*=sc1;
        emit bilichi(bilis);
        emit newjiange(jiange,penwidth);
    }
    if(event->delta()<0)  //鼠标滚轮向内
    {
        int numSteps = event->delta()/15/8;
        sc= pow(1/1.01, - numSteps);
        sc1= pow(1.01,- numSteps);
        this ->scale(sc,sc);
        bilis*=sc1;
        jiange*=sc1;
        penwidth*=sc1;
        emit bilichi(bilis);
        emit newjiange(jiange,penwidth);
      //  emit newpenwidth(penwidth);
    }
}
QPointF LoMoView ::mapToMap(QPointF p)
{
    QPointF zuobiao;
    qreal w= sceneRect().width();
    qreal h=sceneRect().height();

    qreal xzuobiao=p.x()+w;
    qreal yzuobiao=p.y()+h;

    zuobiao.setX(xzuobiao);
    zuobiao.setY(yzuobiao);
    return zuobiao;

}

void LoMoView :: mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
    this->setMouseTracking(true);
    QPoint viewPoint = event->pos();
    qDebug() <<"viewPoint" <<viewPoint << endl;
    QPointF scenePoint = this->mapToScene(viewPoint);
    QPointF MapPoint = mapToMap(scenePoint);
    emit xlabel(scenePoint.x());
    emit ylabel(scenePoint.y());
    emit mapxlabel(MapPoint.x());
    emit mapylabel(MapPoint.y());

}


//qreal LoMoView::setnewpenwidth(double penwidth)
//{
//    return penwidth;
//}

void LoMoView::drawGridBackground(double width,double penwidth)
{

        QPolygonF myPolygon1;
        myPolygon1 << QPointF(0,0) << QPointF(0,width);
        QPolygonF myPolygon2;
        myPolygon2 << QPointF(0,width) << QPointF(width,width);
        QPolygonF myPolygon3;
        myPolygon3 << QPointF(width,width) << QPointF(width,0);
        QPolygonF myPolygon4;
        myPolygon4 << QPointF(width,0) << QPointF(0,0);
        QPixmap pixmap(width, width);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        QPen pen(Qt::lightGray);
        pen.setWidth(penwidth);
        painter.setPen(pen);
        painter.translate(0, 0);
        painter.drawPolyline(myPolygon1);
        painter.drawPolyline(myPolygon2);
        painter.drawPolyline(myPolygon3);
        painter.drawPolyline(myPolygon4);
        this->setBackgroundBrush(pixmap);
}


