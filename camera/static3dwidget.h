#ifndef STATIC3DWIDGET_H
#define STATIC3DWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
class TGLWidget;
class Static3DWidget : public QWidget
{
    Q_OBJECT
public:
    Static3DWidget();
public:
    QHBoxLayout *H_Layout;
private:
    TGLWidget *p_GLWidget;

};

#endif // STATIC3DWIDGET_H
