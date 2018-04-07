#include "signinreport.h"
#include "ui_signinreport.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

SignInReport::SignInReport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignInReport)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *v1=new QVBoxLayout();
    v1->setContentsMargins(10,10,10,10);
    v1->setSpacing(0);
    v1->setAlignment(Qt::AlignCenter);
    setLayout(v1);

    QHBoxLayout *h1 =new QHBoxLayout();
    h1->setSpacing(10);
    h1->setContentsMargins(0,0,0,0);
    h1->setAlignment(Qt::AlignLeft);

    fresh=new QToolButton();
    fresh->setText(QStringLiteral("刷新"));

    searchbyID=new QLineEdit();
    searchbyID->setFixedSize(200,40);
    searchbyID->setText(QStringLiteral("请输入待查员工的ID"));

    search =new QToolButton();
    search->setText(QStringLiteral("查询"));

    h1->addWidget(fresh);
    h1->addWidget(searchbyID);
    h1->addWidget(search);
    connect(fresh,SIGNAL(clicked()),this,SLOT(freshsigninreport()));

    setupModel();
    freshreport();

    tableview=new QTableView();
    tableview->setModel(m_model);
    tableview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout *h2 =new QHBoxLayout();
    h2->setSpacing(10);
    h2->setContentsMargins(0,0,0,0);
    h2->setAlignment(Qt::AlignRight);

    back=new QToolButton();
    back->setText(QStringLiteral("返回签到"));

    h2->addWidget(back);

    connect(back,SIGNAL(clicked()),this,SIGNAL(backtosignup()));

    v1->addLayout(h1,1);
    v1->addWidget(tableview,8);
    v1->addLayout(h2,1);


}

SignInReport::~SignInReport()
{
    delete ui;
}

void SignInReport::setupModel(){
  m_model = new SignInModel(9,8);
  freshsigninreport();
}


void SignInReport::freshsigninreport(){
    SignIn query;
    QVector<SignIn> infos =  this->m_signinDao.getPageList(query);
    m_model->appendsigninInfos(infos);
    m_model->freshModel();
    for(int i = 0;i < m_model->rowCount();i++){
             QModelIndex index = m_model->index(i,8,QModelIndex());
             m_model->setData(index,Qt::Unchecked,Qt::CheckStateRole);
    }
}
void SignInReport::freshreport(){
    SignIn query;
    QVector<SignIn> infos =  this->m_signinDao.getPageList(query);
    m_model->appendsigninInfos(infos);
    m_model->freshModel();
    for(int i = 0;i < m_model->rowCount();i++){
             QModelIndex index = m_model->index(i,8,QModelIndex());
             m_model->setData(index,Qt::Unchecked,Qt::CheckStateRole);
    }
}



