#include "basestationform.h"
#include "ui_basestationform.h"

#include <QFont>
#include <QListView>
#include <QComboBox>
#include <style.h>
#include<QApplication>
#include<QFormLayout>
#include<QVBoxLayout>
BaseStationForm::BaseStationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaseStationForm)
{
    ui->setupUi(this);

    this->setFixedSize(450,600);

    setWindowFlags(Qt::FramelessWindowHint);
    //表单输入
    formlayout1=new QFormLayout();
    formlayout2=new QFormLayout();
    formlayout1->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
    formlayout2->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
    idEdit=new QLineEdit();
    macEdit=new QLineEdit();
   // cateEdit=new QLineEdit();
    xEdit=new QLineEdit();
    yEdit=new QLineEdit();
    zEdit=new QLineEdit();
    remarkEdit=new QLineEdit();
    m_boxLabel = new QLabel();
    m_boxLabel->setText(QStringLiteral("基站类型 : "));

    idEdit->setPlaceholderText(QStringLiteral("请输入基站ID"));
    macEdit->setPlaceholderText(QStringLiteral("请输入基站物理地址"));
    setBox();
   // cateEdit->setPlaceholderText(QStringLiteral("请输入建站类型"));
    xEdit->setPlaceholderText(QStringLiteral("基站x轴坐标"));
    yEdit->setPlaceholderText(QStringLiteral("基站y轴坐标"));
    zEdit->setPlaceholderText(QStringLiteral("基站z轴坐标"));
    remarkEdit->setPlaceholderText(QStringLiteral("备注"));


    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(m_boxLabel);
    hlayout->addWidget(m_box);
    hlayout->setSpacing(12);
    hlayout->setContentsMargins(10,40,0,40);
    hlayout->setAlignment(Qt::AlignLeft);
    formlayout1->addRow(QStringLiteral("&基站ID： "),idEdit);
    formlayout1->addRow(QStringLiteral("&基站MAC： "),macEdit);
    //formlayout2->addRow(QStringLiteral("&基站类型："),cateEdit);

    formlayout2->addRow(QStringLiteral("&基站X坐标："),xEdit);
    formlayout2->addRow(QStringLiteral("&基站Y坐标："),yEdit);
    formlayout2->addRow(QStringLiteral("&基站Z坐标："),zEdit);
    formlayout2->addRow(QStringLiteral("&备注："),remarkEdit);

    formlayout1->setLabelAlignment(Qt::AlignRight);
    formlayout1->setVerticalSpacing(40);
    formlayout1->setHorizontalSpacing(10);

    formlayout2->setLabelAlignment(Qt::AlignRight);
    formlayout2->setVerticalSpacing(40);
    formlayout2->setHorizontalSpacing(10);

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addLayout(formlayout1);
    vlayout->addLayout(hlayout);
    vlayout->addLayout(formlayout2);


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

    title=new FormTitle(this,QStringLiteral("基站信息"));
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

    //isLeftPressed=false;
    curPos=0;  //鼠标左击时的位置
    this->setMinimumSize(450,10);
    this->setFixedWidth(450);
    QCursor cursor;
    cursor.setShape(Qt::ArrowCursor);
    QWidget::setCursor(cursor);
}

void BaseStationForm::combine(){
    BaseInfo newbaseInfo;
    newbaseInfo.SetbaseID(this->idEdit->text());
    newbaseInfo.SetbaseMac(this->macEdit->text());
    newbaseInfo.SetbaseRemark(this->remarkEdit->text());
    newbaseInfo.SetbaseType(this->m_box->currentText());
    newbaseInfo.SetbaseX(this->xEdit->text());
    newbaseInfo.SetbaseY(this->yEdit->text());
    newbaseInfo.SetbaseZ(this->zEdit->text());
    emit newBaseItem(newbaseInfo);
    this->close();
}

BaseStationForm::~BaseStationForm()
{

    delete ui;
}

/********************窗口缩放***********************/

void BaseStationForm::mousePressEvent(QMouseEvent *eve)
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

void BaseStationForm::mouseReleaseEvent(QMouseEvent *eve)
{
    if(isLeftPressed)
        isLeftPressed=false;
    QApplication::restoreOverrideCursor();
    eve->ignore();
}

void BaseStationForm::mouseMoveEvent(QMouseEvent *eve)
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

int BaseStationForm::countFlag(QPoint p, int row)
{
    if(p.y()<MARGIN)
        return 10+row;
    else if(p.y()>this->height()-MARGIN)
        return 30+row;
    else
        return 20+row;
}
void BaseStationForm::setCursorType(int flag)
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
int BaseStationForm::countRow(QPoint p)
{
    return (p.x()<MARGIN)?1:(p.x()>(this->width()-MARGIN))?3:2;
}


void BaseStationForm::setBox(){
    m_box = new QComboBox;
    m_box->setObjectName("m_box");
//    m_box->setStyleSheet("QComboBox{border:1px solid gray;}"
//      "QComboBox QAbstractItemView::item{width:40px;height:20px;}" //下拉选项高度
//      "QComboBox::down-arrow{image:url(:/new/images/arrow_down.png);}" //下拉箭头
//      "QComboBox::drop-down{border:0px;}"); //下拉按钮
    m_box->setView(new QListView());
    baseTypeDao dao;
    QVector<QString>v;
    v.clear();
    v.append(dao.getType());
    for(int i = 0;i < v.size();i++){
       m_box->addItem(v[i]);
    }
    m_box->setStyleSheet("background:white;"
                         "border:1px solid rgb(111,156,207);"
                         "border-radius:4px;"
                         "height:30px;"
                         "width:285px;");
}












