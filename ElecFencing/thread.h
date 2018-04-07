#ifndef THREAD_H
#define THREAD_H
#include<QThread>
#include<QObject>
#include<QPoint>
#include"moveman.h"
#include"position.h"
#include<QPainterPath>
#include <QTimeLine>
class Thread : public QThread
{
    Q_OBJECT
public:
    Thread();
    void stop();
    void setItem(MoveMan*);
    void setPath(QVector<QPoint> v);
public:
    void run();
private:
    MoveMan * m_man;
    QVector<QPoint> m_path;
    QTimeLine *m_line;
};











#endif // THREAD_H
