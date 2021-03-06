#ifndef POSITION_H
#define POSITION_H

#include <QPoint>
#include <QVector>
class Position   //用于判断一个点是否在某一区域内
{
public:
    Position(QVector<QPoint> v,int n);
    bool PtInPolygon(QPoint p);
    ~Position();
private:
    QVector<QPoint> m_Polygon;
    int m_count;
};

#endif // POSITION_H
