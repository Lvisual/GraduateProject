#ifndef LABELDETAIL_H
#define LABELDETAIL_H
#include <QWidget>
#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QLabel>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include "basestation/formtitle.h"
#include <QLabel>
#include "Employee/employeedao.h"
#define MARGIN 8  //四个角的宽度
class labelDetail : public QWidget
{
    Q_OBJECT
public:
    explicit labelDetail(int id,QWidget *parent = 0);
    ~labelDetail();
    QFormLayout *formlayout;
    QLabel *nameLabel;
    QLabel *ageLabel;
    QLabel *sexLabel;
    QLabel *addressLabel;
    QLabel *phoneLabel;

    QLabel *showName;
    QLabel *showAge;
    QLabel *showSex;
    QLabel *showAddress;
    QLabel *showPhone;

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
   //void mouseDoubleClickEvent(QMouseEvent *eve);
    void mouseMoveEvent(QMouseEvent *eve);

signals:

public slots:
private:
    bool isLeftPressed;
    int curPos;
    QPoint pLast;
    employeeDao m_employeeDao;
};

#endif // LABELDETAIL_H
