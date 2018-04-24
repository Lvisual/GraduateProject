#ifndef LOMOWIDGET_H
#define LOMOWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QGraphicsView>
#include <QStandardItemModel>
#include <QToolButton>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QLineEdit>
#include <QTableView>
#include <QTabWidget>
#include <QLabel>
#include <QSlider>

#include <QWheelEvent>
#include <QMouseEvent>

#include "Maps/drawscene.h"
#include "Maps/drawobj.h"
#include "Maps/drawtool.h"
#include "ElecFencing/elecfencingview.h"
#include "ElecFencing/historychoice.h"
#include "ElecFencing/myxml.h"
#include "Maps/route.h"

#include "DaoHang/colordefines.h"
#include "DaoHang/message.h"
#include "DaoHang/navdelegate.h"
#include "DaoHang/naviview.h"
#include "DaoHang/navmodel.h"
#include "DaoHang/dhpushbutton.h"


namespace Ui {
class LoMoWidget;
}

class LoMoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoMoWidget(QWidget *parent = 0);
    ~LoMoWidget();
     void openFileMap(QString s);

//    void wheelEvent(QWheelEvent*event);
//protected:
//    void mouseMoveEvent(QMouseEvent *event);
public slots:

    void setxlabelvalue(double);
    void setylabelvalue(double);
    void setbililabelvalue(double);
    void jiazai();
    void showHistoryWin();
    void showHistoryRoute(HistoryInfo);
    void loadScene1(bool);
signals:
   // void stateChange();
private:
    Ui::LoMoWidget *ui;
    ElecFencingView *view;

    QToolButton *toolbutton1;
    //QToolButton *toolbutton2;
    QToolButton *toolbutton3;
    QToolButton *toolbutton4;

    QVector<QPoint> m_access1;
    QVector<QPoint> m_access2;
    MyXml m_xml1;
    MyXml m_xml2;

    QPushButton *pushbutton1;

    NaviView * m_naviView;

    QTabWidget *tabwidget;
    QLabel *locatelabel;
    QLabel *Xlabel;
    QLabel *Ylabel;
    HistoryChoice *m_historyChoice;

    QLabel *blilixiangsu;
    QLabel *bilichi1;
    QLabel *bilivalue;

    QLabel *tablelabel;

    QRadioButton *radio1;
    QRadioButton *radio2;
    QRadioButton *radio3;
    QRadioButton *radio4;

    QCheckBox *supersets;
    QLabel *filterbeginnum;
    QLineEdit *filternum;
    QLabel *pointfrequency;
    QLineEdit *pointFre;

    QToolButton *savebegin;
    QToolButton *saveend;
    QToolButton *openfileindex;

    QSlider *hslider;
    QToolButton *scan;
    QLineEdit *scanedit;
    QLabel *playerback;
    QCheckBox *roundplay;
    QLabel *null;
    QToolButton *playbegin;
    QToolButton *playend;

    DrawScene *scene1;

    QStandardItemModel *model;

private slots:
    void supersetvisble();

};

#endif // LOMOWIDGET_H
