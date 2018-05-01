#include "locatedatawin.h"
#include "Maps/myfile.h"
extern QQueue<QString> historyBuffer;
LocateDataWin::LocateDataWin(QWidget *parent) : QWidget(parent)
{
    m_server = new QTcpServer(this);
    m_socket  =new QTcpSocket(this);
    m_server->listen(QHostAddress::Any,8000);
    connect(m_server,SIGNAL(newConnection()),this,SLOT(dealConnection()));
 }
void LocateDataWin::dealConnection(){
   // m_file.setFileName("manPos.txt");
    //if(!m_file.open(QIODevice::ReadWrite | QIODevice::Text))
  //  {
   //     qDebug() << "file to open the file to store the data";
 //   }
    m_socket = m_server->nextPendingConnection();
    connect(m_socket,SIGNAL(readyRead()),this,SLOT(getData()));
    connect(m_socket,SIGNAL(disconnected()), m_socket,SLOT(deleteLater()));
}

void LocateDataWin::getData(){
    QByteArray posdata = m_socket->readAll();
    QString tempStr = QString(posdata);
    QStringList strList = tempStr.split(',');
    QPointF pos(strList.at(3).toFloat(),strList.at(4).toFloat());
    historyBuffer.enqueue(tempStr);
    emit(sendMapData(strList.at(1),pos));
    qDebug() << "enqueue" << historyBuffer.size() <<endl;
}

void LocateDataWin::closeSocket(){
    m_socket->close();
}


