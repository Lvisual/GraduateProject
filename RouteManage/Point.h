#ifndef POINT_H
#define POINT_H
#define __CPOINTH__

#define NULL 0
#define SAFE_DELETE(x) if( (x)!=NULL ) { delete (x); (x)=NULL; }

#include <math.h>


class CPoint{

public:
    int obstacleflag;
    float x;
    float y;

    int F=0,G=0,H=0;
    CPoint *parent=NULL;
    CPoint()
    {
        x = 0;
        y = 0;
    };

    static float distance(CPoint pt1 , CPoint pt2)
    {
        return sqrt((pt1.x-pt2.x)*(pt1.x-pt2.x) + (pt1.y-pt2.y)*(pt1.y-pt2.y));//两个点的距离
    };

    CPoint(float fx, float fy)
    {
        x = fx;
        y = fy;
    };

    bool operator ==(const CPoint& p);
    CPoint& operator =(const CPoint& p);
};

#endif // POINT_H
