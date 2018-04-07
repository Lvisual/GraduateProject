#ifndef ASTAR_H
#define ASTAR_H

#include<vector>
#include<list>
#include "point.h"
#include "BowyerWatson.h"

//struct Point
//{

//    int x,y; //�����꣬����Ϊ�˷��㰴��C++�����������㣬x������ţ�y��������
//    int F,G,H; //F=G+H
//    Point *parent; //parent�����꣬����û����ָ�룬�Ӷ��򻯴���
//    Point(int _x,int _y):x(_x),y(_y),F(0),G(0),H(0),parent(nullptr)  //������ʼ��
//    {
//    }
//};

class Astar
{
public:
    //void InitAstar(std::vector<std::vector<int>>mymaze);
    std::list<CPoint *> GetPath(CPoint &startPoint,CPoint &endPoint);
    int w;  //������ʼ������һ����������
    //void setMaze();
    int findPolygon(CPoint startPoint);
     CPoint *isInList(std::list<CPoint *> &list, CPoint *point) ;
     CBowyerWatson cbowyer;

private:
    CPoint *findPath(CPoint &startPoint,CPoint &endPoint);
    std::vector<CPoint *> getSurroundPoints(CPoint point);
    //bool isCanreach(const CPoint *point,const CPoint *target) const; //�ж�ĳ���Ƿ����������һ���ж�
   // CPoint *isInList(std::list<CPoint *> &list, CPoint *point) ; //�жϿ���/�ر��б����Ƿ����ĳ��
    CPoint *getLeastFpoint(); //�ӿ����б��з���Fֵ��С�Ľڵ�
    //����FGHֵ
    int calcG(CPoint *temp_start,CPoint *point);
    int calcH(CPoint *point,CPoint *end);
    int calcF(CPoint *point);
private:
    std::vector<std::vector<int>> maze;
    std::list<CPoint *> openList;  //�����б�
    std::list<CPoint *> closeList; //�ر��б�

};
#endif // ASTAR_H
