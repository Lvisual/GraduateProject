#include "signinwidget.h"
#include "ui_signinwidget.h"
#include <QDateTime>
#include <QDebug>
#include <QPixmap>
#include <QHBoxLayout>
#include <QString>
#include "string.h"
#include <QDebug>
SignInWidget::SignInWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignInWidget)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);



    QVBoxLayout *v1 =new QVBoxLayout();
    v1->setAlignment(Qt::AlignTop);
    v1->setContentsMargins(10,10,10,10);
    v1->setSpacing(0);
    this->setLayout(v1);


    QHBoxLayout *h11=new QHBoxLayout();
    h11->setAlignment(Qt::AlignLeft);
    h11->setContentsMargins(0,0,0,0);
    h11->setSpacing(10);

    QGridLayout *g1 = new QGridLayout();
    g1->setSpacing(10);
    g1->setAlignment(Qt::AlignHCenter);

    QVBoxLayout *v11=new QVBoxLayout();
    v11->setAlignment(Qt::AlignLeft);
    v11->setAlignment(Qt::AlignTop);
    v11->setSpacing(10);
    v11->setContentsMargins(0,0,0,0);

    QVBoxLayout *v13 =new QVBoxLayout();
  //  v13->setAlignment(Qt::AlignHCenter);
    v13->setAlignment(Qt::AlignTop);
    v13->setSpacing(10);
    v13->setContentsMargins(0,0,0,0);

    h11->addLayout(v11,2);
    h11->addLayout(v13,1);
//    g1->addLayout(v11,0,0,1,2);
//    g1->addLayout(v13,0,2,1,1);

    QHBoxLayout *h12=new QHBoxLayout();
    h12->setContentsMargins(0,0,0,0);
    h12->setSpacing(10);
    h12->setAlignment(Qt::AlignLeft);
    QHBoxLayout *h13=new QHBoxLayout();
    h13->setContentsMargins(0,0,0,0);
    h13->setSpacing(10);
    h13->setAlignment(Qt::AlignLeft);
    QHBoxLayout *h14=new QHBoxLayout();
    h14->setContentsMargins(0,0,0,0);
    h14->setSpacing(10);
    h14->setAlignment(Qt::AlignLeft);
    QHBoxLayout *h15=new QHBoxLayout();
    h15->setContentsMargins(0,0,0,0);
    h15->setSpacing(10);
    h15->setAlignment(Qt::AlignLeft);
    QHBoxLayout *h16=new QHBoxLayout();
    h16->setContentsMargins(0,0,0,0);
    h16->setSpacing(10);
    h16->setAlignment(Qt::AlignLeft);
    QHBoxLayout *h17=new QHBoxLayout();
    h17->setContentsMargins(0,0,0,0);
    h17->setSpacing(10);
    h17->setAlignment(Qt::AlignLeft);
    QHBoxLayout *h18=new QHBoxLayout();
    h18->setContentsMargins(0,0,0,0);
    h18->setSpacing(10);
    h18->setAlignment(Qt::AlignLeft);


    v11->addLayout(h12,1);
    v11->addLayout(h13,1);
    v11->addLayout(h14,1);
    v11->addLayout(h15,1);
    v11->addLayout(h16,1);
    v11->addLayout(h17,1);
    v11->addLayout(h18,1);

    m_employeeID =new QLabel();
    m_employeeID->setText(QStringLiteral("员工ID"));
    emplyeeID =new QLineEdit();

    m_department =new QLabel();
    m_department->setText(QStringLiteral("员工部门"));
    department = new QLineEdit();

    m_sex = new QLabel();
    m_sex->setText(QStringLiteral("性别"));
    sex = new QLineEdit();

    QDateTime time =QDateTime::currentDateTime(); //获取系统现在时间
    QString date = time.toString("yyyy-MM-dd");
    QString curr_time =time.toString("hh:mm:ss");
    QString weekDay =time.toString("ddd");


    m_signdate =new QLabel();
    m_signdate->setText(QStringLiteral("打卡日期"));
    signdate = new QLineEdit();
    signdate->setText(date);
    m_signtime =new QLabel();
    m_signtime->setText(QStringLiteral("打卡时间"));
    signtime = new QLineEdit();
    signtime->setText(curr_time);
    m_weekday = new QLabel();
    m_weekday->setText(weekDay);

    m_beizhu = new QLabel();
    m_beizhu->setText(QStringLiteral("签到状态"));
    beizhu = new QLineEdit();

    m_words = new QLabel();
    m_words->setText(QStringLiteral("备注"));
    words = new QLineEdit();
    words->setText(QStringLiteral("无"));

    setbeizhuvalue();
    m_name = new QLineEdit();
    m_name->setText(QStringLiteral("员工姓名"));
    m_name->setFixedSize(200,30);
    m_photo = new QLabel();
    QPixmap pixmap(":/new/images/Myperson.png");
    m_photo->setPixmap(pixmap);
    m_photo->setFixedSize(pixmap.size());
    m_photo->setCursor(Qt::PointingHandCursor);

