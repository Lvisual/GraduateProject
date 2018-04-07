#include "point.h"

bool CPoint::operator ==(const CPoint& p)//构造函数，重新定义了点中的双等号“==”的含义
{
    if (p.x == x && p.y == y)
    {
        return true;
    }

    return false;
}

CPoint& CPoint::operator =(const CPoint& p)
{
    this->obstacleflag=p.obstacleflag;
    x = p.x;
    y = p.y;

    return *this;
}
