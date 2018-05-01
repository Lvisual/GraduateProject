#ifndef MYFILE_H
#define MYFILE_H

#include <QString>
#include <QTextStream>
#include<QDateTime>
#define max1 100
class MyFile
{
public:
    MyFile();
    void readFile(QString filename);
    void writeFile(QString filename);
    QVector<QPointF> getHistoryPoint(QString filename,QString labelName,QDateTime startTime,QDateTime endTime);
    QString* getBuffer();
    int getRow();
private:
QString  m_buffer[max1];
int m_row;
};

#endif // MYFILE_H
