#include "mymapview.h"
#include <QWheelEvent>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QWidget>
#include <QDebug>
qreal mapscale=5;
qreal gridlen=50;
qreal mappenwidth=1;
MyMapView::MyMapView()
{
    drawGridBackground(gridlen,mappenwidth);
    connect(this,SIGNAL(newjiange(double,double)),this,SLOT(drawGridBackground(double,double)));
}

void MyMapView::wheelEvent(QWheelEvent *event)
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
        mapscale*=sc1;
        gridlen*=sc1;
        mappenwidth*=sc1;
        emit bilichi( mapscale);
        emit newjiange(gridlen,mappenwidth);
    }
    if(event->delta()<0)  //鼠标滚轮向内
    {
        int numSteps = event->delta()/15/8;
        sc= pow(1/1.01, - numSteps);
        sc1= pow(1.01,- numSteps);
        this ->scale(sc,sc);
        mapscale*=sc1;
        gridlen*=sc1;
        mappenwidth*=sc1;
        emit bilichi( mapscale);
        emit newjiange(gridlen,mappenwidth);
    }
}
QPointF MyMapView ::mapToMap(QPointF p)
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

void MyMapView :: mouseMoveEvent(QMouseEvent *event)
{
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

void MyMapView::drawGridBackground(double width,double penwidth1)
{
        qDebug() << "width" << width;
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
        painter.setPen(pen);
        painter.translate(0, 0);
        painter.drawPolyline(myPolygon1);
        painter.drawPolyline(myPolygon2);
        painter.drawPolyline(myPolygon3);
        painter.drawPolyline(myPolygon4);
        this->setBackgroundBrush(pixmap);
}
