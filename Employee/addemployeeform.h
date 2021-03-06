#ifndef ADDEMPLOYEEFORM_H
#define ADDEMPLOYEEFORM_H
#include <QWidget>
#include <QWidget>
#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#define MARGIN 8  //四个角的宽度

#include "employeemodel.h"
#include "employeedao.h"
#include "basestation/formtitle.h"

class addEmployeeForm : public QWidget
{
    Q_OBJECT
public:
    explicit addEmployeeForm(QWidget *parent = 0);
    ~addEmployeeForm();
    QFormLayout *formlayout;

    QLineEdit *idEdit;
    QLineEdit *nameEdit;
    QLineEdit *ageEdit;
    QLineEdit *sexEdit;
    QLineEdit *phoneEdit;
    QLineEdit *addressEdit;
    QLineEdit *remarkEdit;

    QPushButton *chk_btn;
    QPushButton *can_btn;
    QGridLayout *gridlayout;
    QHBoxLayout *hor_layout;
    QVBoxLayout *mainlayout;
    QWidget *widget_1;
    QWidget *widget_2;
    QScrollArea *scrollArea;
    FormTitle *title;
    //窗口缩放
    int countFlag(QPoint p,int row);
    void setCursorType(int flag);
    int countRow(QPoint P);
protected:
    void mousePressEvent(QMouseEvent *eve);
    void mouseReleaseEvent(QMouseEvent *eve);
   // void mouseDoubleClickEvent(QMouseEvent *eve);
    void mouseMoveEvent(QMouseEvent *eve);

signals:
    void newEmployeeInfo(Employee &info);
public slots:
    void combine();
private:
    bool isLeftPressed;
    int curPos;
    QPoint pLast;
};

#endif // ADDEMPLOYEEFORM_H
