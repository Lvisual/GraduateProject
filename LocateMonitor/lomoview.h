#ifndef LOMOVIEW_H
#define LOMOVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QWidget>

class LoMoView : public QGraphicsView
{
    Q_OBJECT
public:
    LoMoView();

    void wheelEvent(QWheelEvent*event);
    QPointF mapToMap(QPointF p);
    void mouseMoveEvent(QMouseEvent *event);

protected slots:

    void drawGridBackground(double width,double penwidth);
   // qreal setnewpenwidth(double penwidth);

signals:
    xlabel(double);
    ylabel(double);
    mapxlabel(double);
    mapylabel(double);
    bilichi(double);
    newjiange(double,double);
   // newpenwidth(double);

//private:
//    qreal penwidth=1;

//private:
   // QPainter *painter;


};

#endif // LOMOVIEW_H
