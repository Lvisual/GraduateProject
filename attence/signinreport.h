#ifndef SIGNINREPORT_H
#define SIGNINREPORT_H

#include <QWidget>
#include <QTableView>
#include <QToolButton>
#include <QLineEdit>
#include "signindao.h"
#include "signinmodel.h"

namespace Ui {
class SignInReport;
}

class SignInReport : public QWidget
{
    Q_OBJECT

public:
    explicit SignInReport(QWidget *parent = 0);
    ~SignInReport();

    void setupModel();
    void freshreport();

signals:

    backtosignup();

public slots:
    //void addWin();
   //void selectWin();
   // void addEmployee(Employee&info);
   // void deleteEmployee();
    void freshsigninreport();
   // void selectsignin(int id);

private:

    Ui::SignInReport *ui;
    QTableView *tableview;

    QToolButton *fresh;
    QToolButton *search;
    QToolButton *back;
    QLineEdit *searchbyID;

    SignInModel *m_model;
    SignInDao m_signinDao;

};

#endif // SIGNINREPORT_H
