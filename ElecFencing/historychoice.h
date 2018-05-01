#ifndef HISTORYCHOICE_H
#define HISTORYCHOICE_H
#include <QWidget>
#include <QLabel>
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
#include <QLabel>
#include <QComboBox>
#include "basestation/formtitle.h"
#include "label/labeldao.h"
#include <QDateTimeEdit>
#define MARGIN 8

struct HistoryInfo{
    QString lableName;
    QDateTime startTime;
    QDateTime endTime;
};

class HistoryChoice : public QWidget
{
    Q_OBJECT
public:
    void setBox();
    explicit HistoryChoice(QWidget *parent = 0);
    int countFlag(QPoint p,int row);
    void setCursorType(int flag);
    int countRow(QPoint P);
    ~HistoryChoice();
signals:
    void historyInfo(HistoryInfo);

public slots:
    void combine();
    void setReflect();
protected:
    void mousePressEvent(QMouseEvent *eve);
    void mouseReleaseEvent(QMouseEvent *eve);
   // void mouseDoubleClickEvent(QMouseEvent *eve);
    void mouseMoveEvent(QMouseEvent *eve);
private:
    QComboBox *m_timeBox;
    QLabel *m_timeBoxLabel;
    QComboBox *m_idBox;
    QLabel *m_idBoxLabel;

    QLabel *m_beginLabel;
    QDateTimeEdit *m_beginTime;
    QLabel *m_endLabel;
    QDateTimeEdit *m_endTime;


    QPushButton *chk_btn;
    QPushButton *can_btn;
    QGridLayout *gridlayout;
    QHBoxLayout *hor_layout;
    QVBoxLayout *mainlayout;
    QWidget *widget_1;
    QWidget *widget_2;
    QScrollArea *scrollArea;
    FormTitle *title;
    bool isLeftPressed;
    int curPos;
    QPoint pLast;

    QMap<QString,QString> m_reflect;
};

#endif // HISTORYCHOICE_H
