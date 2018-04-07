#include "widget_histogram.h"
#include <QApplication>
#include <QDebug>

Widget_Histogram::Widget_Histogram(QWidget *parent):
    QWidget(parent)
{
    this->setFixedSize(650,680);

    setWindowFlags(Qt::FramelessWindowHint);


    title = new FormTitle(this,QStringLiteral("人员分布直方图"));
    title->setFixedHeight(40);

    histogram = new Histogram();

    label_area = new QLabel();
    label_area->setText(QStringLiteral("区域选择:"));
    label_area->setStyleSheet("font-size:15px;"
                              "color:white");

    combobox_area = new QComboBox();
    combobox_area->setObjectName("combobox_area");
//    combobox_area->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    combobox_area->addItem("21A_1st");
    combobox_area->addItem("21A_2nd");

    combobox_area->insertSeparator(0);
    combobox_area->insertSeparator(1);

    button_export = new QPushButton();
    button_export->setText(QStringLiteral("导出"));

    QHBoxLayout *layout_area = new QHBoxLayout();
    layout_area->addWidget(label_area);
    layout_area->addWidget(combobox_area);
    layout_area->addWidget(button_export);
    layout_area->setSpacing(8);

    layout_area->setAlignment(Qt::AlignVCenter);
    layout_area->setAlignment(Qt::AlignLeft);

    widget_area = new QWidget();
    widget_area->setLayout(layout_area);
    widget_area->setFixedHeight(40);
    widget_area->setStyleSheet("background:rgb(224, 238, 255);");

    QVBoxLayout *ver_layout=new QVBoxLayout(this);

    QVBoxLayout *histogram_layout = new QVBoxLayout();

    histogram_layout->addWidget(histogram);
    histogram_layout->setContentsMargins(10,10,50,30);

    widget2 = new QWidget();
    widget2->setLayout(histogram_layout);
    widget2->setObjectName("widget2");

    ver_layout->addWidget(title);
    ver_layout->addWidget(widget_area);
    ver_layout->addWidget(widget2);
    ver_layout->setSpacing(0);
    ver_layout->setContentsMargins(0,0,0,0);

    setLayout(ver_layout);

    connect(title,SIGNAL(showMin()),this,SLOT(showMinimized()));
    connect(title,SIGNAL(closeWidget()),this,SLOT(close()));

    connect(combobox_area,SIGNAL(currentIndexChanged(int)),this,SLOT(IndexChange()));
    connect(button_export,SIGNAL(clicked()),this,SLOT(pic_export()));
}

Widget_Histogram::~Widget_Histogram()
{

}

void Widget_Histogram::IndexChange()
{

    if(histogram->data==true)
    {
        histogram->data=false;
    }
    else
    {
        histogram->data=true;

    }
    histogram->data_change();
}

void Widget_Histogram::pic_export()
{
    histogram->exportChart();
}
