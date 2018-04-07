#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <QWidget>
#include <qwt_plot.h>
#include <qstringlist.h>

class DistroChartItem;

class Histogram : public QwtPlot
{
    Q_OBJECT

public:
    Histogram(QWidget * = NULL);
    ~Histogram();

    bool data=true;

    int axis1 = QwtPlot::xBottom;
    int axis2 = QwtPlot::yLeft;

    QVector< double > samples;
    QVector< double > samples2;

    void data_change();
    void exportChart();


public Q_SLOTS:
//    void setOrientation( int );
//    void exportChart();

private:
    void populate();

    DistroChartItem *d_barChartItem;
    QStringList d_distros;
};

#endif // HISTOGRAM_H
