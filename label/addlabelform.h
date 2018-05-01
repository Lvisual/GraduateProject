#ifndef ADDLABELFORM_H
#define ADDLABELFORM_H

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
#include "basestation/formtitle.h"
#include"labelmodel.h"
#define MARGIN 8  //四个角的宽度
class addLabelForm : public QWidget
{
    Q_OBJECT
public:
    explicit addLabelForm(QWidget *parent = 0);
    ~addLabelForm();
    QFormLayout *formlayout;

    QLineEdit *labelIdEdit;
    QLineEdit *labelNameEdit;
    QLineEdit *employeeIdEdit;
    QLineEdit *chargeEdit;
    QLineEdit *stateEdit;
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
    void newLabelInfo(Label &info);
public slots:
    void combine();
private:
    bool isLeftPressed;
    int curPos;
    QPoint pLast;
};

#endif // ADDLABELFORM_H
