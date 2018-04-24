#include "selectbaseform.h"

SelectBaseForm::SelectBaseForm(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(400,300);

    setWindowFlags(Qt::FramelessWindowHint);

    //表单输入
    formlayout=new QFormLayout();
    formlayout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
    idEdit=new QLineEdit();
    idEdit->setPlaceholderText(QStringLiteral("请输入基站ID"));
    formlayout->addRow(QStringLiteral("&基站ID："),idEdit);
    formlayout->setLabelAlignment(Qt::AlignRight);
    formlayout->setVerticalSpacing(40);
    formlayout->setHorizontalSpacing(10);
    formlayout->setFormAlignment(Qt::AlignVCenter);
    widget_1=new QWidget();
    widget_1->setLayout(formlayout);
    widget_1->setObjectName("widget_1");
    //widget_1->setMinimumSize(500,290);
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

    title=new FormTitle(this,QStringLiteral("基站查询"));
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

void SelectBaseForm::combine(){
    int id;
    id = this->idEdit->text().toInt();
    emit selectBaseId(id);
    this->close();
}

SelectBaseForm::~SelectBaseForm()
{
}

/********************窗口缩放***********************/

void SelectBaseForm::mousePressEvent(QMouseEvent *eve)
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

void SelectBaseForm::mouseReleaseEvent(QMouseEvent *eve)
{
    if(isLeftPressed)
        isLeftPressed=false;
    QApplication::restoreOverrideCursor();
    eve->ignore();
}

void SelectBaseForm::mouseMoveEvent(QMouseEvent *eve)
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

int SelectBaseForm::countFlag(QPoint p, int row)
{
    if(p.y()<MARGIN)
        return 10+row;
    else if(p.y()>this->height()-MARGIN)
        return 30+row;
    else
        return 20+row;
}
void SelectBaseForm::setCursorType(int flag)
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
int SelectBaseForm::countRow(QPoint p)
{
    return (p.x()<MARGIN)?1:(p.x()>(this->width()-MARGIN))?3:2;
}

