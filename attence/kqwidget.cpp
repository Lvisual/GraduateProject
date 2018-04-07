#include "kqwidget.h"
#include "ui_kqwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QItemSelectionModel>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDateTime>
#include <QDebug>

KqWidget::KqWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KqWidget)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);


    QVBoxLayout *ver1=new QVBoxLayout;
    ver1->setAlignment(Qt::AlignCenter);
    ver1->setContentsMargins(10,10,10,10);
    ver1->setSpacing(0);
    setLayout(ver1);

    m_signin=new SignInWidget;
    m_signinreport =new SignInReport;
    m_personalDaily=new PersonalDailyReport;
    m_personalWeekly =new PersonalWeekReport;
    m_attencereport = new AttenceRecord;

    m_signin->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_personalDaily->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_personalWeekly->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_attencereport->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_signinreport->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    m_stackedwidget=new QStackedWidget;
    m_stackedwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_stackedwidget->addWidget(m_signin);
    m_stackedwidget->addWidget(m_signinreport);
    m_stackedwidget->addWidget(m_personalDaily);
    m_stackedwidget->addWidget(m_personalWeekly);
    m_stackedwidget->addWidget(m_attencereport);

    connect(m_signin, SIGNAL(turntoreport(int)),this,SLOT(showsigninreport(int)));
    connect(m_signinreport, SIGNAL(backtosignup()),this,SLOT(showsigninwidget()));

    m_status = 0;
    m_navBtn = new DHPushButton;
    m_navBtn->loadPixmap(":/new/images/right1.png");

    m_naviView = new NaviView(this);
    m_naviView->setVisible(false);
    NavModel* model = new NavModel(this);
    model->ReadDataFromConfig("attence1.xml");
    NavDelegate* delegate = new NavDelegate(this);
    m_naviView->setModel(model);
    m_naviView->setItemDelegate(delegate);

    connect(this->m_naviView, SIGNAL(clicked(const QModelIndex &)), model, SLOT(Collapse(const QModelIndex&)));
    connect(this->m_naviView, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(switchPage()));
    connect(this->m_navBtn, SIGNAL(clicked()), this, SLOT(setNav()));

    QHBoxLayout *h11= new QHBoxLayout;
    h11->setSpacing(0);
    h11->setContentsMargins(0,0,0,0);

    QHBoxLayout *h12 =new QHBoxLayout;
    h12->setSpacing(0);
    h12->addWidget(m_naviView);
    h12->addWidget(m_navBtn);

    QHBoxLayout *h13 = new QHBoxLayout;
    h13->setSpacing(0);
    h13->addWidget(m_stackedwidget);

    h11->addLayout(h12,1);
    h11->addLayout(h13,5);
    ver1->addLayout(h11);

}

KqWidget::~KqWidget()
{
    delete ui;
}

void KqWidget::switchPage(){
   int n = m_naviView->currentIndex().row();
   m_stackedwidget->setCurrentIndex(n);
}

void KqWidget::setNav(){
    if(m_status==0){
    this->m_naviView->setVisible(true);
    m_naviView->resize(this->width()/6,this->height());
    m_navBtn->loadPixmap(":/new/images/left1.png");
    m_status = 1;
 }
    else{
        m_naviView->setVisible(false);
        m_navBtn->loadPixmap(":/new/images/right1.png");
       // m_navBtn->setFixedSize(30,60);
        m_status = 0;
    }
}

void KqWidget::showsigninreport(int i){
    qDebug()<< "hehe" << i;
   //m_stackedwidget->setcurrentWidget(m_signin);
   // m_stackedwidget->setCurrentWidget(m_signin);
    m_stackedwidget->setCurrentIndex(i);
    m_signinreport->freshreport();
    m_stackedwidget->currentWidget()->show();

}

void KqWidget::showsigninwidget(){
  // m_stackedwidget->currentIndex()-1;
  // m_stackedwidget->setCurrentWidget(m_signinreport);

    m_stackedwidget->setCurrentIndex(0);

    m_signin->UpDateUI();

    //m_stackedwidget->currentWidget()->update();
   // m_signinreport->show();
}


