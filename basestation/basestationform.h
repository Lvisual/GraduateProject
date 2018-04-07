#ifndef BASESTATONFORM_H
#define BASESTATONFORM_H

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
#include <QComboBox>
#include "basetypedao.h"
#define MARGIN 8  //鍥涗釜瑙掔殑瀹藉害

#include "basemodel.h"
#include "formtitle.h"

namespace Ui {
class BaseStationForm;
}

class BaseStationForm : public QWidget
{
    Q_OBJECT

public:
    explicit BaseStationForm(QWidget *parent = 0);
    ~BaseStationForm();

    QFormLayout *formlayout1;
    QFormLayout *formlayout2;
    QLineEdit *idEdit;
    QLineEdit *macEdit;
    //QLineEdit *cateEdit;
    QLineEdit *xEdit;
    QLineEdit *yEdit;
    QLineEdit *zEdit;
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
    QLabel *m_boxLabel;
    QComboBox *m_box;
    int countFlag(QPoint p,int row);
    void setCursorType(int flag);
    int countRow(QPoint P);
    void setBox();
protected:
    void mousePressEvent(QMouseEvent *eve);
    void mouseReleaseEvent(QMouseEvent *eve);
   // void mouseDoubleClickEvent(QMouseEvent *eve);
    void mouseMoveEvent(QMouseEvent *eve);

signals:
    void newBaseItem(BaseInfo &info);
public slots:
    void combine();

private:
    Ui::BaseStationForm *ui;
    bool isLeftPressed;
    int curPos;
    QPoint pLast;
};

#endif // BASESTATIONFORM_H
