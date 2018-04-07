#include "BowyerWatson.h"
#include "Point.h"
#include "Line.h"
#include "Triangle.h"
#include <iostream>
#include <QStringList>
#include <QTextStream>
#include <QDebug>
#include <vector>
#include "bwfile.h"
#include "Point.h"
#include "bwposition.h"
#include <QStringList>
using namespace std;

CBowyerWatson::CBowyerWatson(QWidget *parent)
    : QMainWindow(parent)
{
   ClearBowyerWatson();
   setObstaclePolygon();
}

CBowyerWatson::~CBowyerWatson()
{
     ClearBowyerWatson();
}
CBowyerWatson* CBowyerWatson::m_pBowyerWatson = NULL;


CBowyerWatson* CBowyerWatson::GetInstance()
{
    if( !m_pBowyerWatson )
        m_pBowyerWatson = new CBowyerWatson;
    return m_pBowyerWatson;
}

void CBowyerWatson::ClearBowyerWatson()
{
    m_bUpdateDrawFlag = false;

    std::list<CPoint*>::iterator iter_point =	m_lstBowyerWatsonPointList.begin();
    while (iter_point != m_lstBowyerWatsonPointList.end())
    {
        std::list<CPoint*>::iterator iter_pointNext = iter_point;
        iter_pointNext++;

        SAFE_DELETE(*iter_point);
        m_lstBowyerWatsonPointList.erase(iter_point);

        iter_point = iter_pointNext;
    }//Point


    std::list<CLine*>::iterator iter_line =	m_lstBowyerWatsonLineList.begin();
    while (iter_line != m_lstBowyerWatsonLineList.end())
    {
        std::list<CLine*>::iterator iter_lineNext = iter_line;
        iter_lineNext++;

        SAFE_DELETE(*iter_line);
        m_lstBowyerWatsonLineList.erase(iter_line);

        iter_line = iter_lineNext;
    }//line

    std::list<CTriangle*>::iterator iter_triangle =	m_lstBowyerWatsonTriangleList.begin();
    while (iter_triangle != m_lstBowyerWatsonTriangleList.end())
    {
        std::list<CTriangle*>::iterator iter_triangleNext = iter_triangle;
        iter_triangleNext++;

        SAFE_DELETE(*iter_triangle);
        m_lstBowyerWatsonTriangleList.erase(iter_triangle);

        iter_triangle = iter_triangleNext;
    }//Triangle

    iter_point = m_lstAddPointList.begin();
    while (iter_point != m_lstAddPointList.end())
    {
        std::list<CPoint*>::iterator iter_pointNext = iter_point;
        iter_pointNext++;

        SAFE_DELETE(*iter_point);
        m_lstAddPointList.erase(iter_point);

        iter_point = iter_pointNext;
    }//Point
}

//设置三角剖分的范围
void CBowyerWatson::CreateHelperPoint(CPoint pt1, CPoint pt2, CPoint pt3, CPoint pt4)
{
    mHelperPoints[0] = pt1;
    mHelperPoints[1] = pt2;
    mHelperPoints[2] = pt3;
    mHelperPoints[3] = pt4;

    pt1.obstacleflag=0;
    pt2.obstacleflag=0;
    pt3.obstacleflag=0;
    pt4.obstacleflag=0;

    //鍔犲叆杈呭姪鐐�涓�
    AddBowyerWatsonPoint(pt1);
    AddBowyerWatsonPoint(pt2);
    AddBowyerWatsonPoint(pt3);
    AddBowyerWatsonPoint(pt4);

    //鍔犲叆杈呭姪绐椾綋鐨�鏉¤竟
    CLine line1 = CLine(pt1,pt2);
    CLine line2 = CLine(pt2,pt3);
    CLine line3 = CLine(pt3,pt4);
    CLine line4 = CLine(pt4,pt1);
    CLine line5 = CLine(pt2,pt4);
    AddBowyerWatsonLine(line1);
    AddBowyerWatsonLine(line2);
    AddBowyerWatsonLine(line3);
    AddBowyerWatsonLine(line4);
    AddBowyerWatsonLine(line5);

    //鍔犲叆杈呭姪涓夎褰�涓�
    CTriangle tg1 = CTriangle(pt1,pt2,pt4);
    CTriangle tg2 = CTriangle(pt2,pt3,pt4);
    AddBowyerWatsonTriangle(tg1);
    AddBowyerWatsonTriangle(tg2);

}
//添加新点
void CBowyerWatson::AddNewPoint(CPoint pt,int obstacleflag)
{
    pt.obstacleflag=obstacleflag;
    bool existflag = false;
    std::list<CPoint*>::iterator iter_point = m_lstAddPointList.begin();
    for ( ;iter_point != m_lstAddPointList.end();iter_point++)
    {
        if (pt == (**iter_point))
        {
            existflag = true;
        }
    }

    if (!existflag)
    {
        CPoint* newPoint = new CPoint(pt.x,pt.y);
        newPoint->obstacleflag=obstacleflag;
        m_lstAddPointList.push_back(newPoint);
    }
}

