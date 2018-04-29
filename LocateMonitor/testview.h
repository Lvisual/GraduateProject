#ifndef TESTVIEW_H
#define TESTVIEW_H

#include <QWidget>
#include "Maps/mymapview.h"
class TestView : public QWidget
{
    Q_OBJECT
public:
    explicit TestView(QWidget *parent = 0);

signals:

public slots:
private:
    MyMapView *m_view;
};

#endif // TESTVIEW_H
