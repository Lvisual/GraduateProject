#ifndef JUDGE_H
#define JUDGE_H



#include <QPoint>
#include <QVector>
#include "point.h"
#include <vector>
#include <QPointF>
using namespace  std;

class Judge
{
public:
    Judge();
    bool PtInPolygon(QPointF p);
    bool getresult(vector<CPoint*>tg,QPointF p);
    ~Judge();

private:
    QVector<QPointF> m_Polygon;

};

#endif // JUDGE_H