//逐点插入法
void CBowyerWatson::UpdateNewPoint()
{
    std::list<CPoint*>::iterator iter_point = m_lstAddPointList.begin();
    while (iter_point != m_lstAddPointList.end())
    {
        ProcessNewPoint(**iter_point);

        std::list<CPoint*>::iterator iter_pointNext = iter_point;
        iter_pointNext++;

        SAFE_DELETE(*iter_point);
        m_lstAddPointList.erase(iter_point);

        iter_point = iter_pointNext;
    }//Point
}

//澧炲姞Delaunay涓夎褰㈢殑鐐�
void CBowyerWatson::AddBowyerWatsonPoint(CPoint pt)
{
    bool existflag = false;
    std::list<CPoint*>::iterator iter_point = m_lstBowyerWatsonPointList.begin();
    for ( ;iter_point != m_lstBowyerWatsonPointList.end();iter_point++)
    {
        if (pt == (**iter_point))
        {
            existflag = true;
        }
    }

    if (!existflag)
    {
        CPoint* newPoint = new CPoint(pt.x,pt.y);
        m_lstBowyerWatsonPointList.push_back(newPoint);
    }

}

//添加线段
void CBowyerWatson::AddBowyerWatsonLine(CLine line)
{
    bool existflag = false;
    std::list<CLine*>::iterator iter_line = m_lstBowyerWatsonLineList.begin();
    for ( ;iter_line != m_lstBowyerWatsonLineList.end();iter_line++)
    {
        if (line == (**iter_line))
        {
            existflag = true;
        }
    }

    if (!existflag)
    {
        CLine* newLine = new CLine(line.p1,line.p2);
        m_lstBowyerWatsonLineList.push_back(newLine);
    }
}

//删除两个三角形的共有线
void CBowyerWatson::DelBowyerWatsonLine(CLine line)
{
    std::list<CLine*>::iterator iter_line =	m_lstBowyerWatsonLineList.begin();
    while (iter_line != m_lstBowyerWatsonLineList.end())
    {
        if (line == (**iter_line))
        {
            SAFE_DELETE(*iter_line);
            m_lstBowyerWatsonLineList.erase(iter_line);
            break;
        }
        else
            iter_line++;
    }//line

    std::list<CTriangle*>::iterator iter_Triangle =	m_lstBowyerWatsonTriangleList.begin();
    while (iter_Triangle != m_lstBowyerWatsonTriangleList.end())
    {
        if ((*iter_Triangle)->l1 == line || (*iter_Triangle)->l2 == line || (*iter_Triangle)->l3 == line )
        {
            SAFE_DELETE(*iter_Triangle);
            m_lstBowyerWatsonTriangleList.erase(iter_Triangle);
            break;
        }
        else
            iter_Triangle++;
    }//Triangle
}

//添加三角形
void CBowyerWatson::AddBowyerWatsonTriangle(CTriangle triangle)
{
    bool existflag = false;
    std::list<CTriangle*>::iterator iter_Triangle = m_lstBowyerWatsonTriangleList.begin();
    for ( ;iter_Triangle != m_lstBowyerWatsonTriangleList.end();iter_Triangle++)
    {
        if (triangle == (**iter_Triangle))
        {
            existflag = true;
        }
    }

    if (!existflag)
    {
        if(!sameline(triangle.p1,triangle.p2,triangle.p3)){
        CTriangle* newTriangle = new CTriangle(triangle.p1,triangle.p2,triangle.p3);
        m_lstBowyerWatsonTriangleList.push_back(newTriangle);
        }
    }
}

