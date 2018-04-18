#include "mapscene.h"
#include <QGraphicsSceneMouseEvent>
MapScene::MapScene(QObject *parent):QGraphicsScene(parent)
{
}


void MapScene :: openFile()
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

  void MapScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
   QPointF pos= event->scenePos();
   QTransform transform;
   QGraphicsItem *clickItem = this->itemAt(pos,transform);
   if(clickItem!=nullptr){
       m_indoorWin.show();
   }
}

