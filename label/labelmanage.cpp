#include "labelmanage.h"
#include "ui_labelmanage.h"

labelmanage::labelmanage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::labelmanage)
{
    ui->setupUi(this);
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
m_addBtn = new QPushButton(QString::fromLocal8Bit("增加"));
m_deleteBtn = new QPushButton(QString::fromLocal8Bit("删除"));
m_freshBtn = new QPushButton(QString::fromLocal8Bit("刷新"));
m_findBtn = new QPushButton(QString::fromLocal8Bit("查询"));
h1->addWidget(m_addBtn);
h1->addWidget(m_deleteBtn);
h1->addWidget(m_freshBtn);
h1->addWidget(m_findBtn);
h1->setSpacing(5);
setupModel();
m_tableView= new QTableView();
m_tableView->setModel(m_model);
m_tableView->setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Expanding);
m_delegateBtn = new ButtonDelegate;
m_tableView->setItemDelegateForColumn(7,m_delegateBtn);



QHBoxLayout *hor_layout = new QHBoxLayout();

widget_9 = new QWidget();

firstPage =new QPushButton();
//firstPage->setText(QStringLiteral("第一页"));
//firstPage->setToolTip(QStringLiteral("第一页"));
firstPage->setObjectName("firstPage");
nextPage=new QPushButton();
//nextPage->setText(QStringLiteral("下一页"));
//nextPage->setToolTip(QStringLiteral("下一页"));
nextPage->setObjectName("nextPage");
prePage=new QPushButton();
//prePage->setText(QStringLiteral("上一页"));
//prePage->setToolTip(QStringLiteral("上一页"));
prePage->setObjectName("prePage");
lastPage=new QPushButton();
//lastPage->setText(QStringLiteral("最后一页"));
//lastPage->setToolTip(QStringLiteral("最后一页"));
lastPage->setObjectName("lastPage");

hor_layout->addWidget(firstPage);
hor_layout->addWidget(prePage);
hor_layout->addWidget(nextPage);
hor_layout->addWidget(lastPage);
hor_layout->setAlignment(Qt::AlignCenter);
widget_9->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
widget_9->setLayout(hor_layout);

connect(m_addBtn,SIGNAL(clicked(bool)),this,SLOT(addWin()));
connect(m_deleteBtn,SIGNAL(clicked()),this,SLOT(deleteLabel()));
connect(m_freshBtn,SIGNAL(clicked()),this,SLOT(freshLabel()));
connect(m_findBtn,SIGNAL(clicked()),this,SLOT(selectWin()));

v1->addLayout(h1,1);
v1->addWidget(m_tableView,8);
v1->addWidget(widget_9,1);
this->setLayout(v1);

}

labelmanage::~labelmanage()
{
    delete ui;
}
void labelmanage::setupModel(){
  m_model = new LabelModel(8,0);
  freshLabel();
}

void labelmanage::addWin(){
    m_addForm = new addLabelForm;
    m_addForm->show();
    connect(m_addForm,SIGNAL(newLabelInfo(Label&)),this,SLOT(addLabel(Label&)));
}

void labelmanage::addLabel(Label &info){
    m_labelDao.insert(info);
    freshLabel();
}

void labelmanage::deleteLabel(){
    int count = m_model->rowCount();
    int j = 0;
    for (int i = 0; i < count; ++i)
    {
        if (m_model->rowCheckStateMap[i]==Qt::Checked)
        {
            Label info = m_model->getLabelVec().at(i-j);
            m_labelDao.deleteById(info.lableId());
            m_model->removeRow(i-j);
            j++;
        }
    }
    freshLabel();
}

void labelmanage::freshLabel(){
    Label query;
    QVector<Label> infos =  this->m_labelDao.getPageList(query);
    m_model->appendLabelInfos(infos);
    m_model->freshModel();
    for(int i = 0;i < m_model->rowCount();i++){
             QModelIndex index = m_model->index(i,0,QModelIndex());
             m_model->setData(index,Qt::Unchecked,Qt::CheckStateRole);
    }
}

void labelmanage::selectLabel(int id){
  QVector<Label> info = m_labelDao.selectById(id);
  m_model->appendLabelInfos(info);
  m_model->freshModel();
}

void labelmanage::selectWin(){
    m_selectLabelForm = new selectLabelForm;
    m_selectLabelForm->show();
    connect(m_selectLabelForm,SIGNAL(newLabelId(int)),this,SLOT(selectLabel(int)));
}

