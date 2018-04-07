#ifndef WIDGET_HISTOGRAM_H
#define WIDGET_HISTOGRAM_H

#include <QWidget>
#include <QApplication>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QPushButton>

#include "histogram.h"
#include "basestation/formtitle.h"


class Widget_Histogram : public QWidget
{
    Q_OBJECT
public:
    explicit Widget_Histogram(QWidget *parent=0);
    ~Widget_Histogram();

    Histogram *histogram;
    Histogram *histogram2;
    FormTitle *title;
    QWidget *widget2;
    QWidget *widget_area;
    QLabel *label_area;
    QComboBox *combobox_area;
    QPushButton *button_export;

public slots:
    void IndexChange();
    void pic_export();

};

#endif // WIDGET_HISTOGRAM_H
