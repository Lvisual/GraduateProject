#include "testview.h"

TestView::TestView(QWidget *parent) : QWidget(parent)
{

    m_view = new MyMapView();
    m_view->show();
}