//删除三角形
void CBowyerWatson::DelBowyerWatsonTriangle(CTriangle triangle)
{
    std::list<CTriangle*>::iterator iter_Triangle =	m_lstBowyerWatsonTriangleList.begin();
    while (iter_Triangle != m_lstBowyerWatsonTriangleList.end())
    {
        if (triangle == (**iter_Triangle))
        {
            SAFE_DELETE(*iter_Triangle);
            m_lstBowyerWatsonTriangleList.erase(iter_Triangle);
            return;
        }
        else
            iter_Triangle++;
    }//line
}


//插入一个点
void CBowyerWatson::ProcessNewPoint(CPoint pt)
{
    std::list<CLine*>	lineList ;
    std::list<CTriangle*> triangleList;
    std::vector<CTriangle*> commonTriangleVector;

    std::list<CLine*>::iterator iter_line =	m_lstBowyerWatsonLineList.begin();
    for(;iter_line != m_lstBowyerWatsonLineList.end();iter_line++)
    {
        CLine* newline = new CLine();
        memcpy(newline, *iter_line, sizeof(CLine));

        lineList.push_back(newline);
    }
    std::list<CTriangle*>::iterator iter_triangle =	m_lstBowyerWatsonTriangleList.begin();
    for(;iter_triangle != m_lstBowyerWatsonTriangleList.end();iter_triangle++)
    {
        CTriangle* newtriangle = new CTriangle();
        memcpy(newtriangle, *iter_triangle, sizeof(CTriangle));

        triangleList.push_back(newtriangle);
    }

    iter_triangle = triangleList.begin();
    while (iter_triangle != triangleList.end())
    {
        //判断一个点是否位于三角形的外接圆中
        if ((*iter_triangle)->CheckInCircle(pt))
        {
            commonTriangleVector.push_back(*iter_triangle);
        }
        iter_triangle++;
    }// triangle

    //如果该点仅位于一个三角形外接圆中
    if (commonTriangleVector.size() == 1)
    {
        std::vector<CTriangle*>::iterator iter_v =	commonTriangleVector.begin();
        //删除该三角形
        DelBowyerWatsonTriangle(**iter_v);

        CLine line1 = CLine(pt,(*iter_v)->p1);
        CLine line2 = CLine(pt,(*iter_v)->p2);
        CLine line3 = CLine(pt,(*iter_v)->p3);
        AddBowyerWatsonLine(line1);
        AddBowyerWatsonLine(line2);
        AddBowyerWatsonLine(line3);

        //新建三个三角形
        if (CheckTriangleLinesExist(pt, (*iter_v)->p1, (*iter_v)->p2))
        {
            CTriangle tg1 = CTriangle(pt,(*iter_v)->p1,(*iter_v)->p2);
            AddBowyerWatsonTriangle(tg1);
        }
        if (CheckTriangleLinesExist(pt, (*iter_v)->p2, (*iter_v)->p3))
        {
            CTriangle tg2 = CTriangle(pt,(*iter_v)->p2,(*iter_v)->p3);
            AddBowyerWatsonTriangle(tg2);
        }
        if (CheckTriangleLinesExist(pt, (*iter_v)->p3, (*iter_v)->p1))
        {
            CTriangle tg3 = CTriangle(pt,(*iter_v)->p3,(*iter_v)->p1);
            AddBowyerWatsonTriangle(tg3);
        }
    }
    //如果该点位于多个三角形的外接圆中
    if (commonTriangleVector.size() > 1)
    {
        for (int i = 0;i < (commonTriangleVector.size()-1);i++)
        {
            for (int j = i+1;j <commonTriangleVector.size();j++)
            {
                CTriangle* trg1 =	*(commonTriangleVector.begin() + i);
                CTriangle* trg2 =	*(commonTriangleVector.begin() +j);

                CLine* commonLine = trg1->FindCommonLine(*trg2);

                if (commonLine != NULL)
                {
                    ////////////////////////////////
                    //鍒犻櫎褰卞搷涓夎褰�
                    DelBowyerWatsonTriangle(*trg1);
                    DelBowyerWatsonTriangle(*trg2);

                    //鍒犻櫎鍏叡杈�
                    DelBowyerWatsonLine(*commonLine);

                    /////////////////////////////////
                    //杩炴帴涓夎褰笁鐐�
                    CLine line1_1 = CLine(pt,trg1->p1);
                    CLine line1_2 = CLine(pt,trg1->p2);
                    CLine line1_3 = CLine(pt,trg1->p3);
                    CLine line2_1 = CLine(pt,trg2->p1);
                    CLine line2_2 = CLine(pt,trg2->p2);
                    CLine line2_3 = CLine(pt,trg2->p3);

                    AddBowyerWatsonLine(line1_1);
                    AddBowyerWatsonLine(line1_2);
                    AddBowyerWatsonLine(line1_3);
                    AddBowyerWatsonLine(line2_1);
                    AddBowyerWatsonLine(line2_2);
                    AddBowyerWatsonLine(line2_3);

                    //鍔犲叆鏂颁笁瑙掑舰
                    if (CheckTriangleLinesExist(pt, trg1->p1, trg1->p2))
                    {
                        CTriangle tg1 = CTriangle(pt, trg1->p1, trg1->p2);
                        AddBowyerWatsonTriangle(tg1);
                    }
                    if (CheckTriangleLinesExist(pt, trg1->p2, trg1->p3))
                    {
                        CTriangle tg2 = CTriangle(pt,trg1->p2,trg1->p3);
                        AddBowyerWatsonTriangle(tg2);
                    }
                    if (CheckTriangleLinesExist(pt, trg1->p3, trg1->p1))
                    {
                        CTriangle tg3 = CTriangle(pt, trg1->p3, trg1->p1);
                        AddBowyerWatsonTriangle(tg3);
                    }

                    if (CheckTriangleLinesExist(pt, trg2->p1, trg2->p2))
                    {
                        CTriangle tg1 = CTriangle(pt, trg2->p1, trg2->p2);
                        AddBowyerWatsonTriangle(tg1);
                    }
                    if (CheckTriangleLinesExist(pt, trg2->p2, trg2->p3))
                    {
                        CTriangle tg2 = CTriangle(pt,trg2->p2,trg2->p3);
                        AddBowyerWatsonTriangle(tg2);
                    }
                    if (CheckTriangleLinesExist(pt, trg2->p3, trg2->p1))
                    {
                        CTriangle tg3 = CTriangle(pt, trg2->p3, trg2->p1);
                        AddBowyerWatsonTriangle(tg3);
                    }

                }
            }
        }
    }

    AddBowyerWatsonPoint(pt);

    iter_line =	lineList.begin();
    while (iter_line != lineList.end())
    {
        std::list<CLine*>::iterator iter_lineNext = iter_line;
        iter_lineNext++;

        SAFE_DELETE(*iter_line);
        lineList.erase(iter_line);

        iter_line = iter_lineNext;
    }//line

    iter_triangle =	triangleList.begin();
    while (iter_triangle != triangleList.end())
    {
        std::list<CTriangle*>::iterator iter_triangleNext = iter_triangle;
        iter_triangleNext++;

        SAFE_DELETE(*iter_triangle);
        triangleList.erase(iter_triangle);

        iter_triangle = iter_triangleNext;
    }//Triangle
}

