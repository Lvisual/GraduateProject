#include "Triangle.h"
#include <math.h>
#include <QDebug>
#include <vector>
#include "BowyerWatson.h"
CTriangle::CTriangle(CPoint pt1, CPoint pt2, CPoint pt3)
{
    p1 = pt1;
    p2 = pt2;
    p3 = pt3;//三角形三个顶点

    TriCenter.x= (p1.x+p2.x+p3.x)/3;
    TriCenter.y= (p1.y+p2.y+p3.y)/3;

    p1.obstacleflag=pt1.obstacleflag;
    p2.obstacleflag=pt2.obstacleflag;
    p3.obstacleflag=pt3.obstacleflag;

    l1 = CLine(p1,p2);
    l2 = CLine(p2,p3);
    l3 = CLine(p3,p1);//三角形的三个边

    float dis1 = CPoint::distance(p1,p2);
    float dis2 = CPoint::distance(p2,p3);
    float dis3 = CPoint::distance(p3,p1);//三个边的大小

    radiu = dis1*dis2*dis3/TriangleArea()/4;


    float c1, c2;
    float xA, yA, xB, yB, xC, yC;

    xA = p1.x; yA = p1.y;
    xB = p2.x; yB = p2.y;
    xC = p3.x; yC = p3.y;
    c1 = (xA * xA + yA * yA - xB * xB - yB * yB) / 2;
    c2 = (xA * xA + yA * yA - xC * xC - yC * yC) / 2;

    center.x = (c1 * (yA - yC) - c2 * (yA - yB)) /
        ((xA - xB) * (yA - yC) - (xA - xC) * (yA - yB));
    center.y = (c1 * (xA - xC) - c2 * (xA - xB)) /
        ((yA - yB) * (xA - xC) - (yA - yC) * (xA - xB)); //x、y的中心点坐标

}

float CTriangle::TriangleArea()
{
    return fabs(p1.x * p2.y + p2.x * p3.y
        + p3.x * p1.y - p2.x * p1.y
        - p3.x * p2.y - p1.x * p3.y) / 2;
}

bool CTriangle::CheckInCircle(CPoint pt)//判断点是否落在某一个三角形的外接圆内
{
    if (CPoint::distance(center,pt) <= radiu)
    {
        return true;
    }

    return false;
}
/*
int CTriangle::CheckIntri(std::vector<CTriangle*> tg,CPoint p)
{
    int result=0;
    qDebug () << "kkkkkkk"<<tg.size();
    for(int i=0;i<tg.size();i++)
     {
      int t1=tg.at(i)->p1.x;
      int t2=tg.at(i)->p1.y;
      int t3=tg.at(i)->p2.x;
      int t4=tg.at(i)->p2.y;
      int t5=tg.at(i)->p3.x;
      int t6=tg.at(i)->p3.y;
     qDebug () << "qqqqqqqq"<<t1<<t2<<t3<<t4<<t5<<t6;
     qDebug () << "p"<<p.x<<p.y;
     int a=(t1-p.x)*(t4-t2)-(t2-p.y)*(t3-t1);
     int b=(t1-t5)*(t4-t2)-(t2-t6)*(t3-t1);
     int c=(t3-p.x)*(t6-t4)-(t4-p.y)*(t5-t3);
     int d=(t3-t1)*(t6-t4)-(t4-t2)*(t5-t3);
     int e=(t5-p.x)*(t2-t6)-(t6-p.y)*(t1-t5);
     int f=(t5-t3)*(t2-t6)-(t6-t4)*(t1-t5);
      qDebug () << "wwwwwwwwwwww"<<a<<b<<c<<d<<e<<f;
     if(a*b>0 && c*d>0 && e*f>0){
         qDebug () << "oooooooooo"<<i;
         result=i;
     }
    }
    qDebug()<<"result:"<<result;
    qDebug()<<"jieshiweimao";
    return result ;
}
*/
bool CTriangle::CheckIsTri(CTriangle tg)
{
   if(this->p1==tg.p1&&this->p2==tg.p2&&this->p3==tg.p3){
       return true;
   }
   else{
      return false;
   }
}



