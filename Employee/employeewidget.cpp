#include "employeewidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
employeeWidget::employeeWidget(QWidget *parent) : QWidget(parent)
{

//setFixedSize(900,600);
    QVBoxLayout *v1=new QVBoxLayout();
    v1->setContentsMargins(10,10,10,10);
    v1->setAlignment(Qt::AlignCenter);
    v1->setSpacing(10);
    QHBoxLayout *h1=new QHBoxLayout();
    h1->setAlignment(Qt::AlignLeft);
    h1->setSpacing(0);
    h1->setContentsMargins(0,0,0,0);

    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Expanding);

//QHBoxLayout * hlayout1 = new QHBoxLayout();
//QVBoxLayout * vlayout = new QVBoxLayout();
m_addBtn = new QPushButton(QStringLiteral("增加"));
m_deleteBtn = new QPushButton(QStringLiteral("删除"));
m_freshBtn = new QPushButton(QStringLiteral("更新"));
m_findBtn = new QPushButton(QStringLiteral("查询"));
h1->addWidget(m_addBtn);
h1->addWidget(m_deleteBtn);
h1->addWidget(m_freshBtn);
h1->addWidget(m_findBtn);
h1->setSpacing(5);
setupModel();
m_tableView= new QTableView();
m_tableView->setModel(m_model);
m_tableView->setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Expanding);
//m_tableView->setFixedWidth(900);
//QHBoxLayout * hlayout2 = new QHBoxLayout();
//hlayout2->addWidget(m_tableView);

//vlayout->addLayout(hlayout1);
//vlayout->addLayout(hlayout2);

firstPage =new QPushButton();
//firstPage->setText(QStringLiteral("第一页"));
firstPage->setToolTip(QStringLiteral("第一页"));
firstPage->setObjectName("firstPage");
nextPage=new QPushButton();
//nextPage->setText(QStringLiteral("下一页"));
nextPage->setToolTip(QStringLiteral("下一页"));
nextPage->setObjectName("nextPage");
prePage=new QPushButton();
//prePage->setText(QStringLiteral("上一页"));
prePage->setToolTip(QStringLiteral("上一页"));
prePage->setObjectName("prePage");
lastPage=new QPushButton();
//lastPage->setText(QStringLiteral("最后一页"));
lastPage->setToolTip(QStringLiteral("最后一页"));
lastPage->setObjectName("lastPage");

widget_8 = new QWidget();
QHBoxLayout *hor_layout = new QHBoxLayout();
hor_layout->addWidget(firstPage);
hor_layout->addWidget(prePage);
hor_layout->addWidget(nextPage);
hor_layout->addWidget(lastPage);
hor_layout->setAlignment(Qt::AlignCenter);
widget_8->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
widget_8->setLayout(hor_layout);


connect(m_addBtn,SIGNAL(clicked(bool)),this,SLOT(addWin()));
connect(m_deleteBtn,SIGNAL(clicked()),this,SLOT(deleteEmployee()));
connect(m_freshBtn,SIGNAL(clicked()),this,SLOT(freshEmployee()));
connect(m_findBtn,SIGNAL(clicked()),this,SLOT(selectWin()));

v1->addLayout(h1,1);
v1->addWidget(m_tableView,8);
v1->addWidget(widget_8,1);
this->setLayout(v1);
}

void employeeWidget::setupModel(){
  m_model = new employeeModel(9,8);
  freshEmployee();
}

/*
void employeeWidget::addWin(){
    m_addForm = new baseTypeForm;
    m_addForm->show();
    connect(m_addForm,SIGNAL(newBaseTypeItem(baseTypeInfo&)),this,SLOT(addBaseTypeInfo(baseTypeInfo&)));
}
*/

void employeeWidget::addEmployee(Employee &info){
    m_employeeDao.insert(info);
    freshEmployee();
}

void employeeWidget::deleteEmployee(){
    int count = m_model->rowCount();
    int j = 0;
    for (int i = 0; i < count; ++i)
    {
        if (m_model->rowCheckStateMap[i]==Qt::Checked)
        {
            Employee info = m_model->getEmployeeVec().at(i-j);
            m_employeeDao.deleteById(info.id());
            m_model->removeRow(i-j);
            j++;
        }
    }
    freshEmployee();
}

void employeeWidget::freshEmployee(){
    Employee query;
    QVector<Employee> infos =  this->m_employeeDao.getPageList(query);
    m_model->appendEmployeeInfos(infos);
    m_model->freshModel();
    for(int i = 0;i < m_model->rowCount();i++){
             QModelIndex index = m_model->index(i,8,QModelIndex());
             m_model->setData(index,Qt::Unchecked,Qt::CheckStateRole);
    }
}

void employeeWidget::selectEmployee(int id){
  QVector<Employee> info = m_employeeDao.selectById(id);
  m_model->appendEmployeeInfos(info);
  m_model->freshModel();
}

void employeeWidget::addWin(){
    m_addForm = new addEmployeeForm;
    m_addForm->show();
    connect(m_addForm,SIGNAL(newEmployeeInfo(Employee&)),this,SLOT(addEmployee(Employee&)));
}

void employeeWidget::selectWin(){
    m_selectForm = new selectForm;
    m_selectForm->show();
    connect(m_selectForm,SIGNAL(newEmployeeId(int)),this,SLOT(selectEmployee(int)));
}




