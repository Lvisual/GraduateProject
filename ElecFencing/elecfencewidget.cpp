#include "elecfencewidget.h"
#include "ui_elecfencewidget.h"
#include "ccustommessagebox.h"
#include <QPointF>
#include <QPolygonF>
#include <QDebug>
#include<QThread>
#include<synchapi.h>
#include<QPoint>
#include<QObject>
#include<QMessageBox>
ElecFenceWidget::ElecFenceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ElecFenceWidget)
{

    ui->setupUi(this);
    m_historyRoute = nullptr;
    QGraphicsPolygonItem *poly=new QGraphicsPolygonItem();
    QPolygonF polygon;
    polygon<<(QPointF (0,0));
    poly->setPolygon(polygon);
    //poly->setBrush(QColor(r1,g1,b1,alpha));
   // poly->setZValue(alpha);
    poly_vector.append(poly);

    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);


    QVBoxLayout *v1 =new QVBoxLayout();
    setLayout(v1);
    v1->setAlignment(Qt::AlignLeft);
    v1->setContentsMargins(10,10,10,10);
    v1->setSpacing(0);

    QHBoxLayout *h1 =new QHBoxLayout();
    h1->setAlignment(Qt::AlignLeft);
    h1->setSpacing(10);
    h1->setContentsMargins(0,0,0,10);

//    QVBoxLayout *v1 =new QVBoxLayout();
//    setLayout(v1);
//    v1->setAlignment(Qt::AlignLeft);
//    v1->setContentsMargins(10,10,10,10);
//    v1->setSpacing(0);

//    QHBoxLayout *h1 =new QHBoxLayout();
//    h1->setAlignment(Qt::AlignLeft);
//    h1->setSpacing(10);

    jiazaiditu=new QToolButton();
    jiazaiditu->setText(QStringLiteral("加载地图"));
    connect(jiazaiditu,SIGNAL(clicked()) , this, SLOT(jiazai()));
    location =new QToolButton();
    location->setText(QStringLiteral("开始定位"));
    endlocation =new QToolButton();
    endlocation->setText(QStringLiteral("终止定位"));
    m_monitorRoute = new QToolButton();
    m_monitorRoute->setText(QStringLiteral("实时路径"));

    h1->addWidget(jiazaiditu);
    h1->addWidget(location);
    h1->addWidget(endlocation);
    h1->addWidget(m_monitorRoute);
    QHBoxLayout *h2=new QHBoxLayout();
    h2->setSpacing(10);

    view1 =new ElecFencingView();
    setPolygon();
    m_man1 = new MoveMan;
    m_man2 = new MoveMan;
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
    bilichiValue->setText(QStringLiteral("1格(50Px)=5米"));
    connect(view1 , SIGNAL(bilichi(double)) , this, SLOT(setbililabelvalue(double)));
    vn5->addWidget(bilichi1);
    vn5->addWidget(bilichiValue);

    QHBoxLayout *hn1= new QHBoxLayout();
    hn1->setSpacing(10);
    xianshiweilan=new QLabel();
    xianshiweilan->setText(QStringLiteral("显示围栏"));
    setfence = new QComboBox();
    connect(setfence, SIGNAL(currentIndexChanged(int)),this,SLOT(addfence(int)));
    //connect(setfence,SIGNAL())

    hn1->addWidget(xianshiweilan);
    hn1->addWidget(setfence);

    QHBoxLayout *hn2=new QHBoxLayout();
    hn2->setSpacing(10);
    yincangweilan=new QLabel();
    yincangweilan->setText(QStringLiteral("隐藏围栏"));
    removefence = new QComboBox();
    connect(removefence, SIGNAL(currentIndexChanged(int)),this,SLOT(deletefence(int)));
    hn2->addWidget(yincangweilan);
    hn2->addWidget(removefence);

    jiazaiwenjian = new QToolButton();
    jiazaiwenjian->setText(QStringLiteral("加载围栏文件"));


    m_simulate = new QToolButton();
    m_simulate->setText(QStringLiteral("仿真"));

    m_showHistory = new QToolButton();
    m_showHistory->setText(QStringLiteral("历史轨迹"));

    m_fresh = new QToolButton();
    m_fresh->setText(QStringLiteral("刷新"));


    connect(m_monitorRoute,SIGNAL(clicked(bool)),this,SLOT(showMonitorWin()));
    connect(jiazaiwenjian , SIGNAL (clicked()), this, SLOT(ReadFile()));
    connect(m_simulate, SIGNAL (clicked()), this, SLOT(simulate()));
    connect(m_man1,SIGNAL(currrentPos(QPointF)),this,SLOT(monitor1(QPointF)));
    connect(m_man2,SIGNAL(currrentPos(QPointF)),this,SLOT(monitor2(QPointF)));
    connect(m_showHistory,SIGNAL(clicked()),this,SLOT(showHistoryWin()));
    connect(m_fresh,SIGNAL(clicked()),this,SLOT(fresh()));

    v2->addLayout(vn1);
    v2->addLayout(vn2);
    v2->addLayout(vn5);
    v2->addWidget(jiazaiwenjian);
    v2->addLayout(hn1);
    v2->addLayout(hn2);
    v2->addWidget(m_simulate);
    v2->addWidget(m_showHistory);
    v2->addWidget(m_fresh);
    h2->addLayout(v2,1);
    v1->addLayout(h1,1);
    v1->addLayout(h2,10);
}

