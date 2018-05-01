#include "historyroute.h"
#include <QPen>
HistoryRoute::HistoryRoute(QVector<QPointF> v)
{
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(5);
    pen.setBrush(Qt::green);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    this->setPen(pen);
    this->setFlag (QGraphicsItem::ItemIsPanel);
    m_path.moveTo(v[0].x(),v[0].y());
    for(int i = 1;i < v.size();i++){
        m_path.lineTo(v[i].x(),v[i].y());
    }
    this->setPath(m_path);
}
