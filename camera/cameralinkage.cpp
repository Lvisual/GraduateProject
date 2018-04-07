#include "cameralinkage.h"
#include "static3dwidget.h"
#include "display3dwidget.h"
#include "ui_cameralinkage.h"

CameraLinkage::CameraLinkage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraLinkage)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);

    QVBoxLayout *ver1=new QVBoxLayout;
    setLayout(ver1);
    ver1->setSpacing(0);
    ver1->setContentsMargins(10,10,10,10);
    ver1->setAlignment(Qt::AlignCenter);

    QWidget *widget1 =new QWidget;
    QHBoxLayout *hl1=new QHBoxLayout();
    hl1->setSpacing(10);
    widget1->setLayout(hl1);
    xuanze =new QPushButton();
    xuanze->setText(QStringLiteral("选择"));
    shanchu=new QPushButton();
    shanchu->setText(QStringLiteral("删除"));
    tianjia=new QPushButton();
    tianjia->setText(QStringLiteral("添加"));

    Xzuobiao =new QLabel;
    Xzuobiao->setText(QStringLiteral("X坐标"));
    Yzuobiao=new QLabel;
    Yzuobiao->setText(QStringLiteral("Y坐标"));
    Xvalue=new QLabel;
    Xvalue->setText(QStringLiteral("X"));

    Yvalue =new QLabel;
    Yvalue->setText(QStringLiteral("Y"));

    hl1->setAlignment(Qt::AlignLeft);
    hl1->addWidget(xuanze);
    hl1->addWidget(shanchu);
    hl1->addWidget(tianjia);
    hl1->addWidget(Xzuobiao);
    hl1->addWidget(Yzuobiao);
    hl1->addWidget(Xvalue);
    hl1->addWidget(Yvalue);
    widget1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QWidget *widget3=new Display3dWidget;
    QWidget *widget4 =new Static3DWidget;
   // QListView *listview1 =new QListView;

    m_naviView = new NaviView(this);
   // m_naviView->setVisible(false);
    NavModel* model = new NavModel(this);
    model->ReadDataFromConfig("cameralist.xml");
    NavDelegate* delegate = new NavDelegate(this);
    m_naviView->setModel(model);
    m_naviView->setItemDelegate(delegate);

    connect(widget3 , SIGNAL(displayCoor(double,double)) , this, SLOT(setscenexlabelvalue(double,double)));

    QWidget *widget2 =new QWidget;
    QHBoxLayout *hl2=new QHBoxLayout();
    hl2->setSpacing(10);
    widget2->setLayout(hl2);

    firstpage =new QPushButton();
    firstpage->setObjectName("firstPage");
//    firstpage->setText(QStringLiteral("第一页"));
    nextpage=new QPushButton();
    nextpage->setObjectName("nextPage");
//    nextpage->setText(QStringLiteral("下一页"));
    prepage=new QPushButton();
    prepage->setObjectName("prePage");
//    prepage->setText(QStringLiteral("前一页"));
    lastpage=new QPushButton();
    lastpage->setObjectName("lastPage");
//    lastpage->setText(QStringLiteral("最后一页"));
    hl2->setAlignment(Qt::AlignHCenter);
    hl2->addWidget(firstpage);
    hl2->addWidget(prepage);
    hl2->addWidget(nextpage);
    hl2->addWidget(lastpage);
    widget2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QHBoxLayout *h12 = new QHBoxLayout();
    h12->setSpacing(0);
    h12->addWidget(widget3,3);
    h12->addWidget(m_naviView,1);
    h12->addWidget(widget4,3);

    ver1->addWidget(widget1,1);
    ver1->addLayout(h12,8);
    ver1->addWidget(widget2,1);
}

CameraLinkage::~CameraLinkage()
{
    delete ui;
}

void CameraLinkage :: setscenexlabelvalue(double x,double y)
{
    Xvalue->setText(QString::number(x));
    Yvalue->setText(QString::number(y));
}
