#include "targetitem.h"
#include <QRectF>
#include <QPainter>
TargetItem::TargetItem(int n)
{
    m_flag =n;
    brushColor = Qt::red;
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsMovable,false);
    setAcceptHoverEvents(true);
}

QRectF TargetItem::boundingRect() const
{
    qreal adjust = 0.5;
    return QRectF(-10 - adjust, -10 - adjust,
                  20 + adjust, 20 + adjust);
}

void TargetItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget)
{   //qDebug("************TargetItem::paint*****************");
    if(hasFocus()) {
        painter->setPen(QPen(QColor(255,255,255,200)));
    } else {
        painter->setPen(QPen(QColor(100,100,100,100)));
    }
    painter->setBrush(brushColor);
    if(m_flag==0){
    //painter->drawRect(-10, -10, 20, 20);
    QPixmap map(":/new/images/start3.png");
    painter->drawPixmap(-10,-10,32,32,map);
    }
    else{
        QPixmap map(":/new/images/end3.png");
        painter->drawPixmap(-10,-10,32,32,map);
    }

}

// ��갴���¼������������ñ������ͼ�����ý��㣬���ı������
void TargetItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug("************TargetItem::mousePressEvent*****************");
    setFocus();
    //setCursor(Qt::ClosedHandCursor);
}
