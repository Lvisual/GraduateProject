#ifndef DISPLAY3DWIDGET_H
#define DISPLAY3DWIDGET_H
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolButton>
#include <QDialog>
#include <QLabel>
//#include "RouteManage/ccustommessagebox.h"
#include "ccustommessagebox.h"
class GLWidget;
class Display3dWidget : public QWidget
{
    Q_OBJECT
public:
    Display3dWidget();
public:
    QHBoxLayout *H_Layout;
    QVBoxLayout *V_Layout_1;
    QVBoxLayout *V_Layout_2;
    QToolButton *button_1, *button_2, *button_3;
    QLabel *coorX;
    QLabel *coorY;
    QDialog *D_warning;
    QLabel *L_warning;
   CCustomMessageBox *warningbox;
signals:
    void displayCoor(double x,double y);
public slots:
    void fWanring(bool tf);
private:
    GLWidget *p_GLWidget;
};

#endif // DISPLAY3DWIDGET_H
