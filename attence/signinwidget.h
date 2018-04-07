#ifndef SIGNINWIDGET_H
#define SIGNINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QToolButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "signindao.h"
#include "signinmodel.h"
#include <QTime>

namespace Ui {
class SignInWidget;
}

class SignInWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SignInWidget(QWidget *parent = 0);
    ~SignInWidget();

    void UpDateUI();

public slots:

    void setbeizhuvalue();
    void combine();
    void addSignin(SignIn&info);
    void sendIndex();
signals:

    void turntoreport(int i);
    void newsigninInfo(SignIn &info);



private:

    Ui::SignInWidget *ui;

    QLabel *m_employeeID;
    QLineEdit *emplyeeID;
    QLabel *m_department;
    QLineEdit *department;
    QLabel *m_sex;
    QLineEdit *sex;
    QLabel *m_signdate;
    QLineEdit *signdate;
    QLabel *m_signtime;
    QLineEdit *signtime;
    QLabel *m_photo;
    QLineEdit *m_name;
    QLabel *m_weekday;

    QLabel *m_beizhu;
    QLineEdit *beizhu;

    QLabel *m_words;
    QLineEdit *words;
    QToolButton *sign_in;

    SignInDao m_signinDao;

    bool isLeftPressed;
    int curPos;

};

#endif // SIGNINWIDGET_H
