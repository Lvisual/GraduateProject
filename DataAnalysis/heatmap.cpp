#include "heatmap.h"


#include <qnumeric.h>
#include <qwt_color_map.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_scale_widget.h>
#include <qwt_scale_draw.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_renderer.h>
#include <qdebug.h>

/***********************坐标以及象限数据**************************/

class SpectrogramData: public QwtRasterData  //展示密度的栅格数据
{
public:
    SpectrogramData()
    {
//        setInterval( Qt::XAxis, QwtInterval( -1.5, 1.5 ) );
//        setInterval( Qt::YAxis, QwtInterval( -1.5, 1.5 ) );
        setInterval( Qt::XAxis, QwtInterval( 0, 300 ) );
        setInterval( Qt::YAxis, QwtInterval( 0, 300 ) );
        setInterval( Qt::ZAxis, QwtInterval( 0.0, 100.0 ) );
    }
    double h;
//    virtual double value( double x, double y ) const
    double value( double x, double y ) const
    {
        double c = h;
        double a=x-150;
        double b=y-150;
        const double v1 = a * a + ( b - c ) * ( b + c );
        const double v2 = a * ( b + c ) + a * ( b + c );
        return 100000000 / ( v1 * v1 + v2 * v2 );

    }
};

class SpectrogramData2: public QwtRasterData  //展示密度的栅格数据
{
public:
    SpectrogramData2()
    {
//        setInterval( Qt::XAxis, QwtInterval( -1.5, 1.5 ) );
//        setInterval( Qt::YAxis, QwtInterval( -1.5, 1.5 ) );

        setInterval( Qt::XAxis, QwtInterval( 0, 300 ) );
        setInterval( Qt::YAxis, QwtInterval( 0, 300 ) );
        setInterval( Qt::ZAxis, QwtInterval( 0.0, 10.0 ) );
    }

    double h2;
//    virtual double value( double x, double y ) const
    virtual double value( double x, double y ) const
    {
         double c = h2;
        double a=x-130;
        double b=y-130;
        const double v1 = b * b + ( a - c ) * ( a + c );
        const double v2 = b * ( a + c ) + b * ( a + c );
        return 10000000 / ( v1 * v1 + v2 * v2 );

    }
};

/***********************Z轴坐标颜色数据设置**************************/

class LinearColorMapRGB: public QwtLinearColorMap
{
public:
    LinearColorMapRGB():
        QwtLinearColorMap( Qt::darkCyan, Qt::red, QwtColorMap::RGB )
    {
        addColorStop( 0.1, Qt::cyan );
        addColorStop( 0.6, Qt::green );
        addColorStop( 0.95, Qt::yellow );
    }
};

HeatMap::HeatMap(QWidget *parent)
    : QwtPlot(parent),
      d_alpha(255)
{
    d_spectrogram = new QwtPlotSpectrogram();
    d_spectrogram->setRenderThreadCount( 0 ); // use system specific thread count
    d_spectrogram->setCachePolicy( QwtPlotRasterItem::PaintCache );

    QList<double> contourLevels;
    for ( double level = 0.5; level < 10.0; level += 1.0 )
        contourLevels += level;
    d_spectrogram->setContourLevels( contourLevels );

    Data_set();
    (void)startTimer(3000);  //设置定时器

    QwtScaleWidget *axis = axisWidget( QwtPlot::yRight );
    const QwtInterval zInterval = d_spectrogram->data()->interval( Qt::ZAxis );

    d_spectrogram->setColorMap( new LinearColorMapRGB() );
    axis->setColorMap( zInterval, new LinearColorMapRGB() );

/*******************************设置右边Z轴*************************************/
    QwtScaleWidget *rightAxis = axisWidget( QwtPlot::yRight );
    rightAxis->setTitle( "人/百平方米" );
    rightAxis->setColorBarEnabled( true );

    setAxisScale( QwtPlot::yRight, zInterval.minValue(), zInterval.maxValue() );
    enableAxis( QwtPlot::yRight );

    plotLayout()->setAlignCanvasToScales( true );

//    setColorMap( HeatMap::RGBMap );


    // Avoid jumping when labels with more/less digits
    // appear/disappear when scrolling vertically

    const QFontMetrics fm( axisWidget( QwtPlot::yLeft )->font() );
    QwtScaleDraw *sd = axisScaleDraw( QwtPlot::yLeft );
    sd->setMinimumExtent( fm.width( "100.00" ) );

    d_spectrogram->setDisplayMode( QwtPlotSpectrogram::ImageMode, true );
    d_spectrogram->setDefaultContourPen(
        true ? QPen( Qt::black, 0 ) : QPen( Qt::NoPen ) );


}

void HeatMap::exportChart()
{
    QwtPlotRenderer renderer;
    renderer.exportTo( this, "heatmap.pdf" );
}

void HeatMap::Data_set()
{
    if(data==true)
    {
        d_spectrogram->detach();
//        d_spectrogram->setData( new SpectrogramData() );
        SpectrogramData *data_spect=new SpectrogramData();
        data_spect->h=m;
        d_spectrogram->setData(data_spect);
        d_spectrogram->attach( this );
    }
    else
    {
        d_spectrogram->detach();
//        d_spectrogram->setData( new SpectrogramData2() );
        SpectrogramData2 *data_spect=new SpectrogramData2();
        data_spect->h2=m;
        d_spectrogram->setData(data_spect);
        d_spectrogram->attach( this );
    }
    replot();

}

void HeatMap::timerEvent(QTimerEvent *e)
{
//    d_spectrogram->detach();
    if(data==true)
    {
        SpectrogramData *data_spect=new SpectrogramData();
        data_spect->h=m;
        d_spectrogram->setData(data_spect);
        d_spectrogram->attach( this );
    }
    else
    {
        SpectrogramData2 *data_spect=new SpectrogramData2();
        data_spect->h2=m;
        d_spectrogram->setData(data_spect);
        d_spectrogram->attach( this );
    }
    m=m+5;

    replot();
}


//HeatMap::~HeatMap()
//{

//}
