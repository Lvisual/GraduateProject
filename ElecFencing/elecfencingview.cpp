#include "elecfencingview.h"
#include <QRectF>
#include <QtGui/QPainter>
#include <QPolygonF>
#include <QPointF>
#include <QLineF>
#include <QPen>
#include <QDebug>
qreal bili=5;
qreal jiange1=50;
qreal penwidth1=1;
ElecFencingView::ElecFencingView()
{
   // m_grid = new GridTool();
   // painter=new QPainter();

    drawGridBackground(jiange1,penwidth1);
    connect(this,SIGNAL(newjiange(double,double)),this,SLOT(drawGridBackground(double,double)));
   // connect(this,SIGNAL(newpenwidth(double)),this,SLOT(setnewpenwidth(double)));

}

void ElecFencingView::wheelEvent(QWheelEvent *event)
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
        bili*=sc1;
        jiange1*=sc1;
        penwidth1*=sc1;
        emit bilichi(bili);
        emit newjiange(jiange1,penwidth1);
    }
    if(event->delta()<0)  //鼠标滚轮向内
    {
        int numSteps = event->delta()/15/8;
        sc= pow(1/1.01, - numSteps);
        sc1= pow(1.01,- numSteps);
        this ->scale(sc,sc);
        bili*=sc1;
        jiange1*=sc1;
        penwidth1*=sc1;
        emit bilichi(bili);
        emit newjiange(jiange1,penwidth1);
      //  emit newpenwidth(penwidth);
    }
}
QPointF ElecFencingView ::mapToMap(QPointF p)
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

void ElecFencingView :: mouseMoveEvent(QMouseEvent *event)
{
   // QGraphicsView::mouseMoveEvent(event);
    this->setMouseTracking(true);
    QPoint viewPoint = event->pos();
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

void ElecFencingView::drawGridBackground(double width,double penwidth1)
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
        pen.setWidth(penwidth1);

        qDebug()<<"penwidth:"<<penwidth1;
        painter.setPen(pen);
        painter.translate(0, 0);
        painter.drawPolyline(myPolygon1);
        painter.drawPolyline(myPolygon2);
        painter.drawPolyline(myPolygon3);
        painter.drawPolyline(myPolygon4);
        this->setBackgroundBrush(pixmap);
}


