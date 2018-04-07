#ifndef MOVEMAN_H
#define MOVEMAN_H
#include <QGraphicsItem>
#include <QGraphicsItemAnimation>
#include <QPoint>
#include<QObject>
#include<QTimeLine>
class MoveMan : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    MoveMan();
    QRectF boundingRect() const;
    void setColor(const QColor &color) { brushColor = color; }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void move(QVector<QPoint> v);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    QTimeLine* getTimer();
signals:
    void currrentPos(QPointF);
private:
    QColor brushColor;
    QTimeLine *m_timer;
};

#endif // MOVEMAN_H
