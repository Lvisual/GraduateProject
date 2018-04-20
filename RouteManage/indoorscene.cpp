#include "indoorscene.h"
#include "astar.h"
#include "BowyerWatson.h"
#include "bwfile.h"
#include "Maps/route.h"
#include <list>
using namespace  std;
IndoorScene::IndoorScene(QObject *parent):QGraphicsScene(parent){
startItem = new TargetItem(0);
endItem = new TargetItem(1);
initAstar();
initScene();
}


void IndoorScene :: openFile()
{
    QString s = QFileDialog::getOpenFileName(0, "Select A File", "/", "Txt File(*.txt)");
    if (s.isEmpty())
    {
        QMessageBox::information(0, tr("INformation"), tr("Open failed!"));
        return;
    }
    int st = 0;
    int id;
    float x1,y1,a,b,angle;
    int r1, r2, g1, g2, a1, a2, b1, b2;
    int width;
    currentPath = s;
    QFile file(currentPath);
    if (file.open(QFile::ReadOnly))
    {
        QTextStream cin(&file);
        while(!cin.atEnd())
        {
          //  st = 0;       //st���Ա���ͼԪ������
            cin >>st>>id;
            GraphicsItem *item;
            if (st == 0)
                break;
            if (st == 3)   //�������ߵĻ�
            {
                //float x2,y2;
               // cin>>x1>>y1>>x2>>y2>>a>>b>>r1>>g1>>b1>>a1>>r2>>g2>>b2>>a2>>width;
                cin>>x1>>y1>>a>>b>>angle>>r1>>g1>>b1>>a1>>r2>>g2>>b2>>a2>>width;
                item = new GraphicsLineItem(0);
                item->setX(x1);
                item->setY(y1);
                item->setPen(QPen(QColor(r1, g1, b1, a1),width));
                item->setBrush( QColor(r2, g2, b2, a2));
                item->setMyShape(QColor(r1, g1, b1, a1), QColor(r2, g2, b2, a2), width);
                item->resizeTo(SizeHandleRect::LeftTop,QPointF(x1-a/2,y1-b/2));
                item->resizeTo( SizeHandleRect::RightBottom,QPointF(x1+a/2,y1+b/2));
                item->setRotation(angle);
                this->addItem(item);
                item_container.append(item);
                item_container.at(id);
                continue;
            }
            else
                cin>>x1>>y1>>a>>b>>angle>>r1>>g1>>b1>>a1>>r2>>g2>>b2>>a2>>width;

            switch(st)
            {
            case 1:
                item=new GraphicsRectItem(QRect(0,0,0,0),NULL);
                break;
            case 2:

                item =new GraphicsEllipseItem(QRect(0,0,0,0),NULL);
                break;
            case 4:
                item= new GraphicsArcItem(0);
                break;
            case 5:
                item=new GraphicsPieItem(0);
                break;
            }
            item->setX(x1);
            item->setY(y1);
            item->setPen(QPen(QColor(r1, g1, b1, a1),width));
            item->setBrush( QColor(r2, g2, b2, a2));
            item->setMyShape(QColor(r1, g1, b1, a1), QColor(r2, g2, b2, a2), width);
            item->resizeTo(SizeHandleRect::LeftTop,QPointF(x1-a/2,y1-b/2));
            item->resizeTo( SizeHandleRect::RightBottom,QPointF(x1+a/2,y1+b/2));
            item->setRotation(angle);
            this->addItem(item);
            item_container.append(item);
            item_container.at(id);
        }
    }
    file.close();
}

  void IndoorScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
   QPointF pos= event->scenePos();
   QTransform transform;
   QGraphicsItem *clickItem = this->itemAt(pos,transform);
   if(clickItem==nullptr){
   CPoint temp(pos.x(),pos.y());
   if(m_startendVec.size()==0){
       startItem->setPos(pos);
       this->addItem(startItem);
       m_startendVec.push_back(temp);
   }else{
       if(m_startendVec.size()==1){
           endItem->setPos(pos);
           this->addItem(endItem);
           m_startendVec.push_back(temp);
       }
   }
   if(m_startendVec.size()==2){
       drawPath();
       m_startendVec.clear();
   }
}
}

  void IndoorScene::initAstar(){
      m_astar.cbowyer.ClearBowyerWatson();
      m_astar.cbowyer.CreateHelperPoint(CPoint(-500,-400),CPoint(-500,400),CPoint(500,400),CPoint(500,-400));
      BwFile file;
      QString str = "indoorData.txt";
      file.readFile(str);
      int rowCount = file.getRow();
      qDebug() << "row" << rowCount <<endl;
      QString *buffer = file.getBuffer();
      for(int i = 0;i < rowCount;i++){
          QStringList list = buffer[i].split(' ');
          float x = list.at(0).toFloat();
          float y = list.at(1).toFloat();
          int flag = list.at(2).toInt();
          m_astar.cbowyer.AddNewPoint(CPoint(x,y),flag);
    }
      m_astar.cbowyer.UpdateNewPoint();
      m_astar.cbowyer.DelCommoooonline();
      m_astar.cbowyer.popArray();
  }

  void IndoorScene::drawPath(){
      CPoint start = m_startendVec[0];
      CPoint end = m_startendVec[1];
      list<CPoint*> path = m_astar.GetPath(start,end);
      QVector<QPoint> pathVec;
      list<CPoint*>::iterator it = path.begin();
     while(it!=path.end()){
          qDebug()<<"hehe" << QPoint((*it)->x,(*it)->y)<<endl;
          pathVec.push_back(QPoint((*it)->x,(*it)->y));
          it++;
      }
      Route *planRoute = new Route(pathVec);
      this->addItem(planRoute);
  }
  void IndoorScene::initScene(){
     QVector< QVector<QPointF> > obstacle = m_astar.cbowyer.m_obstacle;
     for(int i = 0;i < obstacle.size();i++){
        QGraphicsPolygonItem *poly=new QGraphicsPolygonItem();
        QPolygonF polygon;
         for(int j = 0;j<obstacle[i].size();j++){
             polygon<< obstacle[i][j];
         }
         poly->setPolygon(polygon);
         poly->setBrush(QColor(40,218,76,70));
         poly->setZValue(70);
         this->addItem(poly);
  }
}





