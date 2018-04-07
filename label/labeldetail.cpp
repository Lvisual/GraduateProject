#include "labeldetail.h"
#include <QLabel>
#include<QString>
#include<QDebug>
labelDetail::labelDetail(int id,QWidget *parent) : QWidget(parent)
{
    QVector<Employee> employeeVec = m_employeeDao.selectById(id);
    Employee info = employeeVec[0];
    this->setFixedSize(450,600);

    setWindowFlags(Qt::FramelessWindowHint);

    //表单输入
    formlayout=new QFormLayout();
    formlayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
    nameLabel = new QLabel();
    nameLabel->setText(QString::fromLocal8Bit("员工姓名："));
    ageLabel = new QLabel();
    ageLabel->setText(QString::fromLocal8Bit("员工年龄："));
    sexLabel = new QLabel();
    sexLabel->setText(QString::fromLocal8Bit("员工性别："));
    phoneLabel = new QLabel();
    phoneLabel->setText(QString::fromLocal8Bit("员工联系方式："));
    addressLabel = new QLabel();
    addressLabel->setText(QString::fromLocal8Bit("员工住址："));

    showName = new QLabel();
    showName->setText(info.name());
    showAge = new QLabel();
    QString str = QString::number(info.age());
    showAge->setText(QString(str));
    showSex = new QLabel();
    showSex->setText(info.sex());
    showPhone = new QLabel();
    showPhone->setText(info.phone());
    showAddress = new QLabel();
    showAddress->setText(info.address());

    QGridLayout *grid = new QGridLayout();
    grid->addWidget(nameLabel,0,0);
    grid->addWidget(showName,0,1);
    grid->addWidget(ageLabel,1,0);
    grid->addWidget(showAge,1,1);
    grid->addWidget(sexLabel,2,0);
    grid->addWidget(showSex,2,1);
    grid->addWidget(addressLabel,3,0);
    grid->addWidget(showAddress,3,1);
    grid->addWidget(phoneLabel,4,0);
    grid->addWidget(showPhone,4,1);

    widget_1=new QWidget();
    widget_1->setLayout(grid);
    widget_1->setObjectName("widget_1");
    widget_1->setMinimumSize(500,290);

    chk_btn=new QPushButton();
    chk_btn->setText(QString::fromLocal8Bit("确 定"));
    chk_btn->setObjectName("chk_btn");
    can_btn=new QPushButton();
    can_btn->setText(QString::fromLocal8Bit("取 消"));
    can_btn->setObjectName("can_btn");

    hor_layout=new QHBoxLayout();
    hor_layout->addWidget(chk_btn);
    hor_layout->addWidget(can_btn);
    hor_layout->setAlignment(Qt::AlignRight);
    hor_layout->setMargin(10);
    hor_layout->setSpacing(30);

    widget_2=new QWidget();
    widget_2->setLayout(hor_layout);
    widget_2->setObjectName("widget_2");
    widget_2->setFixedHeight(70);


    scrollArea=new QScrollArea();
    scrollArea->setWidget(widget_1);
    scrollArea->setObjectName("scrollArea");


    scrollArea->setWidgetResizable(false);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setFrameShape(QFrame::NoFrame);

    title=new FormTitle(this,QString::fromLocal8Bit("员工类型"));
    title->setFixedHeight(40);

    gridlayout=new QGridLayout(this);
    gridlayout->addWidget(title,0,0,1,1);
    gridlayout->addWidget(scrollArea,1,0,1,1);
    gridlayout->addWidget(widget_2,2,0,1,1);
    gridlayout->setSizeConstraint(QLayout::SetMaximumSize);
    gridlayout->setContentsMargins(0,0,0,0);
    gridlayout->setSpacing(0);

    setLayout(gridlayout);

    connect(this->chk_btn,SIGNAL(clicked()),this,SLOT(close()));
    connect(this->can_btn,SIGNAL(clicked()),this,SLOT(close()));
    connect(title,SIGNAL(showMin()),this,SLOT(showMinimized()));
    connect(title,SIGNAL(closeWidget()),this,SLOT(close()));

/********************窗口缩放***********************/

    this->setMouseTracking(true);

    isLeftPressed=false;
    curPos=0;  //鼠标左击时的位置
    this->setMinimumSize(450,10);
    this->setFixedWidth(450);
    QCursor cursor;
    cursor.setShape(Qt::ArrowCursor);
    QWidget::setCursor(cursor);

}


labelDetail::~labelDetail()
{
}

/********************窗口缩放***********************/

void labelDetail::mousePressEvent(QMouseEvent *eve)
{
    if(eve->button()==Qt::LeftButton)
    {
        this->isLeftPressed=true;
        QPoint temp=eve->globalPos();
        pLast=temp;
        curPos=countFlag(eve->pos(),countRow(eve->pos()));
        eve->ignore();
    }
}

void labelDetail::mouseReleaseEvent(QMouseEvent *eve)
{
    if(isLeftPressed)
        isLeftPressed=false;
    QApplication::restoreOverrideCursor();
    eve->ignore();
}

void labelDetail::mouseMoveEvent(QMouseEvent *eve)
{
    int poss=countFlag(eve->pos(),countRow(eve->pos()));
    setCursorType(poss);
    if(isLeftPressed)
    {
        QPoint ptemp=eve->globalPos();
        ptemp=ptemp-pLast;
        if(curPos==22)
        {
            ptemp=ptemp+pos();

            move(pos());

        }
        else
        {
            QRect wid=geometry();

            switch (curPos)
            {
            case 11:wid.setTopLeft(wid.topLeft());break;
            case 13:wid.setTopRight(wid.topRight());break;
            case 31:wid.setBottomLeft(wid.bottomLeft());break;
            case 33:wid.setBottomRight(wid.bottomRight());break;
            case 12:wid.setTop(wid.top()+ptemp.y());break;
            case 21:wid.setLeft(wid.left());break;
            case 23:wid.setRight(wid.right());break;
            case 32:wid.setBottom(wid.bottom()+ptemp.y());break;
            }
            setGeometry(wid);
        }
        pLast=eve->globalPos();
    }
    eve->ignore();
}

int labelDetail::countFlag(QPoint p, int row)
{
    if(p.y()<MARGIN)
        return 10+row;
    else if(p.y()>this->height()-MARGIN)
        return 30+row;
    else
        return 20+row;
}
void labelDetail::setCursorType(int flag)
{

    if(curPos==32)
    {
        this->setCursor(Qt::ArrowCursor);
    }
    else
    {
        this->setCursor(Qt::ArrowCursor);
    }
}
int labelDetail::countRow(QPoint p)
{
    return (p.x()<MARGIN)?1:(p.x()>(this->width()-MARGIN))?3:2;
}
