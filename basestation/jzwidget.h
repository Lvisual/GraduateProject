#ifndef JZWIDGET_H
#define JZWIDGET_H

#include <QWidget>
#include <QPushButton>
#include"basemodel.h"
#include <QTableView>
#include "basestationform.h"
#include "basestationdao.h"
#include "DaoHang/colordefines.h"
#include "DaoHang/message.h"
#include "DaoHang/navdelegate.h"
#include "DaoHang/naviview.h"
#include "DaoHang/navmodel.h"
#include "DaoHang/dhpushbutton.h"
#include <QStackedWidget>
#include "basetypewidget.h"
#include "selectbaseform.h"
namespace Ui {
class JzWidget;
}

class JzWidget : public QWidget
{
    Q_OBJECT

public:
    explicit JzWidget(QWidget *parent = 0);
    ~JzWidget();
    void setupModel();
private:
    Ui::JzWidget *ui;
public slots:
    void deleteBaseItem();
    void addBaseWin();
    void freshBaseItem();
    void addBaseItem(BaseInfo &info);
    void switchPage();
    void setNav();
    void selectBaseWin();
    void selectBaseItem(int id);
private:
    QPushButton *addBase;
    QPushButton *deleteBase;
    QPushButton *freshBase;
    QPushButton *selectBase;
    BaseModel   *baseModel;
    QTableView  *baseTable;
    QPushButton *nextPage;
    QPushButton *prePage;
    QPushButton *firstPage;
    QPushButton *lastPage;   
    BaseStationDao *baseStationdao;
    BaseStationForm *addWin;
    SelectBaseForm *selectWin;

    QStackedWidget *stack;
    NaviView * m_naviView;
    DHPushButton * m_navBtn;
    baseTypeWidget *m_baseType;
    int m_status;
};

#endif // JZWIDGET_H
