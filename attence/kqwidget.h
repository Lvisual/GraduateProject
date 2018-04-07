#ifndef KQWIDGET_H
#define KQWIDGET_H

#include <QWidget>
#include <QWidget>
#include "signinwidget.h"
#include "personaldailyreport.h"
#include "personalweekreport.h"
#include "attencerecord.h"
#include "signinreport.h"
#include "DaoHang/colordefines.h"
#include "DaoHang/message.h"
#include "DaoHang/navdelegate.h"
#include "DaoHang/naviview.h"
#include "DaoHang/navmodel.h"
#include "DaoHang/dhpushbutton.h"
#include <QStackedWidget>


namespace Ui {
class KqWidget;
}

class KqWidget : public QWidget
{
    Q_OBJECT

public:
    explicit KqWidget(QWidget *parent = 0);
    ~KqWidget();

public slots:
    void switchPage();
    void setNav();

    void showsigninreport(int);
    void showsigninwidget();
private:
    Ui::KqWidget *ui;

    SignInWidget *m_signin;
    PersonalDailyReport *m_personalDaily;
    PersonalWeekReport *m_personalWeekly;
    AttenceRecord *m_attencereport;
    SignInReport *m_signinreport;

    QStackedWidget *m_stackedwidget;
    //QAction *openAct;

    QStackedWidget *stack;
    NaviView * m_naviView;
    DHPushButton * m_navBtn;
    int m_status;

    QString setbeizhuvalue();


};

#endif // KQWIDGET_H