ElecFenceWidget::~ElecFenceWidget()
{
    delete ui;
}

void ElecFenceWidget::jiazai()
{
    if(!scene1->item_container.isEmpty())
    {
        scene1->clear();
    }
    scene1->open_file();
}


void ElecFenceWidget :: setscenexlabelvalue(double x)
{
    sceneX->setText(QString::number(x));
}
void ElecFenceWidget :: setsceneylabelvalue(double y)
{
    sceneY->setText(QString::number(y));
}
void ElecFenceWidget :: setmapxlabelvalue(double x)
{
    MapX->setText(QString::number(x));
}
void ElecFenceWidget :: setmapylabelvalue(double y)
{
    MapY->setText(QString::number(y));
}
void ElecFenceWidget :: setbililabelvalue(double bili)
{
    bilichiValue->setText(QStringLiteral("1格(50Px)=")+QString::number(bili)+QStringLiteral("米"));
}


void ElecFenceWidget:: ReadFile()
{
    QString s = QFileDialog::getOpenFileName(0, "Select A File", "/", "Txt File(*.txt)");
    if (s.isEmpty())
    {
        QMessageBox::information(0, tr("INformation"), tr("Open failed!"));
        return;
    }
    currentPath = s;
    QFile file(currentPath);
    if (file.open(QFile::ReadOnly))
    {
        QTextStream cin(&file);
        int rowcount;
        cin>>rowcount;

        while(!cin.atEnd())
        {
         int id;
         cin>>id;
         int n;
         cin>>n;
         double array[n];

         //for (int i=0;i<)

    //     QVector<QPointF> pp;

         for(int i=0;i<n;i+=2)
         {
             cin>>array[i]>>array[i+1];
//             QPointF p;
//             p.setX(array[i]);
//             p.setY(array[i+1]);
//            // i+=2;
//             pp.append(p);
         }


         for(int i=0;i<n;++i)
         {
         qDebug()<<" Item Selected : " <<array[i];
         }

         int r1,g1,b1;
         cin>>r1>>g1>>b1;
         int alpha;
         cin>>alpha;

         qDebug()<<" Item Selected : " <<r1<<"  "<<g1<<"  "<<b1<<"  "<<alpha;
         QGraphicsPolygonItem *poly=new QGraphicsPolygonItem();
         QPolygonF polygon;
         for(int i=0;i<n;i+=2)
         {
             polygon<<(QPointF (array[i],array[i+1]));
            // polygon<<pp.at(i);
         }
         poly->setPolygon(polygon);
         poly->setBrush(QColor(r1,g1,b1,alpha));
         poly->setZValue(alpha);
         poly_vector.append(poly);

        // poly_vector.at(i);
      //   removefence->addItem((QString("Fence") + QString::number(i)));
        // return poly;
        // scene1->poly_container.append(poly);
        // scene1->poly_container.at(i);
        // i++;

         //poly->paint();
        }
        setfence->addItem("");
        removefence->addItem("");
        for(int i=1;i<=rowcount;i++)
        {
            //ComboboxItem * item = new ComboboxItem(this);
            setfence->addItem((QString("Fence") + QString::number(i)));
        }
        for(int i=1;i<=rowcount;i++)
        {
            //ComboboxItem * item = new ComboboxItem(this);
            removefence->addItem((QString("Fence") + QString::number(i)));
        }
    }

    file.close();
}

void ElecFenceWidget ::addfence(int i)
{
    scene1->addItem(poly_vector.at(i));
    scene1->poly_container.append(poly_vector.at(i));
  // scene1->poly_container.at(i)->show();

  // scene1->poly_container.at(i);
  //  removefence->addItem((QString("Fence") + QString::number(i)));
   // removefence->setCurrentIndex(i);
}

void ElecFenceWidget::deletefence(int i)
{
    scene1->poly_container.removeAt(i);
    scene1->removeItem(poly_vector.at(i));
    //removefence->removeItem(i);
}

void ElecFenceWidget::simulate(){
    //scene1->addItem(m_man1);
    scene1->addItem(m_man2);
    //m_thread1.setItem(m_man1);
    m_thread2.setItem(m_man2);
   // QVector<QPoint> v1;
    QVector<QPoint> v2;
    QPoint p1(30,90);
    QPoint p2(30,130);
    QPoint p3(85,130);
    QPoint p4(125,130);
    QPoint p5(175,130);
    QPoint p6(207,130);
    QPoint p7(220,130);
    QPoint p8(300,130);
    QPoint p9(400,130);
    QPoint p10(515,130);
    QPoint p11(515,170);
    v2.push_back(p11);
    v2.push_back(p10);
    v2.push_back(p9);
    v2.push_back(p8);
    v2.push_back(p7);
    v2.push_back(p6);
    v2.push_back(p5);
    v2.push_back(p4);
    v2.push_back(p3);
    v2.push_back(p2);
    v2.push_back(p1);
    //m_thread1.setPath(v1);
    m_thread2.setPath(v2);
   // m_thread1.run();
    m_thread2.run();
}


