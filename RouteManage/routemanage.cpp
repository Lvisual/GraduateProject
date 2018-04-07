#include "routemanage.h"
#include "ui_routemanage.h"
#define MAX 100
#include <QMap>

RouteManage::RouteManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RouteManage)
{
    ui->setupUi(this);
    setMap();
    m_newroute = nullptr;
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

    m_indoorMap = new QToolButton;
    m_indoorMap->setText(QStringLiteral("室内寻址"));
    jiazaiditu =new QToolButton;
    jiazaiditu->setText(QStringLiteral("加载地图"));
    jiazailujing =new QToolButton;
    jiazailujing->setText(QStringLiteral("路径寻址"));
    m_fresh = new QToolButton;
    m_fresh->setText(QStringLiteral("刷新"));
    hor1->addWidget(m_indoorMap);
    hor1->addWidget(jiazaiditu);
    hor1->addWidget(jiazailujing);
    hor1->addWidget(m_fresh);
    connect(jiazaiditu,SIGNAL(clicked()) , this, SLOT(jiazai()));
    connect(jiazailujing,SIGNAL(clicked()) , this, SLOT(addWin()));
    connect(m_fresh,SIGNAL(clicked()),this,SLOT(fresh()));
    connect(m_indoorMap,SIGNAL(clicked()),this,SLOT(showIndoor()));

    QHBoxLayout *h2=new QHBoxLayout();
    h2->setSpacing(10);
    view1 =new ElecFencingView();
    scene1=new DrawScene();
    view1->setScene(scene1);
    //scene1->drawGridBackground(50);
    scene1->setSceneRect(-view1->rect().width()/2,-view1->rect().height()/2,view1->rect().width(),view1->rect().height());
    view1->show();
    view1->setSizePolicy(QSizePolicy::Expanding , QSizePolicy :: Expanding);
    h2->addWidget(view1 ,6);
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
    connect(view1 , SIGNAL(xlabel(double)) , this, SLOT(setscenexlabelvalue(double)));
    connect(view1 , SIGNAL(ylabel(double)) , this, SLOT(setsceneylabelvalue(double)));

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
    connect(view1 , SIGNAL(mapxlabel(double)) , this, SLOT(setmapxlabelvalue(double)));
    connect(view1 , SIGNAL(mapylabel(double)) , this, SLOT(setmapylabelvalue(double)));
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
    connect(view1 , SIGNAL(bilichi(double)) , this, SLOT(setbililabelvalue(double)));
    vn5->addWidget(bilichi1);
    vn5->addWidget(bilichiValue);


    v2->addLayout(vn1);
    v2->addLayout(vn2);
    v2->addLayout(vn5);
    h2->addLayout(v2,1);
    ver1->addLayout(hor1,1);
    ver1->addLayout(h2,10);

}

RouteManage::~RouteManage()
{
    delete ui;
}

void RouteManage::jiazai()
{
    if(!scene1->item_container.isEmpty())
    {
        scene1->clear();
    }
    scene1->open_file();
}


void RouteManage :: setscenexlabelvalue(double x)
{
    sceneX->setText(QString::number(x));
}
void RouteManage :: setsceneylabelvalue(double y)
{
    sceneY->setText(QString::number(y));
}
void RouteManage :: setmapxlabelvalue(double x)
{
    MapX->setText(QString::number(x));
}
void RouteManage :: setmapylabelvalue(double y)
{
    MapY->setText(QString::number(y));
}
void RouteManage :: setbililabelvalue(double bili)
{
    bilichiValue->setText(QStringLiteral("50Px(1格)=")+QString::number(bili)+QStringLiteral("米"));
}


void RouteManage::getMapPath(int beginId,int endId){
    MyFile *qtFile1 = new MyFile();
    QString filename1 = "MapNode.txt";
    qtFile1->readFile(filename1);
    int vexNum = qtFile1->getRow();
    int vexs[vexNum];
    QString* strs = qtFile1->getBuffer();
    for(int i = 0;i <vexNum;i++){
           QStringList list = strs[i].split(" ");
           QPoint p(list.at(1).toDouble(),list.at(2).toDouble());
           m_allpoints.push_back(p);
           vexs[i]=list.at(0).toInt();
    }
  //将邻接表读出
    int prev[MAX] = {0};
    int dist[MAX] = {0};
    MyFile *qtFile2 = new MyFile();
    QString filename2 = "MapEdge.txt";
    qtFile2->readFile(filename2);
    int edgeNum = qtFile2->getRow();
     qDebug()<<edgeNum;
     EData *edges[edgeNum];
    QString* strs2 = qtFile2->getBuffer();
    for(int i = 0;i <edgeNum;i++){
        QStringList list2 = strs2[i].split(" ");
         int s = list2.at(0).toInt();
         int e = list2.at(1).toInt();
         int w = list2.at(2).toInt();
        // qDebug()<<s <<e<< w;
         edges[i] = new EData(s,e,w);
        // qDebug() <<edges[i]->weight;
    }
   DijkstraFindPath *dij = new DijkstraFindPath(vexs,vexNum,edges,edgeNum);
   QStack<int> st = dij->dijkstra(beginId,endId,prev,dist);
   //qDebug() << st.size();
       m_pathpoints.clear();
       //qDebug()<<m_allpoints[9];
       while(st.size()){
       m_pathpoints.push_back(m_allpoints[st.pop()]);
}
}

void RouteManage::showIndoor(){
    m_indoorWin = new IndoorManage;
    m_indoorWin->show();
}


void RouteManage::move(){
    m_moveball = new MoveItem();
    QTimeLine *timer = new QTimeLine(15000);
    timer->setFrameRange(0,100);
    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
    animation->setItem(m_moveball);
    animation->setTimeLine(timer);
    for(int i = 0; i < m_pathpoints.size(); ++i)
    animation->setPosAt(i / 50.0, QPointF(m_pathpoints[i]));
    timer->start();
}


void RouteManage::drawPath(userPoint &data){
    int start = m_map[data.start];
    int end = m_map[data.end];
    getMapPath(start,end);
    qDebug()<< "get the path";
    m_newroute = new newRoute(m_pathpoints);
    scene1->addItem(m_newroute);
}

void RouteManage::addWin(){
    if(m_newroute!=nullptr)
    scene1->removeItem(m_newroute);
    m_userPath = new userPath;
    m_userPath->show();
    connect(m_userPath,SIGNAL(userPointSignal(userPoint&)),this,SLOT(drawPath(userPoint&)));
}


void RouteManage::setMap(){
   m_map.insert("243",0);
   m_map.insert("240",1);
   m_map.insert("229",2);
}
void RouteManage::fresh(){
  scene1->clear();
}

