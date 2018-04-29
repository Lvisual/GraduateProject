#ifndef MYMAPVIEW_H
#define MYMAPVIEW_H

#include <QWidget>
#include <QGraphicsView>
class MyMapView : public QGraphicsView
{
    Q_OBJECT
public:
    MyMapView();
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
};

#endif // MYMAPVIEW_H
