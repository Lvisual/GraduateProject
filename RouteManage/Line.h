#ifndef CLINE_H
#define CLINE_H
#include "Point.h"

class CLine
{
public:
    CPoint p1;
    CPoint p2;

    CLine()
    {

    }

    CLine(CPoint pt1, CPoint pt2) //确定为某个线的两个端点
    {
        p1.x = pt1.x;
        p1.y = pt1.y;
        p1.obstacleflag=pt1.obstacleflag;
        p2.x = pt2.x;
        p2.y = pt2.y;
        p2.obstacleflag=pt2.obstacleflag;
    };

    bool CheckPointExist(CPoint pt)//检查某个点是否存在
    {
        if (pt == p1 || pt == p2)
        {
            return true;
        }

        return false;
    };

    float Point2LineDistance(CPoint pt);

    bool operator ==(const CLine& l);
    CLine& operator =(const CLine& l);
};

#endif // CLINE_H
