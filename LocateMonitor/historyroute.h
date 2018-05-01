#ifndef HISTORYROUTE_H
#define HISTORYROUTE_H

#include <QObject>
#include <QGraphicsPathItem>
class HistoryRoute : public QGraphicsPathItem
{
public:
    HistoryRoute(QVector<QPointF> v);
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //void setPainterPath(QVector<QPoint>v);
private:
  QPainterPath m_path;
};

#endif // HISTORYROUTE_H
