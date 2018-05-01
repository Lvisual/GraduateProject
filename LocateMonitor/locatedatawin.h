#ifndef LOCATEDATAWIN_H
#define LOCATEDATAWIN_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QTextEdit>
#include <QFile>
#include "xmlthread.h"
class LocateDataWin : public QWidget
{
    Q_OBJECT
public:
    explicit LocateDataWin(QWidget *parent = 0);

signals:
    void sendMapData(QString labelId,QPointF curPos);
public slots:
    void dealConnection();
    void getData();
    void closeSocket();
private:
    QTcpServer *m_server;
    QTcpSocket *m_socket;
    QHostAddress *m_host;
    QFile m_file;
};

#endif // LOCATEDATAWIN_H
