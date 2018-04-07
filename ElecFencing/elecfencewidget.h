#ifndef ELECFENCEWIDGET_H
#define ELECFENCEWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolButton>
#include <QLabel>
#include "Maps/drawscene.h"
#include "elecfencingview.h"
#include <QComboBox>
#include <QGraphicsPolygonItem>
#include <QList>
#include "moveman.h"
#include "position.h"
#include "thread.h"
#include "synchapi.h"
#include "Maps/route.h"
#include "historychoice.h"
#include "monitorroute.h"
#include "myxml.h"

namespace Ui {
class ElecFenceWidget;
}

class ElecFenceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ElecFenceWidget(QWidget *parent = 0);
    ~ElecFenceWidget();

public slots:
    void jiazai();

    void setscenexlabelvalue(double);
    void setsceneylabelvalue(double);
    void setmapxlabelvalue(double);
    void setmapylabelvalue(double);
    void setbililabelvalue(double);

    void ReadFile();
    void addfence(int);
    void deletefence(int);
    void simulate();
    void setPolygon();
    void monitor1(QPointF);
    void monitor2(QPointF);
    void showHistoryRoute(HistoryInfo);
    void showHistoryWin();
    void fresh();

    void showMonitorWin();
    //QPointF getPosition();

private:
    Ui::ElecFenceWidget *ui;

    DrawScene *scene1;
    ElecFencingView *view1;

    QLabel *scenelocate;
    QLabel *Maplocate;
    QLabel *bilichi1;
    QLabel *sceneX;
    QLabel *sceneY;
    QLabel *MapX;
    QLabel *MapY;
    QLabel *bilichiValue;
    QString currentPath;
  //  QToolButton *setFence;
   // QToolButton *removeFence;
    QToolButton *jiazaiwenjian;
    QToolButton *jiazaiditu;
    QToolButton *location;
    QToolButton *endlocation;
    QToolButton *m_monitorRoute;

    QToolButton *m_simulate;
    QToolButton *m_showHistory;
    QToolButton *m_fresh;

    QLabel *xianshiweilan;
    QLabel *yincangweilan;
    QComboBox *setfence;
    QComboBox *removefence;
    QList<QGraphicsPolygonItem *> poly_vector;
    MoveMan *m_man1;
    MoveMan *m_man2;
    Position *m_position;
    QVector<QPoint> m_access1;
    QVector<QPoint> m_access2;
    Thread m_thread1;
    Thread m_thread2;
    MyXml m_xml1;
    MyXml m_xml2;
    HistoryChoice *m_historyChoice;
    MonitorRoute * m_monitor;
    Route *m_historyRoute;
    //ElecThread m_elecThread;
};

#endif // ELECFENCEWIDGET_H
