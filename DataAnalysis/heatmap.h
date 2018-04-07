#ifndef HEATMAP_H
#define HEATMAP_H

#include <qwt_plot.h>
#include <qwt_plot_spectrogram.h>
#include <qdatetime.h>


class HeatMap: public QwtPlot
{
    Q_OBJECT

public:
    enum ColorMap
    {
        RGBMap,
        IndexMap,
        HueMap,
        AlphaMap
    };

    HeatMap( QWidget * = NULL);

    void exportChart();

    void Data_set();
    void timerEvent( QTimerEvent *e );
    bool data=true;
    double m=5.0;


protected:
//    void timerEvent( QTimerEvent *e );

private:
    QwtPlotSpectrogram *d_spectrogram;

    int d_mapType;
    int d_alpha;
//public:
//    HeatMap(QWidget *parent = 0);
//    ~HeatMap();
};

#endif // HEATMAP_H
