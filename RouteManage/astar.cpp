#include "astar.h"
#include "point.h"
#include "Triangle.h"
#include "bwposition.h"
#include "BowyerWatson.h"
#include<math.h>
#include<stddef.h>
#include<vector>
#include <QVector>
#include<QDebug>
#include<vector>
using namespace std;

int Astar::calcG(CPoint *temp_start,CPoint *point)
{
    int a=((point->x)-(temp_start->x))*((point->x)-(temp_start->x));
    int b=((point->y)-(temp_start->y))*((point->y)-(temp_start->y));
    int extraG=sqrt(a+b);
    int parentG=point->parent==NULL?0:point->parent->G;
    return parentG+extraG;
}

int Astar::calcH(CPoint *point,CPoint *end)
{
    //用简单的欧几里得距离计算H，这个H的计算是关键，还有很多算法，没深入研究^_^
    return sqrt((double)(end->x-point->x)*(double)(end->x-point->x)+(double)(end->y-point->y)*(double)(end->y-point->y));
}

int Astar::calcF(CPoint *point)
{
    return point->G+point->H;
}

CPoint *Astar::getLeastFpoint()
{

    if(!openList.empty())
       {
           auto resPoint=openList.front();
           for(auto &point:openList)
               if(point->F<resPoint->F)
                   resPoint=point;
           return resPoint;
       }

       return NULL;
}


CPoint *Astar::findPath(CPoint &startPoint,CPoint &endPoint)
{
     openList.push_back(new CPoint(startPoint.x,startPoint.y)); //置入起点,拷贝开辟一个节点，内外隔离
     std::vector<CTriangle*>commonTriangleVector1=cbowyer.GetcommonTriangles();
     qDebug() <<"lk" << commonTriangleVector1.size() << endl;
     int k = this->findPolygon(endPoint);
     CPoint *endTriCenter=commonTriangleVector1[k]->getCenter();
     CPoint *resPoint=NULL;
     int count=1;
    while(!openList.empty())
        {
            CPoint* curPoint=getLeastFpoint(); //找到F值最小的点
            openList.remove(curPoint); //从开启列表中删除
            closeList.push_back(curPoint); //放到关闭列表
            //1,找到当前周围八个格中可以通过的格子
            std::vector<CPoint*> surroundPoints=getSurroundPoints(*curPoint);
            std::vector<CPoint*>::iterator iter = surroundPoints.begin();
            qDebug() << "size" << surroundPoints.size();
            for(;iter!=surroundPoints.end();iter++)
            {
                //2,对于某个点的相邻三角形的中心点，如果它不在开启列表中，加入到开启列表，设置当前格为其父节点，计算F G H
                CPoint*target = *iter;
                if(isInList(closeList,target)){
                    qDebug() <<"dashi";
                continue;
                }
                else if(!isInList(openList,target))
                {
                    qDebug()<< "sanjiao";
                    target->parent=curPoint;
                    target->G=calcG(curPoint,target);
                    target->H=calcH(target,&endPoint);
                    target->F=calcF(target);
                    openList.push_back(target);
                    count++;
                    qDebug() << count << endl;
                }
                //3，对于某个点的相邻三角形的中心点，如果它在开启列表中，计算G值, 如果比原来的大, 就什么都不做, 否则设置它的父节点为当前点,并更新G和F
                else
                {
                    int tempG=calcG(curPoint,target);
                    if(tempG<target->G)
                    {
                        target->parent=curPoint;
                        target->G=tempG;
                        target->F=calcF(target);
                    }
                }
                resPoint=isInList(openList,endTriCenter);
                if(resPoint)
                    break; //返回列表里的节点指针，不要用原来传入的endpoint指针，因为发生了深拷贝
            }
            if(resPoint){
                  break;
            }
        }
    qDebug() << "the max size of openlist: " <<count;
    return  resPoint;
}


CPoint *Astar::isInList(std::list<CPoint *> &list, CPoint *point)
{
   if(list.size()==0)
       return NULL;
    //判断某个节点是否在列表中，这里不能比较指针，因为每次加入列表是新开辟的节点，只能比较坐标
   std::list<CPoint *>::iterator iter = list.begin();
   for(;iter!=list.end();iter++){
       if(((*iter)->x==point->x)&&((*iter)->y==point->y))
          {
           return *iter;
          }
       else
          continue;
   }
   return NULL;
}


std::list<CPoint *> Astar::GetPath(CPoint &startPoint,CPoint &endPoint)
{
    CPoint *result=findPath(startPoint,endPoint);
         CPoint *extrapoint = result;
         std::list<CPoint *> path;
         path.push_front(&endPoint) ;
         //返回路径，如果没找到路径，返回空链表
         while(result)
         {
              path.push_back(result);
              result=result->parent;
         }
         path.remove(extrapoint);
         return path;
}




//判断起始点在哪一个三角形内
int Astar::findPolygon(CPoint point){
     std::vector<CTriangle*>commonTriangleVector1=cbowyer.GetcommonTriangles();
     QPoint p(point.x,point.y);
     BwPosition pos;
     return pos.getTheIndex(commonTriangleVector1,p);
}

//遍历的是邻接矩阵，将有公共边的边的三角形的质心放入
std::vector<CPoint*> Astar::getSurroundPoints(CPoint point)
{
    std::vector<CPoint*> surroundPoints;
    int i= this->findPolygon(point);
    qDebug()<< "i " << i << endl;
    std::list<CTriangle*> m_lstBowyerWatsonTriangleList= cbowyer.GetBowyerWatsonTriangles();
    std::list<CTriangle*>::iterator iter2 = m_lstBowyerWatsonTriangleList.begin();
    qDebug() <<"all the triangle:" << m_lstBowyerWatsonTriangleList.size();
//    std::list<CTriangle*>::iterator m_iter = m_lstBowyerWatsonTriangleList.begin();
//    for(;m_iter!=m_lstBowyerWatsonTriangleList.end();m_iter++){
//        qDebug()<<(*m_iter)->p1.x<<" "<<(*m_iter)->p1.y<<" ";
//        qDebug()<<(*m_iter)->p2.x<<" "<<(*m_iter)->p2.y<<" ";
//         qDebug()<<(*m_iter)->p3.x<<" "<<(*m_iter)->p3.y<<endl;

//     }
    for(int j=0;j<m_lstBowyerWatsonTriangleList.size();j++){
        iter2 = m_lstBowyerWatsonTriangleList.begin();
        if((cbowyer.adjoinArray[i][j])==1){
           for(int k =0;k<j;k++)
              iter2++;
           surroundPoints.push_back((*iter2)->getCenter());
        }
    }
    qDebug() << "surroundingSize" << surroundPoints.size();
    return surroundPoints;
}
