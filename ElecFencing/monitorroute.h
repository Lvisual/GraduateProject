#ifndef MONITORROUTE_H
#define MONITORROUTE_H

#include <QWidget>
#include <QPainterPath>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "Maps/drawscene.h"
#include "elecfencingview.h"
#include "Maps/route.h"

namespace Ui {
class MonitorRoute;
}

class MonitorRoute : public QWidget
{
    Q_OBJECT
public:
    explicit MonitorRoute(QWidget *parent = 0);
    void jiazai();
signals:

public slots:
    void receivePoints(QPointF);
private:
    //Ui::MonitorRoute *ui;
    QVector<QPoint> m_path;
    DrawScene *scene1;
    ElecFencingView *view;
    Route *m_route;
};

#endif // MONITORROUTE_H
