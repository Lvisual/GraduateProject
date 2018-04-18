#ifndef TARGETITEM_H
#define TARGETITEM_H
#include<QGraphicsItem>

class TargetItem : public  QGraphicsItem
{
public:
    TargetItem(int n);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget);
    void setColor(const QColor &color) { brushColor = color; }
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    QColor brushColor;
    int m_flag;
};

#endif // TARGETITEM_H
