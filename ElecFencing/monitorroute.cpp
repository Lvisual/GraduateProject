#include "monitorroute.h"
#include <QPainterPath>
#include <QPainter>
MonitorRoute::MonitorRoute(QWidget *parent) : QWidget(parent)

{   
   // ui->setupUi(this);
    this->setMinimumSize(900,600);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QVBoxLayout *v1=new QVBoxLayout;
    v1->setContentsMargins(10,10,10,10);
    v1->setAlignment(Qt::AlignCenter);
    v1->setSpacing(0);

    this->setLayout(v1);

    view=new ElecFencingView();
    view->show();
    view->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    scene1=new DrawScene();
    scene1->setSceneRect(-view->rect().width()/2,-view->rect().height()/2,view->rect().width(),view->rect().height());
    view->setScene(scene1);

    v1->addWidget(view);
    jiazai();
}


void MonitorRoute::receivePoints(QPointF p){
    qDebug() << "hehe";
    m_path.append(p.toPoint());
    m_route = new Route(m_path);
    scene1->addItem(m_route);
}

void MonitorRoute ::jiazai()
{
    if(!scene1->item_container.isEmpty())
    {
        scene1->clear();
    }
    scene1->openfile();
}
