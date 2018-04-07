#include "contentwidget.h"
#include "ui_contentwidget.h"

contentwidget::contentwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::contentwidget)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);



    QVBoxLayout *v1 = new QVBoxLayout();
    v1->setAlignment(Qt::AlignCenter);
    v1->setContentsMargins(10,10,10,10);
    v1->setSpacing(0);

    this->setLayout(v1);

    QVBoxLayout *v2 = new QVBoxLayout();
    v2->setSpacing(0);
    v2->setContentsMargins(0,0,0,0);
    v2->setAlignment(Qt::AlignCenter);

    HEULogo = new QLabel;
    QPixmap pixmap(":/new/images/logo.png");
    HEULogo->setPixmap(pixmap);
    HEULogo->setFixedSize(pixmap.size());
    HEULogo->setCursor(Qt::PointingHandCursor);

    welcome = new QLabel;
    welcome->setText(QStringLiteral("欢迎使用哈尔滨工程大学室内定位系统！"));
    welcome->setStyleSheet("font-size: 16px; color:QColor(122,122,122)");

    version =new QLabel;
    version->setText(QStringLiteral("当前版本号：V0.01"));
    version->setStyleSheet("font-size: 16px; color:QColor(122,122,122)");

    developer =new QLabel;
    developer->setText(QStringLiteral("发布：哈尔滨工程大学信息安全与网络技术实验室"));
    developer->setStyleSheet("font-size: 16px; color:QColor(122,122,122)");

    v2->addWidget(HEULogo);
    v2->addWidget(version);
    v2->addWidget(developer);

    QHBoxLayout *h1 =new QHBoxLayout;
    h1->setAlignment(Qt::AlignCenter);
    h1->setSpacing(0);
    h1->setContentsMargins(0,0,0,0);

    copyright =new QLabel;
    copyright->setText(QStringLiteral("copyright：@哈尔滨工程大学信息安全与网络技术实验室"));
    copyright->setStyleSheet("font-size: 10px; color:QColor(122,122,122)");
    h1->addWidget(copyright);

    v1->addLayout(v2,10);
    v1->addLayout(h1,1);

}

contentwidget::~contentwidget()
{
    delete ui;
}
