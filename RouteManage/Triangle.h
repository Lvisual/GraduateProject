#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Point.h"
#include "Line.h"
#include<iostream>
#include<vector>
#include<QVector>
#include"BowyerWatson.h"
class CTriangle
{
public :
    int obsflag;
    CPoint p1;
    CPoint p2;
    CPoint p3;

    CLine l1;
    CLine l2;
    CLine l3;

    CPoint center;//外接圆圆心
    CPoint TriCenter;//三角形的质心
    float radiu;

    CTriangle(){}
    CTriangle(CPoint pt1, CPoint pt2, CPoint pt3);

    bool CheckInCircle(CPoint pt);
    bool CheckIsTri(CTriangle tg);//检查是否为这个三角形

    float TriangleArea();

    CLine FindNearestLine(CPoint pt);
    CLine* FindCommonLine(CTriangle tg);
    CLine* FindCommonLine2(CTriangle tg);
    CLine* FindCommonLine233(CTriangle tg);

    CPoint GetOtherPoint(CPoint pt1, CPoint pt2);

    bool CheckPointExist(CPoint pt);
   // int CheckIntri(std::vector<CTriangle*> tg,CPoint P);

    bool operator ==(const CTriangle& t);
    CPoint* getCenter();
};

#endif // TRIANGLE_H
