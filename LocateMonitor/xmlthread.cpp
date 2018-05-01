#include "xmlthread.h"
#include <QDebug>
QQueue<QString> historyBuffer;
XmlThread::XmlThread()
{
    m_file.setFileName("manPos.txt");
}


void XmlThread::run(){
    if(!m_file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "file to open the file to store the data";
    }
    while(1){
        sleep(5);
        while(!historyBuffer.isEmpty()){
            QString str =historyBuffer.dequeue();
            m_file.write(str.toUtf8());
            qDebug() <<"dequeue" <<  historyBuffer.size() <<endl;
        }
    }
}