//妫�鏌elaunay涓夎褰㈢殑绾挎槸鍚﹀瓨鍦紙鏍规嵁绾跨殑鍘熺悊鐢讳笁瑙掑舰锛�
bool CBowyerWatson::CheckTriangleLinesExist(CPoint pt1, CPoint pt2, CPoint pt3)
{
    bool exist_line1 = false;
    bool exist_line2 = false;
    bool exist_line3 = false;

    CLine line1 = CLine(pt1, pt2);
    CLine line2 = CLine(pt2, pt3);
    CLine line3 = CLine(pt3, pt1);

    std::list<CLine*>::iterator iter_line = m_lstBowyerWatsonLineList.begin();
    for ( ;iter_line != m_lstBowyerWatsonLineList.end();iter_line++)
    {
        if (line1 == (**iter_line))
        {
            exist_line1 = true;
            continue;
        }
        if (line2 == (**iter_line))
        {
            exist_line2 = true;
            continue;
        }
        if (line3 == (**iter_line))
        {
            exist_line3 = true;
        }
    }

    if (exist_line1 && exist_line2 && exist_line3)
    {
        return true;
    }

    return false;
}



//删除三角形公共边
void CBowyerWatson::DelCommoooonline()
{
    const std::list<CTriangle*> triangleList1  = m_lstBowyerWatsonTriangleList;
    qDebug() << m_lstBowyerWatsonTriangleList.size() << "size";
    std::list<CTriangle*>::const_iterator iter_triangle = triangleList1.begin();
     for(int i = 0;i < m_obstacle.size();i++){
         m_adjoinTritangle.clear();
         iter_triangle = triangleList1.begin();
     for ( ;iter_triangle != triangleList1.end();iter_triangle++)
    {
        BwPosition p;
        bool isInthePolygon = p.isIntheObstacle(*iter_triangle,m_obstacle[i]);
        if(isInthePolygon){
         m_adjoinTritangle.push_back(*iter_triangle);
         for(int j= 0;j < m_adjoinTritangle.size();j++)
          for(int k = 0; k < m_adjoinTritangle.size();k++){
              CLine* commonLine =m_adjoinTritangle[j]->FindCommonLine233(*m_adjoinTritangle[k]);
              if (commonLine != NULL){
                    DelBowyerWatsonLine(*commonLine);
                }
            }
          }
      }
}
}
//楠岃瘉閭绘帴鐭╅樀
void CBowyerWatson::popArray()
{
    Getmatrix();
    int n=m_lstBowyerWatsonTriangleList.size();
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            //qDebug()<<"bie"<<adjoinArray[i][j];
        }
    }
}
//鑾峰緱涓夎褰㈢殑size
void CBowyerWatson::pushTriangle()
{

std::list<CTriangle*>::const_iterator iter_triangle = m_lstBowyerWatsonTriangleList.begin();
for(;iter_triangle != m_lstBowyerWatsonTriangleList.end();iter_triangle++)
{
    commonTriangleVector1.push_back(*iter_triangle);
}
}


