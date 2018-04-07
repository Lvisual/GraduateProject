#ifndef INDOORMANAGE_H
#define INDOORMANAGE_H

#include <QWidget>
#include "BowyerWatson.h"
#include "astar.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include "ElecFencing/elecfencingview.h"
#include "Maps/drawscene.h"
#include <QToolButton>
class IndoorManage : public QWidget
{
    Q_OBJECT
public:
    explicit IndoorManage(QWidget *parent = 0);
signals:
public slots:
    void setscenexlabelvalue(double);
    void setsceneylabelvalue(double);
    void setmapxlabelvalue(double);
    void setmapylabelvalue(double);
    void setbililabelvalue(double);

    void loadIndoorMap();//加载地图
    void findPath(); //路径寻址
  //  void fresh();
    //void drawPath(userPoint &data);
    //void addWin();
    //void setMap();


private:  
  Astar m_astar;   //A*
  ElecFencingView *m_view; // 地图场景
  DrawScene *m_scene; //地图场景

  QLabel *scenelocate;
  QLabel *Maplocate;
  QLabel *bilichi1;
  QLabel *sceneX;  //场景x坐标
  QLabel *sceneY; //场景y坐标
  QLabel *MapX; //地图x坐标
  QLabel *MapY; //地图y坐标
  QLabel *bilichiValue; //比例尺的值

  QToolButton *showRoute;//显示路径
  QToolButton *loadMap; //加载地图
  QToolButton *m_fresh; // 刷新
 };

#endif // INDOORMANAGE_H
