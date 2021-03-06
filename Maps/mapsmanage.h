#ifndef MAPSMANAGE_H
#define MAPSMANAGE_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <QAction>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "mapdrawing.h"
#include "ElecFencing/elecfencingview.h"
namespace Ui {
class MapsManage;
}

class MapsManage : public QWidget
{
    Q_OBJECT

public:
    explicit MapsManage(QWidget *parent = 0);
    ~MapsManage();
    void setupModel();


public slots:
    void drawmap_show();
    void showMap();
    void clearMap();
private:
    Ui::MapsManage *ui;

    QPushButton *checkmap;
    QPushButton *createmap;
    QPushButton *freshmap;

    QPushButton *biaogeFP;
    QPushButton *biaogeNP;
    QPushButton *biaogePP;
    QPushButton *biaogeLP;
    QStandardItemModel *model;
    ElecFencingView *m_view;
    DrawScene *m_scene;
};

#endif // MAPSMANAGE_H
