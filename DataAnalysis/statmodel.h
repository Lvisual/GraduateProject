#ifndef STATMODEL_H
#define STATMODEL_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QString>

class StatModel : public QWidget
{
    Q_OBJECT

public:
    QLabel *pic_Label;
    QLabel *text_Label;

    QPushButton *btn;
    QTextEdit *text;
    QString *str_pic;

    QString str_remark;


public:
    StatModel(QWidget *parent=0);
    ~StatModel();
};

#endif // STATMODEL_H
