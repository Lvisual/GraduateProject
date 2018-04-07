#include "histogram.h"

#include <qwt_plot_renderer.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_barchart.h>
#include <qwt_column_symbol.h>
#include <qwt_plot_layout.h>
#include <qwt_legend.h>
#include <qwt_scale_draw.h>

#include <QDebug>

class DistroScaleDraw: public QwtScaleDraw
{
public:
    DistroScaleDraw( const QStringList &labels ):
        d_labels( labels )
    {
        setTickLength( QwtScaleDiv::MinorTick, 0 );
        setTickLength( QwtScaleDiv::MediumTick, 0 );
        setTickLength( QwtScaleDiv::MajorTick, 2 );

        enableComponent( QwtScaleDraw::Backbone, false );

        setLabelRotation( -60.0 );

        setLabelAlignment( Qt::AlignLeft | Qt::AlignVCenter );
    }

    virtual QwtText label( double value ) const
    {
        QwtText lbl;

        const int index = qRound( value );//四舍五入
        if ( index >= 0 && index < d_labels.size() )
        {
            lbl = d_labels[ index ];
        }

        return lbl;
    }

private:
    const QStringList d_labels;
};

class DistroChartItem: public QwtPlotBarChart
{
public:
    DistroChartItem():
        QwtPlotBarChart( "人数" )
    {
//        setLegendMode( QwtPlotBarChart::LegendBarTitles );
        setLegendIconSize( QSize( 10, 14 ) );
        setLayoutPolicy( AutoAdjustSamples );
        setLayoutHint( 4.0 ); // minimum width for a single bar
        setSpacing( 10 ); // spacing between bars
    }

    void addDistro( const QString &distro, const QColor &color )
    {
        d_colors += color;
        d_distros += distro;
        itemChanged();
    }

    virtual QwtColumnSymbol *specialSymbol(
        int index, const QPointF& ) const
    {
        // we want to have individual colors for each bar

        QwtColumnSymbol *symbol = new QwtColumnSymbol( QwtColumnSymbol::Box );
        symbol->setLineWidth( 2 );
        symbol->setFrameStyle( QwtColumnSymbol::Raised );

        QColor c( Qt::white );
        if ( index >= 0 && index < d_colors.size() )
            c = d_colors[ index ];

        symbol->setPalette( c );


        return symbol;
    }

    virtual QwtText barTitle( int sampleIndex ) const
    {
        QwtText title;
        if ( sampleIndex >= 0 && sampleIndex < d_distros.size() )
            title = d_distros[ sampleIndex ];

        return title;
    }

private:
    QList<QColor> d_colors;
    QList<QString> d_distros;


};



Histogram::Histogram(QWidget *parent)
    : QwtPlot(parent)
{
    setAutoFillBackground( true );
    setPalette( QColor( "white" ) );


    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setLineWidth( 0 );
    canvas->setFrameStyle( QFrame::Box | QFrame::Sunken );
    canvas->setBorderRadius( 0 );

    QPalette canvasPalette( QColor( "white" ) );
    canvasPalette.setColor( QPalette::Foreground, QColor( "Indigo" ) );
    canvas->setPalette( canvasPalette );

    setCanvas( canvas );

    d_barChartItem = new DistroChartItem();



    data_change();
    setAutoReplot( false );
    setAxisTitle( axis1, "房间号" );
    setAxisMaxMinor( axis1, 3 );
    setAxisTitle( axis2, "人数" );
    setAxisMaxMinor( axis2, 3 );

    QwtScaleDraw *scaleDraw = new QwtScaleDraw();
    scaleDraw->setTickLength( QwtScaleDiv::MediumTick, 4 );
    setAxisScaleDraw( axis2, scaleDraw );

    plotLayout()->setCanvasMargin( 0 );

}



Histogram::~Histogram()
{

}

void Histogram::data_change()
{
    const struct
    {
        const char *distro;
        const int hits;
        QColor color;
    } pageHits[] =
    {
        { "101", 5, QColor( "DodgerBlue" ) },
        { "102", 13, QColor( "#d70751" ) },
        { "103", 16, QColor( "SteelBlue" ) },
        { "104", 13, QColor( "Indigo" ) },
        { "105", 3, QColor( 183, 255, 183 ) },
        { "106", 10, QColor( 115, 186, 37 ) },
        { "107", 12, QColor( "LightSkyBlue" ) },
        { "108", 7, QColor( "FireBrick" ) }

    };

    const struct
    {
        const char *distro;
        const int hits;
        QColor color;
    } pageHits2[] =
    {
        { "201", 3, QColor( "DodgerBlue" ) },
        { "202", 7, QColor( "#d70751" ) },
        { "203", 8, QColor( "SteelBlue" ) },
        { "204", 5, QColor( "Indigo" ) },
        { "205", 4, QColor( 183, 255, 183 ) },
        { "206", 16, QColor( 115, 186, 37 ) },
        { "207", 10, QColor( "LightSkyBlue" ) },
        { "208", 6, QColor( "FireBrick" ) }

    };

    if(data==true)
    {
        d_barChartItem->detach();
        d_distros.clear();
        samples.clear();
        for ( uint i = 0; i < sizeof( pageHits ) / sizeof( pageHits[ 0 ] ); i++ )
        {
            d_distros += pageHits[ i ].distro;
            samples += pageHits[ i ].hits;

            d_barChartItem->addDistro(
                pageHits[ i ].distro, pageHits[ i ].color );
        }
        d_barChartItem->setSamples( samples );
        setAxisScaleDraw( axis1, new DistroScaleDraw( d_distros ) );
        d_barChartItem->setLegendMode(QwtPlotBarChart::LegendBarTitles);
//        insertLegend( new QwtLegend() );
        d_barChartItem->attach( this );

        replot();

    }
    else
    {
        d_barChartItem->detach();

        d_distros.clear();
        samples2.clear();

        for ( uint i = 0; i < sizeof( pageHits2 ) / sizeof( pageHits2[ 0 ] ); i++ )
        {
            d_distros += pageHits2[ i ].distro;
            samples2 += pageHits2[ i ].hits;

            d_barChartItem->addDistro(
                pageHits2[ i ].distro, pageHits2[ i ].color );
        }

        d_barChartItem->setSamples( samples2 );
        setAxisScaleDraw( axis1, new DistroScaleDraw( d_distros ) );

        d_barChartItem->setLegendMode(QwtPlotBarChart::LegendBarTitles);
//        insertLegend( new QwtLegend() );
        d_barChartItem->attach( this );

        replot();
    }

}

void Histogram::exportChart()
{
    QwtPlotRenderer renderer;
    renderer.exportTo( this, "barchart.pdf" );
}
