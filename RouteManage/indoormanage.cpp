#include "indoormanage.h"
#include "bwfile.h"
#include "Point.h"
#include "Triangle.h"
#include "Line.h"
#include  "Maps/route.h"
#include <list>
#include <QDebug>
#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>
using namespace std;
IndoorManage::IndoorManage(QWidget *parent) : QWidget(parent)
{
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);

    QVBoxLayout *ver1=new QVBoxLayout;
    ver1->setAlignment(Qt::AlignCenter);
    ver1->setSpacing(0);
    ver1->setContentsMargins(10,10,10,10);
    setLayout(ver1);

    QHBoxLayout *hor1=new QHBoxLayout;
    hor1->setAlignment(Qt::AlignLeft);
    hor1->setSpacing(10);
    hor1->setContentsMargins(0,0,0,10);

    loadMap =new QToolButton;
    loadMap->setText(QStringLiteral("加载地图"));
    showRoute =new QToolButton;
    showRoute->setText(QStringLiteral("路径寻址"));
    m_fresh = new QToolButton;
    m_fresh->setText(QStringLiteral("刷新"));
    hor1->addWidget(loadMap);
    hor1->addWidget(showRoute);
    hor1->addWidget(m_fresh);

   connect(loadMap,SIGNAL(clicked()),this, SLOT(loadIndoorMap()));
    //connect(showRoute,SIGNAL(clicked()) , this, SLOT(addWin()));
    //connect(m_fresh,SIGNAL(clicked()),this,SLOT(fresh()));
    QHBoxLayout *h2=new QHBoxLayout();
    h2->setSpacing(10);
    m_view =new ElecFencingView();
    m_scene=new DrawScene();
    m_view->setScene(m_scene);
    m_scene->setSceneRect(-m_view->rect().width()/2,-m_view->rect().height()/2,m_view->rect().width(),m_view->rect().height());
   // view1->show();
    m_view->setSizePolicy(QSizePolicy::Expanding , QSizePolicy :: Expanding);
    h2->addWidget(m_view,6);
    QVBoxLayout *v2=new QVBoxLayout();
    v2->setAlignment(Qt::AlignTop);
    v2->setSpacing(20);
    QVBoxLayout *vn1=new QVBoxLayout();
    vn1->setAlignment(Qt::AlignLeft);
    vn1->setSpacing(10);
    scenelocate =new QLabel();
    scenelocate->setText(QStringLiteral("场景坐标"));
    QHBoxLayout *hn3=new QHBoxLayout();
    hn3->setSpacing(10);
    sceneX =new QLabel();
    sceneX->setText(QStringLiteral("场景X坐标"));
    sceneY =new QLabel();
    sceneY->setText(QStringLiteral("场景Y坐标"));
    connect(m_view , SIGNAL(xlabel(double)) , this, SLOT(setscenexlabelvalue(double)));
    connect(m_view , SIGNAL(ylabel(double)) , this, SLOT(setsceneylabelvalue(double)));

    hn3->addWidget(sceneX);
    hn3->addWidget(sceneY);
    vn1->addWidget(scenelocate);
    vn1->addLayout(hn3);
    QVBoxLayout *vn2=new QVBoxLayout();
    vn2->setAlignment(Qt::AlignLeft);
    vn2->setSpacing(10);
    Maplocate =new QLabel();
    Maplocate->setText(QStringLiteral("地图坐标"));
    QHBoxLayout *hn4=new QHBoxLayout();
    hn4->setSpacing(10);
    MapX =new QLabel();
    MapX->setText(QStringLiteral("地图X坐标"));
    MapY =new QLabel();
    MapY->setText(QStringLiteral("地图Y坐标"));
    connect(m_view , SIGNAL(mapxlabel(double)) , this, SLOT(setmapxlabelvalue(double)));
    connect(m_view, SIGNAL(mapylabel(double)) , this, SLOT(setmapylabelvalue(double)));
    hn4->addWidget(MapX);
    hn4->addWidget(MapY);
    vn2->addWidget(Maplocate);
    vn2->addLayout(hn4);

    QVBoxLayout *vn5= new QVBoxLayout();
    vn5->setAlignment(Qt::AlignLeft);
    vn5->setSpacing(10);
    bilichi1=new QLabel();
    bilichi1->setText(QStringLiteral("比例尺"));
    bilichiValue = new QLabel();
    bilichiValue->setText(QStringLiteral("50Px(1格)=5米"));
    connect(m_view , SIGNAL(bilichi(double)) , this, SLOT(setbililabelvalue(double)));
    vn5->addWidget(bilichi1);
    vn5->addWidget(bilichiValue);
    v2->addLayout(vn1);
    v2->addLayout(vn2);
    v2->addLayout(vn5);
    h2->addLayout(v2,1);
    ver1->addLayout(hor1,1);
    ver1->addLayout(h2,10);

}

void IndoorManage::loadIndoorMap(){
    if(!m_scene->item_container.isEmpty())
    {
        m_scene->clear();
    }
    m_scene->open_file();
}

void IndoorManage::findPath(){
    m_astar.cbowyer.ClearBowyerWatson();
    m_astar.cbowyer.CreateHelperPoint(CPoint(-280,-280),CPoint(-280,280),CPoint(280,280),CPoint(280,-280));
    BwFile file;
    QString str = "indoorData.txt";
    file.readFile(str);
    int rowCount = file.getRow();
    qDebug() <<"row" << rowCount << endl;
    QString *buffer = file.getBuffer();
    for(int i = 0;i < rowCount;i++){
        QStringList list = buffer[i].split(' ');
        float x = list.at(0).toFloat();
        float y = list.at(1).toFloat();
        int flag = list.at(2).toInt();
        cout << "x " << x << " y " << y << endl;
        m_astar.cbowyer.AddNewPoint(CPoint(x,y),flag);
  }
    m_astar.cbowyer.UpdateNewPoint();
    m_astar.cbowyer.DelCommoooonline();
    m_astar.cbowyer.popArray();
    for(int i = 0;i < 48;i++)
        for(int j = 0;j < 48;j++)
            cout << m_astar.cbowyer.adjoinArray[i][j] <<"  ";
    std::list<CTriangle*> m_lstBowyerWatsonTriangleList= m_astar.cbowyer.GetBowyerWatsonTriangles();
    qDebug() << "m_lstBowyerWatsonTriangleList.size()" <<m_lstBowyerWatsonTriangleList.size();
    CPoint start(-250,240);
    CPoint end(230,-230);
    list<CPoint*> path = m_astar.GetPath(start,end);
    QVector<QPoint> pathVec;
    list<CPoint*>::iterator it = path.begin();
    while(it!=path.end()){
        pathVec.push_back(QPoint((*it)->x,(*it)->y));
        it++;
    }
    Route *planRoute = new Route(pathVec);
    m_scene->addItem(planRoute);
    m_view->setScene(m_scene);
}


void IndoorManage :: setscenexlabelvalue(double x)
{
    sceneX->setText(QString::number(x));
}
void IndoorManage :: setsceneylabelvalue(double y)
{
    sceneY->setText(QString::number(y));
}
void IndoorManage :: setmapxlabelvalue(double x)
{
    MapX->setText(QString::number(x));
}
void IndoorManage :: setmapylabelvalue(double y)
{
    MapY->setText(QString::number(y));
}
void IndoorManage :: setbililabelvalue(double bili)
{
    bilichiValue->setText(QStringLiteral("50Px(1格)=")+QString::number(bili)+QStringLiteral("米"));
}