void ElecFenceWidget::setPolygon(){
    QVector<QPoint> v;
    QPoint p1(232,-41);
    QPoint p2(153,73);
    QPoint p3(279,186);
    QPoint p4(402,49);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);
    m_position = new Position(v,4);
}

void ElecFenceWidget::monitor1(QPointF data){
        QPoint p = data.toPoint();
        if(m_position->PtInPolygon(p)){
            m_thread1.stop();
         CCustomMessageBox *warnbox = new CCustomMessageBox(CCustomMessageBox::CUSTOM_MESSAGE_WARNING,QStringLiteral("WARN"),QStringLiteral("B进入危险区域"),this);
         warnbox->show();
            // QMessageBox::warning(NULL, "warning", "您已进入警戒区", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
          //QMessageBox::warning(this,tr("warning"),tr("<p>he<span style='color: rgb(0, 176, 80);'>ll</span>o,<span style='color: rgb(255, 0, 0); font-size: 24px;'>w</span>orld!</p>"),QMessageBox::Yes);

        }
 }


void ElecFenceWidget::monitor2(QPointF data){
        QPoint p = data.toPoint();
        if(m_position->PtInPolygon(p)){
            m_thread2.stop();
         CCustomMessageBox *warnbox = new CCustomMessageBox(CCustomMessageBox::CUSTOM_MESSAGE_WARNING,QStringLiteral("WARN"),QStringLiteral("A进入危险区域"),this);
         warnbox->show();
            // QMessageBox::warning(NULL, "warning", "您已进入警戒区", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
          //QMessageBox::warning(this,tr("warning"),tr("<p>he<span style='color: rgb(0, 176, 80);'>ll</span>o,<span style='color: rgb(255, 0, 0); font-size: 24px;'>w</span>orld!</p>"),QMessageBox::Yes);

        }
 }

void ElecFenceWidget::showHistoryRoute(HistoryInfo info){
    //qDebug()<<info.id << " " <<info.time;

    if(info.id==0){
   m_access1 = m_xml1.readXml(info.time,"MapHistoryData1.xml");
   m_historyRoute = new Route(m_access1);
   scene1->addItem(m_historyRoute);
   m_access1.clear();
    }

    if(info.id==1){
    m_access2 = m_xml2.readXml(info.time,"MapHistoryData2.xml");
    m_historyRoute = new Route(m_access2);
    scene1->addItem(m_historyRoute);
    m_access2.clear();
}
}

void ElecFenceWidget::showHistoryWin(){
    qDebug() <<"hehhe";
    if(m_historyRoute!=nullptr)
        scene1->removeItem(m_historyRoute);
    m_historyChoice = new HistoryChoice;
    connect(m_historyChoice,SIGNAL(historyInfo(HistoryInfo)),this,SLOT(showHistoryRoute(HistoryInfo)));
    m_historyChoice->show();
}

void ElecFenceWidget::fresh(){
    scene1->clear();
}



void ElecFenceWidget::showMonitorWin(){
    QPoint p1(30,90);
    QPoint p8(-20,130);
    QPoint p9(-70,130);
    QPoint p10(-120,130);
    QPoint p11(-170,130);
    QPoint p12(-220,130);
    QPoint p13(-270,130);
    QPoint p14(-290,145);
    QPoint p15(-330,150);
    QPoint p16(-350,130);
    QPoint p17(-400,140);
    QPoint p18(-500,130);
    QPoint p19(-500,160);
    QPoint p20(-400,150);
    QPoint p21(-350,140);
    QPoint p22(-300,130);
    QPoint p23(-254,135);
    QPoint p24(-200,140);
    QPoint p25(-150,140);
    QPoint p26(-100,145);
    QVector<QPoint> v1;
    v1.push_back(p1);
    v1.push_back(p8);
    v1.push_back(p9);
    v1.push_back(p10);
    v1.push_back(p11);
    v1.push_back(p12);
    v1.push_back(p13);
    v1.push_back(p14);
    v1.push_back(p15);
    v1.push_back(p16);
    v1.push_back(p17);
    v1.push_back(p18);
    v1.push_back(p19);
    v1.push_back(p20);
    v1.push_back(p21);
    v1.push_back(p22);
    v1.push_back(p23);
    v1.push_back(p24);
    v1.push_back(p25);
    v1.push_back(p26);
    scene1->addItem(m_man1);
    m_monitor = new MonitorRoute;
    m_monitor->show();
    m_thread1.setItem(m_man1);
    m_thread1.setPath(v1);
    m_thread1.run();
    connect(m_man1,SIGNAL(currrentPos(QPointF)),m_monitor,SLOT(receivePoints(QPointF)));
}






