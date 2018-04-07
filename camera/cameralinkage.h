#ifndef CAMERALINKAGE_H
#define CAMERALINKAGE_H

#include <QWidget>
#include <QPushButton>
#include <QListView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "DaoHang/colordefines.h"
#include "DaoHang/message.h"
#include "DaoHang/navdelegate.h"
#include "DaoHang/naviview.h"
#include "DaoHang/navmodel.h"
#include "DaoHang/dhpushbutton.h"
#include <QLabel>

namespace Ui {
class CameraLinkage;
}

class CameraLinkage : public QWidget
{
    Q_OBJECT

public:
    explicit CameraLinkage(QWidget *parent = 0);
    ~CameraLinkage();
public slots:
    void setscenexlabelvalue(double,double);

private:
    Ui::CameraLinkage *ui;
    QPushButton *xuanze;
    QPushButton *shanchu;
    QPushButton *tianjia;
    QPushButton *firstpage;
    QPushButton *nextpage;
    QPushButton *prepage;
    QPushButton *lastpage;
    QLabel *Xzuobiao;
    QLabel *Yzuobiao;
    QLabel *Xvalue;
    QLabel *Yvalue;

    NaviView * m_naviView;
};

#endif // CAMERALINKAGE_H
