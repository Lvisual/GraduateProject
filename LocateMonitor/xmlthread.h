#ifndef XMLTHREAD_H
#define XMLTHREAD_H

#include <QObject>
#include <QThread>
#include<QVector>
#include <QQueue>
#include<QFile>
class XmlThread : public QThread
{
    Q_OBJECT
public:
     XmlThread();
     void run();
signals:

public slots:
private:
   QFile m_file;
};

#endif // XMLTHREAD_H
