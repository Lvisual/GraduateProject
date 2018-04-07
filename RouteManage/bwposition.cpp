#include "bwposition.h"
#include <QDebug>
BwPosition::BwPosition()
{

}
bool BwPosition:: PtInPolygon(QPointF p)
{
        // ��������
       int nCross = 0;
       for (int i = 0; i < 3; i++)
       {
              QPointF p1 = m_Polygon[i];
              QPointF p2 = m_Polygon[(i + 1) % 3];// ����һ��������һ��������
              if (p1.y()==p2.y())
                      continue;
              if (p.y()<qMin(p1.y(),p2.y()))
                      continue;
              if (p.y()>= qMax(p1.y(),p2.y()))
                     continue;

              // �󽻵���x����

              double x = (double)(p.y() - p1.y()) * (double)(p2.x() - p1.x()) / (double)(p2.y() - p1.y()) + p1.x();

              // ֻͳ��p1p2��p�������ߵĽ���
              if (x > p.x())
              {
                     nCross++;
              }
       }
       // ����Ϊż�������ڶ�����֮��
       return (nCross % 2 == 1);
}

bool BwPosition::PtInPolygon2(QPointF p){
    int n = m_Polygon.size();
    for(int i =0;i < n;i++){
        if(p==m_Polygon[i])
            return true;
    }
    return false;

}
 int BwPosition::getTheIndex(vector<CTriangle*>tg,QPointF p){
    for(int i= 0;i < tg.size();i++){
        float t1=tg.at(i)->p1.x;
        float t2=tg.at(i)->p1.y;
        float t3=tg.at(i)->p2.x;
        float t4=tg.at(i)->p2.y;
        float t5=tg.at(i)->p3.x;
        float t6=tg.at(i)->p3.y;
        QPointF p1(t1,t2);
        QPointF p2(t3,t4);
        QPointF p3(t5,t6);
        //qDebug() << p1 << " " << p2 <<" " << p3 << "\n";
        m_Polygon.push_back(p1);
        m_Polygon.push_back(p2);
        m_Polygon.push_back(p3);
        bool result = this->PtInPolygon(p);
        m_Polygon.clear();
        if(result)
            return i;
        else
            continue;
    }
    return -1;
 }

bool BwPosition::isIntheObstacle(CTriangle *c, QVector<QPointF>v){
    m_Polygon.clear();
    m_Polygon.append(v);
    QPointF p1(c->p1.x,c->p1.y);
    QPointF p2(c->p2.x,c->p2.y);
    QPointF p3(c->p3.x,c->p3.y);
    if(PtInPolygon2(p1)&&PtInPolygon2(p2)&&PtInPolygon2(p3)){
        return true;
    }
    return false;
}


BwPosition::~BwPosition(){}
