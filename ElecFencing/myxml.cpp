#include "myxml.h"
#include<QString>
#include<QFile>
#include<QDomDocument>
#include<QDomElement>
#include<QDebug>
#include<QPoint>
#include <QVector>
MyXml::MyXml()
{
}

QVector<QPoint> MyXml::readXml(QString time,QString filename){
    m_historyPoints.clear();
    QDomDocument doc("mydocument");
    QFile file(filename);
    doc.setContent(&file);
    file.close();
    // print out the element names of all elements that are direct children
    // of the outermost element.
    QDomElement docElem = doc.documentElement();
    QDomNode n = docElem.firstChild();
    while (!n.isNull())
    {   
        QDomElement e = n.toElement();
        if (e.tagName()==time)
        {
           QDomNodeList list = n.childNodes();
           for(int i =0;i < list.size();i++){
               QPoint p(1,2);
               QDomNode node = list.at(i);
               if(node.hasChildNodes()){
                   QDomNodeList listp = node.childNodes();
                   p.setX(listp.at(0).toElement().text().toInt());
                   p.setY(listp.at(1).toElement().text().toInt());
                   m_historyPoints.push_back(p);
               }
           }
            break;
        }
        n = n.nextSibling();
    }
    return m_historyPoints;

}
