#include "MoveMan.h"
#include <QPainter>
#include <QPen>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include<QDebug>
MoveMan::MoveMan()
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsMovable,true);
    this->setFlag(ItemSendsGeometryChanges,true);
    m_timer = new QTimeLine(15000);
}

void MoveMan::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(0, 160, 230));
    painter->setPen(pen);
    painter->setBrush(QColor(247, 160, 57));
    painter->drawEllipse(0,0,10,10);
}


QRectF MoveMan::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-10 - adjust, -10 - adjust,
                  20 + adjust, 20 + adjust);
}

 void MoveMan::move(QVector<QPoint> v){

         m_timer->setFrameRange(0,100);
         m_timer->setCurveShape(QTimeLine::LinearCurve);
         QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
         animation->setItem(this);
         animation->setTimeLine(m_timer);
         for(int i = 0; i < v.size(); ++i){
         animation->setPosAt(i/20.0, QPointF(v[i]));
         }
         m_timer->start();
 }

  QVariant MoveMan::itemChange(GraphicsItemChange change, const QVariant &value){
      if(change == this->ItemPositionHasChanged)
        emit currrentPos(this->pos());
        //qDebug()<<this->pos();
      return QGraphicsItem::itemChange(change,value);
  }

QTimeLine* MoveMan::getTimer(){
    return m_timer;
}







