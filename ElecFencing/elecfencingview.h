#ifndef ELECFENCINGVIEW_H
#define ELECFENCINGVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QWidget>

class ElecFencingView : public QGraphicsView
{
    Q_OBJECT
public:
    ElecFencingView();

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

};

#endif // ELECFENCINGVIEW_H
