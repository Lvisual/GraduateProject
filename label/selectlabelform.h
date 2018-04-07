#ifndef SELECTLABELFORM_H
#define SELECTLABELFORM_H

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
#define MARGIN 8  //�ĸ��ǵĿ��
#include "basestation/formtitle.h"

class selectLabelForm : public QWidget
{
    Q_OBJECT
public:
    explicit selectLabelForm(QWidget *parent = 0);
    ~selectLabelForm();
    QFormLayout *formlayout;

    QLineEdit *idEdit;

    QPushButton *chk_btn;
    QPushButton *can_btn;
    QGridLayout *gridlayout;
    QHBoxLayout *hor_layout;
    QVBoxLayout *mainlayout;
    QWidget *widget_1;
    QWidget *widget_2;
    QScrollArea *scrollArea;
    FormTitle *title;
    //��������
    int countFlag(QPoint p,int row);
    void setCursorType(int flag);
    int countRow(QPoint P);
protected:
    void mousePressEvent(QMouseEvent *eve);
    void mouseReleaseEvent(QMouseEvent *eve);
   // void mouseDoubleClickEvent(QMouseEvent *eve);
    void mouseMoveEvent(QMouseEvent *eve);

signals:
    void newLabelId(int id);
public slots:
    void combine();
private:
    bool isLeftPressed;
    int curPos;
    QPoint pLast;
};

#endif // SELECTLABELFORM_H
