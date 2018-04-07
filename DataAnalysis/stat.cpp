#include "stat.h"

Stat::Stat(QWidget *parent):
      QWidget(parent)
{
/****************************实时状态********************************/
    QGridLayout *layout_show = new QGridLayout();
    lab_show = new QLabel();
    lab_show->setText(QStringLiteral("实时状态展示"));
    lab_show->setStyleSheet("font-family:'微软雅黑';"
                            "color:rgb(0,78,161);"
                            "font-weight:fold;"
                            "font-size:15px;");

    basestation_chart = new StatModel(this);
    QPixmap pixmap_base(":/images/zf.jpg");
    basestation_chart->pic_Label->setPixmap(pixmap_base);
    basestation_chart->pic_Label->setFixedSize(215,137);
    basestation_chart->btn->setText(QStringLiteral("人员分布"));
    basestation_chart->text_Label->setText(QStringLiteral("以区域为单位展示人员分布情况"));

    worker_chart = new StatModel(this);
    QPixmap pixmap_work_chart(":/images/zhexian.jpg");
    worker_chart->pic_Label->setPixmap(pixmap_work_chart);
    worker_chart->pic_Label->setFixedSize(215,137);
    worker_chart->btn->setText(QStringLiteral("基站分布"));
    worker_chart->text_Label->setText(QStringLiteral("以折线图实时展示主要区域的基站分布情况"));

    worker_heat = new StatModel(this);

    worker_heat->btn->setText(QStringLiteral("人员密度"));
    QPixmap pixmap_work_heat(":/images/heat_2.jpg");
    worker_heat->pic_Label->setPixmap(pixmap_work_heat);
    worker_heat->pic_Label->setFixedSize(215,137);
    worker_heat->text_Label->setText(QStringLiteral("以热力图实时展示人员密度分布情况"));

    attend_chart = new StatModel(this);
    QPixmap pixmap_attend_chart(":/images/zhexian_1.png");
    attend_chart->pic_Label->setPixmap(pixmap_attend_chart);
    attend_chart->pic_Label->setFixedSize(215,137);
    attend_chart->btn->setText(QStringLiteral("累计人次"));
    attend_chart->text_Label->setText(QStringLiteral("以区域为单位统计分析各个区域近一周内每天的人流量"));

    layout_show->addWidget(lab_show,0,0,1,3);
    layout_show->addWidget(basestation_chart,1,0,1,1);
    layout_show->addWidget(worker_chart,1,1,1,1);
    layout_show->addWidget(worker_heat,1,2,1,1);

/********************************统计分析**************************************/
    QGridLayout *layout_analysis = new QGridLayout();
    lab_analysis = new QLabel();
    lab_analysis->setText(QStringLiteral("数据统计分析"));
    lab_analysis->setStyleSheet("font-family:'微软雅黑';"
                                "color:rgb(0,78,161);"
                                "font-weight:fold;"
                                "font-size:15px;");

    attend_pie = new StatModel(this);
    QPixmap pixmap_attend_pie(":/images/pie_1.jpg");
    attend_pie->pic_Label->setPixmap(pixmap_attend_pie);
    attend_pie->pic_Label->setFixedSize(215,137);
    attend_pie->btn->setText(QStringLiteral("人员考勤"));
    attend_pie->text_Label->setText(QStringLiteral("以饼状图统计分析各个部门人员考勤状况"));

    worker_fence = new StatModel(this);
    QPixmap pixmap_worker_fence(":/images/zhifang_1.jpg");
    worker_fence->pic_Label->setPixmap(pixmap_worker_fence);
    worker_fence->pic_Label->setFixedSize(215,137);
    worker_fence->btn->setText(QStringLiteral("电子围栏"));
    worker_fence->text_Label->setText(QStringLiteral("统计一段时间内进入电子围栏的人数以及每个人进入电子围栏的次数"));

    layout_analysis->addWidget(lab_analysis,0,0,1,3);
    layout_analysis->addWidget(attend_chart,1,0,1,1);
    layout_analysis->addWidget(attend_pie,1,1,1,1);
    layout_analysis->addWidget(worker_fence,1,2,1,1);

    QVBoxLayout *ver_layout = new QVBoxLayout();
    ver_layout->addLayout(layout_show);
    ver_layout->addLayout(layout_analysis);

    setLayout(ver_layout);

    setStyleSheet("background:white;");

    connect(worker_heat->btn,SIGNAL(clicked()),this,SLOT(show_peopleheat()));
    connect(basestation_chart->btn,SIGNAL(clicked()),this,SLOT(show_peoplechart()));
}


void Stat::show_peopleheat()
{
    heatmap_people = new Widget_HeatMap();
    heatmap_people->show();
}
void Stat::show_peoplechart()
{
    histogram_people = new Widget_Histogram();
    histogram_people->show();
}
