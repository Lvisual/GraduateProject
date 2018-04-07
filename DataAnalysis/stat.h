#ifndef STAT_H
#define STAT_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPixmap>

#include "statmodel.h"
#include "widget_heatmap.h"
#include "widget_histogram.h"

class Stat : public QWidget
{
    Q_OBJECT

public:
    QLabel *lab_show;
    QLabel *lab_analysis;

    StatModel *basestation_chart;
    StatModel *worker_chart;
    StatModel *attend_chart;
    StatModel *attend_pie;
    StatModel *worker_heat;
    StatModel *worker_fence;

    Widget_HeatMap *heatmap_people;
    Widget_Histogram *histogram_people;
public:
    Stat(QWidget *parent = 0);
//    ~Stat();
public slots:
//    void show_basestationChart();
    void show_peoplechart();
    void show_peopleheat();
};

#endif // STAT_H
