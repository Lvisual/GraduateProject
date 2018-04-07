#include "judge.h"
#include <QDebug>

Judge::Judge()
{

}
bool Judge:: PtInPolygon(QPointF p)

{
        // 交点个数
       int nCross = 0;
       for (int i = 0; i < 3; i++)
       {

              QPointF p1 = m_Polygon[i];
              QPointF p2 = m_Polygon[(i + 1) % 3];// 最后一个点与第一个点连线
              if (p1.y()==p2.y())
                      continue;
              if (p.y()<qMin(p1.y(),p2.y()))
                      continue;
              if (p.y()>= qMax(p1.y(),p2.y()))
                     continue;

              // 求交点的x坐标

              double x = (double)(p.y() - p1.y()) * (double)(p2.x() - p1.x()) / (double)(p2.y() - p1.y()) + p1.x();

              // 只统计p1p2与p向右射线的交点
              if (x > p.x())
              {
                     nCross++;
              }
       }
       // 交点为偶数，点在多边形之外
       return (nCross % 2 == 1);
}
bool Judge::getresult(vector<CPoint*>tg,QPointF p){

        QPointF p1(tg.at(0)->x,tg.at(0)->y);
        QPointF p2(tg.at(1)->x,tg.at(1)->y);
        QPointF p3(tg.at(2)->x,tg.at(2)->y);
        m_Polygon.push_back(p1);
        m_Polygon.push_back(p2);
        m_Polygon.push_back(p3);
        bool result = this->PtInPolygon(p);
        return result;
 }
Judge::~Judge(){}