//获得障碍物的邻接关系
void  CBowyerWatson::Getmatrix()
{    pushTriangle();
     std::vector<CTriangle*> commonTriangleVector=commonTriangleVector1;
     for (int i = 0;i <commonTriangleVector.size();i++)
     {
         for (int j =0;j <commonTriangleVector.size();j++)
         {
             CTriangle* trg1 =	*(commonTriangleVector.begin() + i);
             CTriangle* trg2 =	*(commonTriangleVector.begin() +j);
             CLine* commonLine = trg1->FindCommonLine(*trg2);
             if (commonLine != NULL&&(i!=j))
             {
                 adjoinArray[i][j]=1;
             }
             else
             {
                 adjoinArray[i][j]=0;
             }
         }
     }
}


void CBowyerWatson::DrawMesh()
{
    std::list<CLine*>::iterator iter = m_lstBowyerWatsonLineList.begin();
    for ( ;iter != m_lstBowyerWatsonLineList.end();iter++)
    {
        //(*iter)->p1.x, (*iter)->p1.y
        //(*iter)->p2.x, (*iter)->p2.y
    }
}

void CBowyerWatson::Update()
{
    if (m_bUpdateDrawFlag)
    {
        DrawMesh();
    }
}

//设置障碍物的边界点
void CBowyerWatson::setObstaclePolygon(){
   QVector<QPointF>v;
   BwFile myfile;
   myfile.readFile("indoorData.txt");
   QString*str = myfile.getBuffer();
   int n = myfile.getRow();
   int initFlag = 0;
   for(int i = 0;i < n;i++){
       QStringList list = str[i].split(' ');
       int flag = list.at(2).toInt();
       if(flag==initFlag){
       QPointF p(list.at(0).toFloat(),list.at(1).toFloat());
       v.push_back(p);
       if(i==n-1){
           m_obstacle.push_back(v);
           break;
       }
       continue;
       }
       else{
           m_obstacle.push_back(v);
           v.clear();
           initFlag = flag;
           QPointF p(list.at(0).toFloat(),list.at(1).toFloat());
           v.push_back(p);
       }
   }
}
//判断是否三点共线
bool CBowyerWatson::sameline(CPoint p1,CPoint p2,CPoint p3){
    if((p2.y-p1.y)*(p3.x-p2.x)==(p2.x-p1.x)*(p3.y-p2.y)){
        return true;
    }
    else
        return false;
}

QVector<QVector<QPointF>> CBowyerWatson::getPolygon(){
 return m_obstacle;
}
