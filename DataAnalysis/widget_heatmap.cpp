#include "widget_heatmap.h"

#include <QApplication>

Widget_HeatMap::Widget_HeatMap(QWidget *parent):
                QWidget(parent)
{
    this->setFixedSize(650,600);

    setWindowFlags(Qt::FramelessWindowHint);


    title = new FormTitle(this,QStringLiteral("人员分布热力图"));
    title->setFixedHeight(40);

    label_area = new QLabel();
    label_area->setText(QStringLiteral("区域选择:"));
    label_area->setStyleSheet("font-size:15px;"
                              "color:white");


    combobox_area = new QComboBox();
    combobox_area->setObjectName("combobox_area");
//    combobox_area->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    combobox_area->addItem("21A_1st");
    combobox_area->addItem("21A_2nd");
    combobox_area->addItem("21A_3rd");
    combobox_area->addItem("21A_4th");
    combobox_area->addItem("21A_5th");
    combobox_area->insertSeparator(0);
    combobox_area->insertSeparator(1);
    combobox_area->insertSeparator(2);
    combobox_area->insertSeparator(3);
    combobox_area->insertSeparator(4);

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


    heatMap = new HeatMap();

    QVBoxLayout *ver_layout=new QVBoxLayout(this);

    QVBoxLayout *heat_layout = new QVBoxLayout();

    heat_layout->addWidget(heatMap);

    widget1 = new QWidget();
    widget1->setLayout(heat_layout);
    widget1->setObjectName("widget1");

    ver_layout->addWidget(title);
    ver_layout->addWidget(widget_area);
    ver_layout->addWidget(widget1);
    ver_layout->setSpacing(0);
    ver_layout->setContentsMargins(0,0,0,0);

    setLayout(ver_layout);

    connect(title,SIGNAL(showMin()),this,SLOT(showMinimized()));
    connect(title,SIGNAL(closeWidget()),this,SLOT(close()));

    connect(button_export,SIGNAL(clicked()),this,SLOT(pic_export()));
    connect(combobox_area,SIGNAL(currentIndexChanged(int)),this,SLOT(data_change()));



}

void Widget_HeatMap::pic_export()
{
    heatMap->exportChart();
}

void Widget_HeatMap::data_change()
{
    if(heatMap->data==true)
    {
        heatMap->data=false;
    }
    else
    {
        heatMap->data=true;
    }
    heatMap->Data_set();
}

Widget_HeatMap::~Widget_HeatMap()
{

}
