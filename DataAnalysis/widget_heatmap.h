#ifndef WIDGET_HEATMAP_H
#define WIDGET_HEATMAP_H

#include <QWidget>
#include <QApplication>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QPushButton>

#include "heatmap.h"
#include "basestation/formtitle.h"


class Widget_HeatMap : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_HeatMap(QWidget *parent=0);
    ~Widget_HeatMap();

    HeatMap *heatMap;
    FormTitle *title;
    QWidget *widget1;
    QWidget *widget_area;
    QLabel *label_area;
    QComboBox *combobox_area;
    QPushButton *button_export;

public slots:
    void pic_export();
    void data_change();

};

#endif // WIDGET_HEATMAP_H
