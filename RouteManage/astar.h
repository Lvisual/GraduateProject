#ifndef ASTAR_H
#define ASTAR_H

#include<vector>
#include<list>
#include "point.h"
#include "BowyerWatson.h"

//struct Point
//{

//    int x,y; //点坐标，这里为了方便按照C++的数组来计算，x代表横排，y代表竖列
//    int F,G,H; //F=G+H
//    Point *parent; //parent的坐标，这里没有用指针，从而简化代码
//    Point(int _x,int _y):x(_x),y(_y),F(0),G(0),H(0),parent(nullptr)  //变量初始化
//    {
//    }
//};

class Astar
{
public:
    //void InitAstar(std::vector<std::vector<int>>mymaze);
    std::list<CPoint *> GetPath(CPoint &startPoint,CPoint &endPoint);
    int w;  //返回起始点在哪一个三角形内
    //void setMaze();
    int findPolygon(CPoint startPoint);
     CPoint *isInList(std::list<CPoint *> &list, CPoint *point) ;
     CBowyerWatson cbowyer;

private:
    CPoint *findPath(CPoint &startPoint,CPoint &endPoint);
    std::vector<CPoint *> getSurroundPoints(CPoint point);
    //bool isCanreach(const CPoint *point,const CPoint *target) const; //判断某点是否可以用于下一步判断
   // CPoint *isInList(std::list<CPoint *> &list, CPoint *point) ; //判断开启/关闭列表中是否包含某点
    CPoint *getLeastFpoint(); //从开启列表中返回F值最小的节点
    //计算FGH值
    int calcG(CPoint *temp_start,CPoint *point);
    int calcH(CPoint *point,CPoint *end);
    int calcF(CPoint *point);
private:
    std::vector<std::vector<int>> maze;
    std::list<CPoint *> openList;  //开启列表
    std::list<CPoint *> closeList; //关闭列表

};
#endif // ASTAR_H
