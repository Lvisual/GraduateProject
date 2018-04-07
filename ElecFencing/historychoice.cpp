#include "historychoice.h"
#include <QFont>
#include <QListView>
#include <QComboBox>
#include <style.h>
#include<QApplication>
#include<QFormLayout>
#include<QVBoxLayout>
#include<QPushButton>
#include<QDebug>
HistoryChoice::HistoryChoice(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedSize(500,400);
    setWindowFlags(Qt::FramelessWindowHint);

    //表单输入
    setReflect();
    setBox();
    m_timeBoxLabel = new QLabel;
    m_timeBoxLabel->setText(QStringLiteral("请选择时间段"));
    m_idBoxLabel = new QLabel;
    m_idBoxLabel->setText(QStringLiteral("请选择员工"));
    QHBoxLayout *hlayout1 = new QHBoxLayout;
    QHBoxLayout *hlayout2 = new QHBoxLayout;
    hlayout1->addWidget(m_timeBoxLabel);
    hlayout1->addWidget(m_timeBox);
    hlayout2->addWidget(m_idBoxLabel);
    hlayout2->addWidget(m_idBox);

    hlayout1->setSpacing(12);
    hlayout1->setContentsMargins(10,40,0,40);
    hlayout1->setAlignment(Qt::AlignLeft);
    hlayout2->setSpacing(12);
    hlayout2->setContentsMargins(10,40,0,40);
    hlayout2->setAlignment(Qt::AlignLeft);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout2);

    widget_1=new QWidget();
    widget_1->setLayout(vlayout);
    widget_1->setObjectName("widget_1");
    widget_1->setMinimumSize(500,290);

    chk_btn=new QPushButton();
    chk_btn->setText(QStringLiteral("确 定"));
    chk_btn->setObjectName("chk_btn");
    can_btn=new QPushButton();
    can_btn->setText(QStringLiteral("取 消"));
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

    title=new FormTitle(this,QStringLiteral("历史轨迹"));
    title->setFixedHeight(40);

    gridlayout=new QGridLayout(this);
    gridlayout->addWidget(title,0,0,1,1);
    gridlayout->addWidget(scrollArea,1,0,1,1);
    gridlayout->addWidget(widget_2,2,0,1,1);
    gridlayout->setSizeConstraint(QLayout::SetMaximumSize);
    gridlayout->setContentsMargins(0,0,0,0);
    gridlayout->setSpacing(0);

    setLayout(gridlayout);

    connect(this->chk_btn,SIGNAL(clicked()),this,SLOT(combine()));
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

void HistoryChoice::combine(){
    HistoryInfo info;
    info.id = this->m_idBox->currentIndex();
    info.time = m_reflect[this->m_timeBox->currentText()];
    emit historyInfo(info);
    //this->close();
}


HistoryChoice::~HistoryChoice()
{
}

/********************窗口缩放***********************/

void HistoryChoice::mousePressEvent(QMouseEvent *eve)
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

void HistoryChoice::mouseReleaseEvent(QMouseEvent *eve)
{
    if(isLeftPressed)
        isLeftPressed=false;
    QApplication::restoreOverrideCursor();
    eve->ignore();
}

void HistoryChoice::mouseMoveEvent(QMouseEvent *eve)
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

int HistoryChoice::countFlag(QPoint p, int row)
{
    if(p.y()<MARGIN)
        return 10+row;
    else if(p.y()>this->height()-MARGIN)
        return 30+row;
    else
        return 20+row;
}
void HistoryChoice::setCursorType(int flag)
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
int HistoryChoice::countRow(QPoint p)
{
    return (p.x()<MARGIN)?1:(p.x()>(this->width()-MARGIN))?3:2;
}


void HistoryChoice::setBox(){
    m_idBox = new QComboBox;
    m_idBox->setObjectName("m_idBox");
    m_idBox->setView(new QListView());
    m_idBox->addItem(QStringLiteral("A员工"));
    m_idBox->addItem(QStringLiteral("B员工"));
    m_idBox->setStyleSheet("background:white;"
                         "border:1px solid rgb(111,156,207);"
                         "border-radius:4px;"
                         "height:30px;"
                         "width:285px;");
    m_timeBox = new QComboBox;
    m_timeBox->setObjectName("m_timeBox");
    m_timeBox->setView(new QListView());
    m_timeBox->addItem(QString::fromLocal8Bit("8:00-9:00"));
    m_timeBox->addItem(QString::fromLocal8Bit("9:00-10:00"));
    m_timeBox->addItem(QString::fromLocal8Bit("10:00-11:00"));
    m_timeBox->addItem(QString::fromLocal8Bit("11:00-12:00"));
    m_timeBox->addItem(QString::fromLocal8Bit("14:00-15:00"));
    m_timeBox->addItem(QString::fromLocal8Bit("15:00-16:00"));
    m_timeBox->addItem(QString::fromLocal8Bit("16:00-17:00"));
    m_timeBox->addItem(QString::fromLocal8Bit("17:00-18:00"));

    m_timeBox->setStyleSheet("background:white;"
                         "border:1px solid rgb(111,156,207);"
                         "border-radius:4px;"
                         "height:30px;"
                         "width:285px;");
}


void HistoryChoice::setReflect(){
    m_reflect.insert("8:00-9:00","first");
    m_reflect.insert("9:00-10:00","second");
    m_reflect.insert("10:00-11:00","third");
    m_reflect.insert("11:00-12:00","fourth");
    m_reflect.insert("14:00-15:00","fifth");
    m_reflect.insert("15:00-16:00","sixth");
    m_reflect.insert("16:00-17:00","seventh");
    m_reflect.insert("17:00-18:00","eighth");
}









