#include "statmodel.h"

StatModel::StatModel(QWidget *parent)
    : QWidget(parent)
{
    pic_Label=new QLabel();



    pic_Label->setScaledContents(true);
    pic_Label->setStyleSheet("background:white;");


    btn=new QPushButton();
    btn->setStyleSheet("background:transparent;");


    text_Label=new QLabel();
    text_Label->setAlignment(Qt::AlignLeft);
    text_Label->setWordWrap(true);

    QVBoxLayout *ver_layout=new QVBoxLayout();
    ver_layout->addWidget(pic_Label);
    ver_layout->addWidget(btn);
    ver_layout->addWidget(text_Label);

    setLayout(ver_layout);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setStyleSheet("font-family:'微软雅黑';"
                  "color:rgb(0,78,161);"
                  "font-weight:fold;"
                  "font-size:13px;");
    btn->setStyleSheet("border-radius:4px;"
                       "border:none;"
                       "width:90px;"
                       "height:25px;"
                       "color:white;"
                       "background:rgb(120,170,220);");
    pic_Label->setStyleSheet("border:1px solid lightblue;");
}

StatModel::~StatModel()
{

}
