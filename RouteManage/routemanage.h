#ifndef ROUTEMANAGE_H
#define ROUTEMANAGE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolButton>
#include <QLabel>
#include "Maps/drawscene.h"
#include "ElecFencing/elecfencingview.h"
#include <QGraphicsPolygonItem>
#include <QList>

#include "Maps/myfile.h"
#include "Maps/dijkstrafindpath.h"
#include "Maps/route.h"
#include "Maps/moveitem.h"
#include "Maps/newroute.h"
#include "Maps/userpath.h"
#include <QMap>
#include "indoormanage.h"

namespace Ui {
class RouteManage;
}

class RouteManage : public QWidget
{
    Q_OBJECT

public:
    explicit RouteManage(QWidget *parent = 0);
    ~RouteManage();

    void getMapPath(int beginId,int endId);
    void move();

    struct pathData{
        int beginId;
        int endId;
    };

signals:
    void pathdata(pathData& data);
public slots:
    void showIndoor();
    void jiazai();
    void setscenexlabelvalue(double);
    void setsceneylabelvalue(double);
    void setmapxlabelvalue(double);
    void setmapylabelvalue(double);
    void setbililabelvalue(double);
    void fresh();
private:
    Ui::RouteManage *ui;

    DrawScene *scene1;
    ElecFencingView *view1;

    QString m_currentPath;                      // open file时的路径
    QVector<QPoint> m_allpoints;
    QVector<QPoint> m_pathpoints;
    DijkstraFindPath *findPath;
    Route * m_route;
    MoveItem *m_moveball;
    pathData m_pathdata;
    newRoute *m_newroute;
    userPath *m_userPath;
    QMap<QString,int>m_map;

    QLabel *scenelocate;
    QLabel *Maplocate;
    QLabel *bilichi1;
    QLabel *sceneX;
    QLabel *sceneY;
    QLabel *MapX;
    QLabel *MapY;
    QLabel *bilichiValue;


    QToolButton *jiazailujing;
    QToolButton *jiazaiditu;
    QToolButton *m_fresh;
    QToolButton *m_indoorMap;

    IndoorManage *m_indoorWin;

private slots:
    void drawPath(userPoint &data);
    void addWin();
    void setMap();




};

#endif // ROUTEMANAGE_H
