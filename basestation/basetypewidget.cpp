#include "basetypewidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
baseTypeWidget::baseTypeWidget(QWidget *parent) : QWidget(parent)
{
setFixedSize(900,600);
QHBoxLayout * hlayout1 = new QHBoxLayout();
QVBoxLayout * vlayout = new QVBoxLayout();
m_addBtn = new QPushButton(QStringLiteral("增加"));
m_deleteBtn = new QPushButton(QStringLiteral("删除"));
m_freshBtn = new QPushButton(QStringLiteral("更新"));
m_findBtn = new QPushButton(QStringLiteral("查询"));
hlayout1->addWidget(m_addBtn);
hlayout1->addWidget(m_deleteBtn);
hlayout1->addWidget(m_freshBtn);
hlayout1->addWidget(m_findBtn);
hlayout1->setAlignment(Qt::AlignLeft);
setupModel();
m_tableView= new QTableView();
m_tableView->setModel(m_model);
m_tableView->setFixedWidth(900);
QHBoxLayout * hlayout2 = new QHBoxLayout();
hlayout2->addWidget(m_tableView);

vlayout->addLayout(hlayout1);
vlayout->addLayout(hlayout2);
connect(m_addBtn,SIGNAL(clicked(bool)),this,SLOT(addWin()));
connect(m_deleteBtn,SIGNAL(clicked()),this,SLOT(deleteBaseType()));
connect(m_freshBtn,SIGNAL(clicked()),this,SLOT(freshBaseType()));
this->setLayout(vlayout);
}

void baseTypeWidget::setupModel(){
  m_model = new baseTypeModel(5,4);
  freshBaseType();
}

void baseTypeWidget::addWin(){
    m_addForm = new baseTypeForm;
    m_addForm->show();

    connect(m_addForm,SIGNAL(newBaseTypeItem(baseTypeInfo&)),this,SLOT(addBaseTypeInfo(baseTypeInfo&)));
}

void baseTypeWidget::addBaseTypeInfo(baseTypeInfo &info){
    m_typeDao.insert(info);
    freshBaseType();
}

void baseTypeWidget::deleteBaseType(){
    int count = m_model->rowCount();
    int j = 0;
    for (int i = 0; i < count; ++i)
    {
        if (m_model->rowCheckStateMap[i]==Qt::Checked)
        {
            baseTypeInfo info = m_model->getTypeBaseInfo().at(i-j);
            m_typeDao.deleteById(info.getTypeId().toInt());
            m_model->removeRow(i-j);
            j++;
        }
    }
    freshBaseType();
}




void baseTypeWidget::freshBaseType(){
    for(int i = 0;i < m_model->rowCount();i++){
             QModelIndex index = m_model->index(i,4,QModelIndex());
             m_model->setData(index,Qt::Unchecked,Qt::CheckStateRole);
    }
    baseTypeInfo query;
    QVector<baseTypeInfo> infos =  this->m_typeDao.getPageList(query);
    m_model->appendBaseTypeInfos(infos);
    m_model->freshModel();
}






