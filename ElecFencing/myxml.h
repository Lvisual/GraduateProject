#ifndef MYXML_H
#define MYXML_H
#include<QString>
#include<QPoint>
#include<QVector>
class MyXml
{
public:
    MyXml();
    QVector<QPoint> readXml(QString time,QString filename);
    //void writeXml(QString filename);
private:
    QVector<QPoint> m_historyPoints;
};

#endif // MYXML_H