CLine CTriangle::FindNearestLine(CPoint pt)
{
    float dis1 = l1.Point2LineDistance(pt);
    float dis2 = l2.Point2LineDistance(pt);
    float dis3 = l3.Point2LineDistance(pt);

    if (dis1 <= dis2 && dis1 <= dis3)
    {
        return l1;
    }
    if (dis2 <= dis1 && dis2 <= dis3)
    {
        return l2;
    }

    return l3;
}

CLine* CTriangle::FindCommonLine(CTriangle tg)//公共边
{
  //  qDebug()<<"this->p1.obstacleflagwewewewewew"<<this->p1.obstacleflag;
    if (this->l1 == tg.l1 || this->l1 == tg.l2 || this->l1 == tg.l3)
    {
        return &l1;
    }

    if (this->l2 == tg.l1 || this->l2 == tg.l2 || this->l2 == tg.l3)
    {
        return &l2;
    }

    if (this->l3 == tg.l1 || this->l3 == tg.l2 || this->l3 == tg.l3)
    {
        return &l3;
    }

    return NULL;
}
CLine* CTriangle::FindCommonLine2(CTriangle tg)//公共边
{
  //  qDebug()<<"this->p1.obstacleflagwewewewewew"<<this->p1.obstacleflag;
    if(!(this->p1==tg.p1&&this->p2==tg.p2&&this->p3==tg.p3))
    {
    if (this->l1 == tg.l1 || this->l1 == tg.l2 || this->l1 == tg.l3)
    {
        return &l1;
    }

    if (this->l2 == tg.l1 || this->l2 == tg.l2 || this->l2 == tg.l3)
    {
        return &l2;
    }

    if (this->l3 == tg.l1 || this->l3 == tg.l2 || this->l3 == tg.l3)
    {
        return &l3;
    }

    return NULL;
    }
}

CLine* CTriangle::FindCommonLine233(CTriangle tg)//为了删除障碍物，设置的公共边
{

   if(!(this->p1==tg.p1&&this->p2==tg.p2&&this->p3==tg.p3))
    /*
    if(this->p1.obstacleflag==1&&this->p2.obstacleflag==1&&this->p3.obstacleflag==1&&
            tg.p1.obstacleflag==1&&tg.p2.obstacleflag==1&&tg.p3.obstacleflag==1)*/
    {


        if (this->l1 == tg.l1 || this->l1 == tg.l2 || this->l1 == tg.l3)
        {
              return &l1;

        }

        if (this->l2 == tg.l1 || this->l2 == tg.l2 || this->l2 == tg.l3)
        {

              return &l2;

        }

        if (this->l3 == tg.l1 || this->l3 == tg.l2 || this->l3 == tg.l3)
        {

              return &l3;

        }
    }
    return NULL;
}

CPoint CTriangle::GetOtherPoint(CPoint pt1, CPoint pt2)
{
    if (!(p1 == pt1) && !(p1 == pt2))
    {
        return p1;
    }

    if (!(p2 == pt1) && !(p2 == pt2))
    {
        return p2;
    }

    return p3;
}

bool CTriangle::CheckPointExist(CPoint pt)
{
    if (pt == p1 || pt == p2 || pt == p3)
    {
        return true;
    }

    return false;
}

bool CTriangle::operator ==(const CTriangle& t)
{
    if ((p1 == t.p1) && (p2 == t.p2) && (p3 == t.p3))
    {
        return true;
    }
    if ((p1 == t.p1) && (p3 == t.p2) && (p2 == t.p3))
    {
        return true;
    }

    if ((p2 == t.p1) && (p1 == t.p2) && (p3 == t.p3))
    {
        return true;
    }
    if ((p2 == t.p1) && (p3 == t.p2) && (p1 == t.p3))
    {
        return true;
    }

    if ((p3 == t.p1) && (p2 == t.p2) && (p1 == t.p3))
    {
        return true;
    }
    if ((p3 == t.p1) && (p1 == t.p2) && (p2 == t.p3))
    {
        return true;
    }

    return false;
}


CPoint* CTriangle::getCenter(){
    return &TriCenter;
}