//    QHBoxLayout *h19 =new QHBoxLayout();
//    h19->setAlignment(Qt::AlignHCenter);
//    h19->setContentsMargins(0,0,0,0);
//    h19->setSpacing(0);
//    h19->addWidget(m_weekday);

    QHBoxLayout *h20 =new QHBoxLayout();
    h20->setAlignment(Qt::AlignHCenter);
    h20->setContentsMargins(0,0,0,0);
    h20->setSpacing(0);
    h20->addWidget(m_photo);

    QHBoxLayout *h21 =new QHBoxLayout();
    h21->setAlignment(Qt::AlignHCenter);
    h21->setContentsMargins(0,0,0,0);
    h21->setSpacing(0);
    h21->addWidget(m_name);

  //  v13->addLayout(h19,1);
    v13->addLayout(h20,3);
    v13->addLayout(h21,1);

    h12->addWidget(m_employeeID,1);
    h12->addWidget(emplyeeID,2);
    h13->addWidget(m_department,1);
    h13->addWidget(department,2);
    h14->addWidget(m_sex,1);
    h14->addWidget(sex,2);
    h15->addWidget(m_signdate,1);
    h15->addWidget(signdate,2);
    h16->addWidget(m_signtime,1);
    h16->addWidget(signtime,2);
    h17->addWidget(m_beizhu,1);
    h17->addWidget(beizhu,2);
    h18->addWidget(m_words,1);
    h18->addWidget(words,2);


    QHBoxLayout *h1 =new QHBoxLayout();
    h1->setAlignment(Qt::AlignRight);
    h1->setContentsMargins(0,0,10,0);
    h1->setSpacing(10);
    sign_in =new QToolButton();
    sign_in->setText(QStringLiteral("签到"));
    h1->addWidget(sign_in);

    connect(this->sign_in,SIGNAL(clicked()),this,SLOT(combine()));
    connect(this->sign_in,SIGNAL(clicked()),this,SLOT(sendIndex()));

    connect(this,SIGNAL(newsigninInfo(SignIn&)),this,SLOT(addSignin(SignIn&)));

    v1->addLayout(h11,6);
    v1->addLayout(h1,1);


}

SignInWidget::~SignInWidget()
{
    delete ui;
}

void SignInWidget::combine(){
    SignIn info;
    info.setId(this->emplyeeID->text().toInt());
    info.setName(this->m_name->text());
    info.setAgent(this->department->text());
    info.setSigndate(this->signdate->text());
    info.setSigntime(this->signtime->text());
    info.setStatus(this->beizhu->text());
    info.setRemark(this->words->text());
    emit newsigninInfo(info);
    this->close();
}


void SignInWidget::addSignin(SignIn &info){
    m_signinDao.insert(info);
}

void SignInWidget::UpDateUI()
{
    emplyeeID->setText(QStringLiteral(""));
    m_name->setText(QStringLiteral(""));
    department->setText(QStringLiteral(""));
    sex->setText(QStringLiteral(""));
    QDateTime time2 =QDateTime::currentDateTime(); //获取系统现在时间
    QString date1 = time2.toString("yyyy-MM-dd");
    QString curr_time1 =time2.toString("hh:mm:ss");

    signdate->setText(date1);
    signtime->setText(curr_time1);
    setbeizhuvalue();
    words->setText(QStringLiteral("无"));

}

void SignInWidget::setbeizhuvalue()
{
    QString str ="08:30:00";
    QDateTime time_1 =QDateTime::currentDateTime(); //获取系统现在时间
    QString time_2 =time_1.toString("hh:mm:ss");
   // int result = time_2.compareTo(str);
    int result = time_2.compare(str);
    qDebug() <<"result"<<result;
    if(result<=0)
    {
        beizhu->setText(QStringLiteral("未迟到"));
        beizhu->setStyleSheet("color:green;");
    }
    else
    {
        beizhu->setText(QStringLiteral("已迟到"));
        beizhu->setStyleSheet("color:red;");
    }
}
void SignInWidget::sendIndex(){
    qDebug()<<"fuck";
    emit turntoreport(1);
}
