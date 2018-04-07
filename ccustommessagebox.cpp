#include "ccustommessagebox.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QStyle>
#include<QPainter>
CCustomMessageBox::CCustomMessageBox(CUSTOM_MESSAGE_TYPE type, const QString &strTitle, const QString &strInfo,QWidget *parent, Qt::WindowFlags flags)
    :QDialog(parent, flags), m_eCustomType(type)
{
    QPalette palette=QPalette(Qt::white);
    //画刷的活动颜色组
    palette.setBrush(QPalette::WindowText,Qt::red);//窗口前景颜色
    this->setPalette(palette);
    initialize(strInfo);
    //<span style="white-space:pre">  </span>
    alignment();
    setWindowTitle(strTitle);
    setFixedSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    //setMinimumSize(MIN_WIDTH, MIN_WEIGHT);
}
CCustomMessageBox::~CCustomMessageBox()
{

}

//设置标签的内容
void CCustomMessageBox::setTextInfo(const QString &strInfo)
{
    if(!strInfo.isEmpty())
        m_pLabelInfo->setText(strInfo);
}

void CCustomMessageBox::setTextInfo(const QString &strTitle, const QString &strInfo)
{
    if(strTitle.isEmpty())
        this->setWindowTitle(strTitle);

    if(!strInfo.isEmpty())
        m_pLabelInfo->setText(strInfo);
}

void CCustomMessageBox::setTextInfo(CUSTOM_MESSAGE_TYPE type, const QString &strTitle, const QString &strInfo)
{
    if(strTitle.isEmpty())
        this->setWindowTitle(strTitle);

    if(!strInfo.isEmpty())
        m_pLabelInfo->setText(strInfo);
    else
        return ;

     m_eCustomType = type;
     QString fileName;
     switch(m_eCustomType){
     case CUSTOM_MESSAGE_QUESTION:
         fileName = ":/question";
         break;
     case CUSTOM_MESSAGE_INFORMATION:
         fileName = ":/information";
         break;
     case CUSTOM_MESSAGE_WARNING:
         fileName = ":/warning";
         break;
     case CUSTOM_MESSAGE_CRITICAL:
         fileName = ":/error";
         break;
     default:
         break;
     }
     QPixmap iconPix(fileName);
     m_pLabelIcon->setPixmap(iconPix);
}


void CCustomMessageBox::initialize(const QString &strInfo)
{
    m_pLabelIcon = new QLabel(this);
    QString fileName;
    switch(m_eCustomType){
    case CUSTOM_MESSAGE_QUESTION:
        fileName = ":/question";
        break;
    case CUSTOM_MESSAGE_INFORMATION:
        fileName = ":/information";
        break;
    case CUSTOM_MESSAGE_WARNING:
        fileName = ":/new/images/warnningInfo.png";
        break;
    case CUSTOM_MESSAGE_CRITICAL:
        fileName = ":/error";
        break;
    default:
        break;
    }

    QPixmap iconPix(fileName);
    m_pLabelIcon->setPixmap(iconPix);
    m_pLabelIcon->setFixedSize(64,64);
    m_pLabelIcon->setObjectName("msgBoxIconLabel");

    QFont font;
    font.setBold(true);
    font.setFamily("Consolas");
    font.setPixelSize(FONT_SIZE);

    m_pLabelInfo = new QLabel(strInfo, this);
    m_pLabelInfo->setWordWrap(true);
    m_pLabelInfo->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_pLabelInfo->setFont(font);
    m_pLabelInfo->setObjectName("msgBoxInfoLabel");


    m_pBtnYes = new QToolButton(this);
    m_pBtnYes->setFixedSize(50,30);
    //QPixmap yesPix(":/new/images/confirm.png");
   // m_pBtnYes->setIcon(yesPix);
    //m_pBtnYes->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    //m_pBtnYes->setIconSize(QSize(64,48));
    m_pBtnYes->setFont(font);
    m_pBtnYes->setObjectName("msgBoxYesBtn");
    m_pBtnYes->setFocusPolicy(Qt::NoFocus);

    if(m_eCustomType == CUSTOM_MESSAGE_QUESTION)
        m_pBtnYes->setText(tr("Yes"));
    else
        m_pBtnYes->setText(QString::fromLocal8Bit("确定"));

    connect(m_pBtnYes, SIGNAL(released()), this, SLOT(accept()));

    if(m_eCustomType == CUSTOM_MESSAGE_QUESTION)
    {
        m_pBtnNo = new QToolButton(this);
        QPixmap noPix(":/no_Btn");
        m_pBtnNo->setIcon(noPix);
        m_pBtnNo->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        m_pBtnNo->setIconSize(QSize(60, 40));
        m_pBtnNo->setText(tr("No") );
        m_pBtnNo->setFont(font);
        m_pBtnNo->setObjectName("msgBoxNoBtn");
        m_pBtnNo->setFocusPolicy(Qt::NoFocus);

        connect(m_pBtnNo, SIGNAL(released()), this, SLOT(reject()));
    }

}
//界面布局
void CCustomMessageBox::alignment()
{
    QHBoxLayout *hbLabelLayout = new QHBoxLayout;
    hbLabelLayout->addWidget(m_pLabelIcon);
    hbLabelLayout->addWidget(m_pLabelInfo);
    //hbBtnLayout->addStretch();
    m_pBtnYes->setGeometry(280,115,50,50);
    m_pBtnYes->setParent(this);
   // hbBtnLayout->addStretch();

    //QVBoxLayout *vbLayout = new QVBoxLayout;
    //vbLayout->addLayout(hbLabelLayout);
    //vbLayout->addSpacing(20);
    //vbLayout->addLayout(hbBtnLayout);

    this->setLayout(hbLabelLayout);
}


void CCustomMessageBox::paintEvent(QPaintEvent *event){

       QPainter painter(this);
       QPainterPath pathBack;
       pathBack.setFillRule(Qt::WindingFill);
       pathBack.addRect(QRect(0, 0, this->width(), this->height()));
       painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
       painter.fillPath(pathBack, QBrush(QColor(255, 255, 255)));

       // 绘制窗口上方蓝条;
       QPainterPath pathHead;
       pathHead.setFillRule(Qt::WindingFill);
       pathHead.addRect(QRect(0, 0, this->width(), 2));
       painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
       painter.fillPath(pathHead, QBrush(QColor(15, 151, 255)));
       return QWidget::paintEvent(event);
}
