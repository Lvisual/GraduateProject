#include "Line.h"
#include "Point.h"

float CLine::Point2LineDistance(CPoint pt)//点到线的距离
{
    float a = p2.y - p1.y;
    float b = p1.x - p2.x;
    float c = p2.x*p1.y - p1.x*p2.y;

    float dis = fabs(a*pt.x + b*pt.y + c)/sqrt(a*a + b*b);

    return dis;
}


bool CLine::operator ==(const CLine& l)//构造线的双等号“==”
{
    if (l.p1.x == p1.x && l.p1.y == p1.y &&l.p2.x == p2.x && l.p2.y == p2.y)
    {
        return true;
    }

    if (l.p2.x == p1.x && l.p2.y == p1.y &&l.p1.x == p2.x && l.p1.y == p2.y)
    {
        return true;
    }

    return false;
}

CLine& CLine::operator =(const CLine& l)
{
    p1 = l.p1;
    p2 = l.p2;
    return *this;
}
