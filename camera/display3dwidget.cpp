#include <QtGui>
#include "display3dwidget.h"
#include "glwidget.h"

Display3dWidget::Display3dWidget()
: p_GLWidget(NULL)
{
    p_GLWidget= new GLWidget(this);
    V_Layout_2 = new QVBoxLayout();
    V_Layout_2->addWidget(p_GLWidget);
    button_1 = new QToolButton();
    button_2 = new QToolButton();
    button_3 = new QToolButton();
    button_1->setText(QStringLiteral("导航"));
    button_2->setText(QStringLiteral("俯视"));
    button_3->setText(QStringLiteral("电子围栏"));
    V_Layout_1 = new QVBoxLayout();
    V_Layout_1->setSpacing(10);

    button_1->setStyleSheet("width:80px;height:25px;");
    button_2->setStyleSheet("width:80px;height:25px;");
    button_3->setStyleSheet("width:80px;height:25px;");

    V_Layout_1->addWidget(button_1);
    V_Layout_1->addWidget(button_2);
    V_Layout_1->addWidget(button_3);
    V_Layout_1->addStretch();
    H_Layout = new QHBoxLayout(this);
    H_Layout->addLayout(V_Layout_1);
    H_Layout->addLayout(V_Layout_2);
    this->setLayout(H_Layout);
    connect(button_1,SIGNAL(clicked(bool)),p_GLWidget,SLOT(trace()));
    connect(button_2,SIGNAL(clicked(bool)),p_GLWidget,SLOT(isoView1()));
    connect(button_3,SIGNAL(clicked(bool)),p_GLWidget,SLOT(makePolygon()));
    L_warning = new QLabel();
    L_warning->setText("您已进入电子围栏");
    QVBoxLayout *layout_warning = new QVBoxLayout();
    layout_warning->addWidget(L_warning);
    D_warning = new QDialog();
    D_warning->setLayout(layout_warning);
    coorX = new QLabel();
    coorX->setText(QStringLiteral("X坐标:"));
    coorY = new QLabel();
    coorY->setText(QStringLiteral("Y坐标:"));
    connect(p_GLWidget,SIGNAL(fenceWarning(bool)),this,SLOT(fWanring(bool)));
    connect(p_GLWidget,SIGNAL(coordinateMod(double,double)),this,SIGNAL(displayCoor(double,double)));
    connect(p_GLWidget,SIGNAL(isFence(bool)),p_GLWidget,SLOT(changeFlag(bool)));
}

void Display3dWidget::fWanring(bool tf)
{
    if(tf)
        D_warning->show();
    else
        D_warning->close();
}


