#ifndef BWPOSITION_H
#define BWPOSITION_H
#include <QVector>
#include <vector>
#include <QPointF>
using namespace std;
#include "Triangle.h"
class BwPosition
{

public:
    BwPosition();
    bool PtInPolygon(QPointF p);
    bool PtInPolygon2(QPointF p);
    int getTheIndex(vector<CTriangle*>,QPointF p);
    bool isIntheObstacle(CTriangle *c,QVector<QPointF>v);
    ~BwPosition();
private:
    QVector<QPointF> m_Polygon;
};

#endif // BWPOSITION_H
