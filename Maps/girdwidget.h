#ifndef GIRDWIDGET_H
#define GIRDWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Ui {
class GirdWidget;
}

class GirdWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GirdWidget(QWidget *parent = 0);
    ~GirdWidget();
    QHBoxLayout *h1;
    QWidget *widget1;

protected:
     virtual bool eventFilter(QObject *watched, QEvent *e);
     void paintOnWidget(QWidget *w);
private:
    Ui::GirdWidget *ui;

};

#endif // GIRDWIDGET_H
