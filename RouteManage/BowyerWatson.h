#ifndef BOWYERWATSON_H
#define BOWYERWATSON_H

#include <QMainWindow>
#include <list>
#include "Point.h"
#include <vector>
//#include <QVector>
#include"Line.h"
class CPoint;
class CLine;
class CTriangle;

class CBowyerWatson : public QMainWindow
{
    Q_OBJECT

public:
    CBowyerWatson(QWidget *parent = 0);
    ~CBowyerWatson();
       static		CBowyerWatson* GetInstance();
        bool        sameline(CPoint pt1, CPoint pt2, CPoint pt3);
        void		ClearBowyerWatson();
        void        Getmatrix();
        void		CreateHelperPoint(CPoint pt1, CPoint pt2, CPoint pt3, CPoint pt4);
        void		AddNewPoint(CPoint pt, int a);
        void		UpdateNewPoint();
        void		AddBowyerWatsonPoint(CPoint pt);
        void		AddBowyerWatsonLine(CLine line);
        void		DelBowyerWatsonLine(CLine line);
        void		AddBowyerWatsonTriangle(CTriangle triangle);
        void		DelBowyerWatsonTriangle(CTriangle triangle);
        void		ProcessNewPoint(CPoint pt);
        bool		CheckTriangleLinesExist(CPoint pt1, CPoint pt2, CPoint pt3);
        void        DelCommoooonline();
        void		DrawMesh();
        void        pushTriangle();
       // void        pushArray();
        void        popArray();
        int         adjoinArray[100][100];
        void		SetUpdateDrawFlag(bool flag){m_bUpdateDrawFlag = flag;}
        void		Update();
        void        setObstaclePolygon();
        const std::list<CLine*>& GetBowyerWatsonLines(){return m_lstBowyerWatsonLineList;}
        const std::list<CTriangle*>& GetBowyerWatsonTriangles(){return m_lstBowyerWatsonTriangleList;}
        const std::vector<CTriangle*>& GetcommonTriangles(){return commonTriangleVector1;}
        std::vector<CTriangle*> commonTriangleVector1;
        std::list<CTriangle*>		m_lstBowyerWatsonTriangleList;
        std::list<CPoint*>		m_lstAddPointList;
        std::list<CPoint*>& Getm_lstAddPointList(){return m_lstAddPointList;}
        QVector<QVector<QPointF>> getPolygon();
        QVector<QVector<QPointF>>m_obstacle;
    private:
        std::list<CPoint*>		m_lstBowyerWatsonPointList;
        std::list<CLine*>			m_lstBowyerWatsonLineList;
       // std::list<CTriangle*>		m_lstBowyerWatsonTriangleList;
       //std::vector<CTriangle*> commonTriangleVector1;
       // QVector<CTriangle*> commonTriangleVector;
        std::vector<int*> shuzuvector;
       // std::list<CPoint*>		m_lstAddPointList;
        CPoint mHelperPoints[4];
        //int adjoinArray[100][100];
        static CBowyerWatson* m_pBowyerWatson;
        bool	m_bUpdateDrawFlag;
        //QVector<QVector<QPointF>>m_obstacle;
        QVector<CTriangle*> m_adjoinTritangle;
        //QVector<QVector<QPoint>>
};
#endif // BOWYERWATSON_H
