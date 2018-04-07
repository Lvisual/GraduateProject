#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>

namespace Ui {
class contentwidget;
}

class contentwidget : public QWidget
{
    Q_OBJECT

public:
    explicit contentwidget(QWidget *parent = 0);
    ~contentwidget();

private:
    Ui::contentwidget *ui;
    QLabel *HEULogo;
    QLabel *welcome;
    QLabel *version;
    QLabel *developer;
    QLabel *copyright;
};

#endif // CONTENTWIDGET_H
