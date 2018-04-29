#include "mapdrawing.h"
#include "ui_mapdrawing.h"
#include "drawscene.h"
#include <QFileDialog>
#include <QtGui/QPainter>
#include <QPainter>
#include <QPen>
#include "drawobj.h"
#include <QMap>

#define MAX 100
int scaleLevel = 0;

MapDrawing::MapDrawing(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MapDrawing)
{
    ui->setupUi(this);
    setMap();
    m_newroute = nullptr;
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    setPalette(palette);
    setAutoFillBackground(true);


    //QGraphicsView *view =new QGraphicsView();
    view= new LoMoView();
//    widget->setLayout(ui->horizontalLayout_2);
//    ui->horizontalLayout_2->addWidget(view);

    // view->setFixedSize(1100,600);
    m_scene = new DrawScene();

    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   // ui->horizontalLayout_2->setAlignment(Qt::AlignCenter);
    view->setScene(m_scene);
   // m_scene->setSceneRect(-1320/2,-580/2,1320,580);
    m_scene->setSceneRect(-view->rect().width()/2,-view->rect().height()/2,view->rect().width(),view->rect().height());
   // m_scene->setSceneRect(0,0,view->rect().width(),view->rect().height());
    //创建新图元实验用，用以保存和
    //  QGraphicsRectItem  *rect=m_scene->addRect(QRectF(0,0,100,100));
    //  rect->setBrush(QBrush(Qt::Dense4Pattern));
    //m_scene->drawGridBackground(50);
    view->show();
    initToolBar();

    QWidget *widget =new QWidget();
    setCentralWidget(widget);


    QHBoxLayout *hor1=new QHBoxLayout;
    hor1->setAlignment(Qt::AlignCenter);
    hor1->setContentsMargins(10,10,10,10);
    hor1->setSpacing(0);
    widget->setLayout(hor1);

    QVBoxLayout *vn0=new QVBoxLayout;
    vn0->setAlignment(Qt::AlignLeft);
    vn0->setAlignment(Qt::AlignTop);
    vn0->setSpacing(15);
    vn0->setContentsMargins(0,10,0,0);


    QVBoxLayout *vn1=new QVBoxLayout();
    vn1->setAlignment(Qt::AlignLeft);
    vn1->setSpacing(10);
    scenelocate =new QLabel();
    scenelocate->setText(QStringLiteral("场景坐标"));
    scenelocate->setStyleSheet("font-size: 13px;");
    QHBoxLayout *hn3=new QHBoxLayout();
    hn3->setSpacing(10);
    sceneX =new QLabel();
    sceneX->setText(QStringLiteral("场景X坐标"));
    sceneX->setStyleSheet("font-size: 13px;");
    sceneY =new QLabel();
    sceneY->setText(QStringLiteral("场景Y坐标"));
    sceneY->setStyleSheet("font-size: 13px;");
    connect(view , SIGNAL(xlabel(double)) , this, SLOT(setscenexlabelvalue(double)));
    connect(view , SIGNAL(ylabel(double)) , this, SLOT(setsceneylabelvalue(double)));

    hn3->addWidget(sceneX);
    hn3->addWidget(sceneY);
    vn1->addWidget(scenelocate);
    vn1->addLayout(hn3);

    QVBoxLayout *vn2=new QVBoxLayout();
    vn2->setAlignment(Qt::AlignLeft);
    vn2->setSpacing(10);
    Maplocate =new QLabel();
    Maplocate->setText(QStringLiteral("地图坐标"));
    Maplocate->setStyleSheet("font-size: 13px;");
    QHBoxLayout *hn4=new QHBoxLayout();
    hn4->setSpacing(10);
    MapX =new QLabel();
    MapX->setText(QStringLiteral("地图X坐标"));
    MapX->setStyleSheet("font-size: 13px;");
    MapY =new QLabel();
    MapY->setText(QStringLiteral("地图Y坐标"));
    MapY->setStyleSheet("font-size: 13px;");
    connect(view , SIGNAL(mapxlabel(double)) , this, SLOT(setmapxlabelvalue(double)));
    connect(view , SIGNAL(mapylabel(double)) , this, SLOT(setmapylabelvalue(double)));
    hn4->addWidget(MapX);
    hn4->addWidget(MapY);
    vn2->addWidget(Maplocate);
    vn2->addLayout(hn4);

    QVBoxLayout *vn3=new QVBoxLayout;
    vn3->setAlignment(Qt::AlignLeft);
    vn3->setSpacing(10);
    bilichi1 =new QLabel();
    bilichi1->setText(QStringLiteral("比例尺:"));
    bilichi1->setStyleSheet("font-size: 13px;");
    QVBoxLayout *hnn1= new QVBoxLayout();
    hnn1->setSpacing(5);
    hnn1->setAlignment(Qt::AlignLeft);
    bilichixiangsu = new QLabel();
    bilichixiangsu->setPixmap(QPixmap(":/new/images/50pxbilichi.png"));
    bilichiValue = new QLabel();
    bilichiValue->setText(QStringLiteral("50Px=5米"));
    bilichiValue->setStyleSheet("font-size: 13px;");
    connect(view , SIGNAL(bilichi(double)) , this, SLOT(setbililabelvalue(double)));
    hnn1->addWidget(bilichixiangsu);
    hnn1->addWidget(bilichiValue);
    vn3->addWidget(bilichi1);
    vn3->addLayout(hnn1);

    vn0->addLayout(vn1);
    vn0->addLayout(vn2);
    vn0->addLayout(vn3);


    //QWidget *widget1=new QWidget;
    girdwidget=new GirdWidget();
    girdwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


  //  QHBoxLayout *hn8=new QHBoxLayout;
   // hn8->setContentsMargins(40,20,0,0);
   // hn8->addWidget(view);
  //  girdwidget->setLayout(hn8);
    //girdwidget->h1->addLayout(hn8);
    //this->paintOnWidget(girdwidget);
    girdwidget->h1->addWidget(view);
   // view->translate(100,100);
    hor1->addLayout(vn0,1);
    hor1->addWidget(girdwidget,6);
}

MapDrawing::~MapDrawing()
{
    delete ui;
}


//void MapDrawing::paintOnWidget(QWidget *w) {
//    QPainter painter(w);
//    QFontMetrics metrics = painter.fontMetrics();
//    int textHeight = metrics.ascent() + metrics.descent();

//    int leftWidth = metrics.width(tr("9000")) + 5;
//    int rightWidth = metrics.width(tr("(日)"));
//    int width = w->size().width() - leftWidth - rightWidth;
//    int height = w->size().height() - 3 * textHeight;

//    // 绘制外框
//    painter.drawRect(0, 0, w->size().width() -1, w->size().height() - 1);
//    //　移动坐标系
//    //painter.translate(inset * 2, ui->yearWidget->size().height() - inset);
//    painter.translate(leftWidth, 1.75 * textHeight + height);

//    int totalCount = 9000; // 默认每年收入9000件衣服
//    int count = 12 ;        // 分成10成
////    float deltaX = width / 12.0f;         // x坐标上每分的宽度
////    float deltaY = (float)height / count; // y坐标上每分的宽度
//    int deltaX = 50;
//    int deltaY = 50;


//    // 画横坐标
//    painter.drawLine(0, 0, width, 0);
//    for (int i = 1; i <= 12; ++i) {
//        QString month = tr("%1月").arg(i);
//        int stringWidth = metrics.width(month);

//        // 绘制坐标刻度
//        painter.drawLine(deltaX * i, 0, deltaX * i, 4);

//        // 绘制坐标处的月
//        int monthX = deltaX * (i - 1) + ((deltaX - stringWidth) / 2);
//        painter.drawText(monthX, textHeight, month);
//    }

//    // 画纵坐标
//    painter.drawLine(0, 0, 0, -height);
//    painter.drawText(-metrics.width(tr("(件)")),
//                     -(deltaY * count + textHeight / 2 + metrics.descent()),
//                     tr("(件)"));
//    for (int i = 1; i <= count; ++i) {
//        QString value = QString("%1").arg(i * totalCount / count);
//        int stringWidth = metrics.width(value);

//        // 绘制坐标刻度
//        painter.drawLine(-4, -i * deltaY, 0, -i * deltaY);

//        // 绘制坐标值
//        //painter.drawText(-stringWidth - 4, -i * deltaY + stringHeight / 2, value);
//        painter.drawText(-stringWidth - 4, -(deltaY * i + textHeight / 2 - metrics.ascent()), value);
//    }
//}


void MapDrawing :: setscenexlabelvalue(double x)
{
    sceneX->setText(QString::number(x));
}
void MapDrawing :: setsceneylabelvalue(double y)
{
    sceneY->setText(QString::number(y));
}
void MapDrawing :: setmapxlabelvalue(double x)
{
    MapX->setText(QString::number(x));
}
void MapDrawing :: setmapylabelvalue(double y)
{
    MapY->setText(QString::number(y));
}
void MapDrawing :: setbililabelvalue(double bili)
{
    bilichiValue->setText(QStringLiteral("50px=")+QString::number(bili)+QStringLiteral("米"));
}



void MapDrawing::keyPressEvent(QKeyEvent *k)
{
    if (k->modifiers() == Qt::ShiftModifier)
    {
        emit change_straight(true);
    }
}

void MapDrawing::keyReleaseEvent(QKeyEvent *k)
{
    double *up = new double[7]{1.0,1.2,1.5,1.75,2.0,2.5,3.0};
    double *down = new double[7]{1.0,0.8,0.6,0.6,0.4,0.6,0.6};

    if (k->key() == Qt::Key_Shift)
    {
       emit change_straight(false);
    }else if(k->key()==Qt::Key_Up){
        if(scaleLevel>=-5&&scaleLevel<0) //鼠标滚轮向外
        {
            view->resetTransform();
            view->scale(down[-scaleLevel],down[-scaleLevel]);
            scaleLevel++;
            /*
            int numSteps = event->delta()/15/8;
            sc = pow(scale,numSteps);
            qDebug()<<"sc:"<<sc<<endl;
            view->scale(sc,sc);
            */

        // qDebug()<<"matrix.x:"<<view->matrix().m11()<<endl<<"matrix.y:"<<view->matrix().m22()<<endl;
        }
        else if(scaleLevel>=0&&scaleLevel<=5)
        {
            view->resetTransform();
            view->scale(up[scaleLevel],up[scaleLevel]);
            scaleLevel++;
        }

    }else if(k->key()==Qt::Key_Down){
        if(scaleLevel>0&&scaleLevel<=5)  //鼠标滚轮向内
        {
            view->resetTransform();
            view->scale(up[scaleLevel],up[scaleLevel]);
            scaleLevel--;
            /*
            int numSteps = event->delta()/15/8;

            sc= pow(1/scale, - numSteps);
            qDebug()<<"sc:"<<sc<<endl;
            view ->scale(sc,sc);*/
            // qDebug()<<"matrix.x:"<<view->matrix().m11()<<endl<<"matrix.y:"<<view->matrix().m22()<<endl;
        }
        else if(scaleLevel<=0&&scaleLevel>=-5)
        {
            view->resetTransform();
            view->scale(down[-scaleLevel],down[-scaleLevel]);
            scaleLevel--;
        }
    }
     qDebug()<<"scaleLevel"<<scaleLevel<<endl;
}


/*
 * 槽函数，保存scence中的Item
 * */


void MapDrawing::color_SLOT()
{
    QColor c = QColorDialog::getColor(Qt::red);
    emit color_change(c);
}

void MapDrawing::brush_SLOT()
{
    QColor c = QColorDialog::getColor(Qt::transparent);
    emit brush_change(c);
}

void MapDrawing::change_widthLabel(int w)
{
    widthLabel->setText("Size: " + QString::number(w));
}

void MapDrawing::change_alphaLabel(int w)
{
    alphaLabel->setText("Alpha: " + QString::number(w) + "%");
}
void MapDrawing::addShape()
{
    if ( sender() == circle_act )
        DrawTool::c_drawShape = ellipse;
    if ( sender() == pie_act )
        DrawTool::c_drawShape = pie;
    if ( sender() == rect_act )
        DrawTool::c_drawShape = rectangle;
    if ( sender() == select_act )
        DrawTool::c_drawShape = selection;
    if (sender() == rotation_act )
        DrawTool::c_drawShape = rotation;
    if ( sender() == line_act )
        DrawTool::c_drawShape = line;
    if (sender() == bezier_act )
        DrawTool::c_drawShape = arc;

}

void MapDrawing::updateUI()
{
    if ( DrawTool::c_drawShape == ellipse )
        circle_act->setChecked(true);
    if ( DrawTool::c_drawShape == pie )
        pie_act->setChecked(true);
    else if ( DrawTool::c_drawShape == rectangle )
        rect_act->setChecked(true);
    else if (DrawTool::c_drawShape == selection )
        select_act->setChecked(true);
    else if ( DrawTool::c_drawShape == rotation )
        rotation_act->setChecked(true);
    else if ( DrawTool::c_drawShape == line )
        line_act->setChecked(true);
    else if ( DrawTool::c_drawShape == arc )
        bezier_act->setChecked(true);

    if (m_scene->selectedItems().count() > 0 ){
        bringtofont_act->setEnabled(true);
        sendtoback_act->setEnabled(true);
    }else{
        bringtofont_act->setEnabled(false);
        sendtoback_act->setEnabled(false);
    }
}

void MapDrawing::on_actionBringToFront_triggered()
{

    if (m_scene->selectedItems().isEmpty())
        return;
    QGraphicsItem *selectedItem = m_scene->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() >= zValue && item->type() == GraphicsItem::Type)
            zValue = item->zValue() + 0.1;
    }
    selectedItem->setZValue(zValue);


    //QGraphicsItemGroup test

    QList<QGraphicsItem *> selectedItems = m_scene->selectedItems();

    QGraphicsItemGroup * group = new QGraphicsItemGroup();
    foreach (QGraphicsItem *item, selectedItems) {
        item->setSelected(false);
        group->addToGroup(item);
    }


//    group->setFlag(QGraphicsItem::ItemIsMovable, true);
//    group->setFlag(QGraphicsItem::ItemIsSelectable, true);
//    group->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    GraphicsItemGroup * proxy = new GraphicsItemGroup(group,NULL );
    m_scene->addItem(proxy);
    proxy->setSelected(true);


}

void MapDrawing::on_actionSendToBack_triggered()
{

    if (m_scene->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = m_scene->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() <= zValue && item->type() == GraphicsItem::Type)
            zValue = item->zValue() - 0.1;
    }
    selectedItem->setZValue(zValue);

}

void MapDrawing::on_actionDelete_triggered()
{
    if (m_scene->selectedItems().isEmpty())
        return;

    QList<QGraphicsItem *> overlapItems = m_scene->selectedItems();

    foreach (QGraphicsItem *item, overlapItems) {

        m_scene->removeItem(item);
        int index = 0;
        for(GraphicsItem* i:m_scene->item_container){
            if(i->x()== item->x()&&i->y()==item->y()){
                break;
            }
            index++;
        }
        m_scene->item_container.removeAt(index);
        delete item;
    }

}

//void MapDrawing::wheelEvent(QWheelEvent *event)
//{
//    /*
//    int x = view->scene()->width();
//    int y = view->scene()->height();
//    double scale =1.25;
//    double *up = new double[7]{1.0,1.2,1.5,1.75,2.0,2.5,3.0};
//    double *down = new double[7]{1.0,0.8,0.6,0.4,0.32,0.28,0.28};

//    scaleLevel= scaleLevel==6?5:(scaleLevel==-6?-5:scaleLevel);
//    //qDebug()<<"sceneRect.x:"<<x<<endl<<"sceneRect.y:"<<y<<endl;
//    qreal sc;
//    if(event->delta()>0&&scaleLevel>=-5&&scaleLevel<0) //鼠标滚轮向外
//    {
//        view->resetTransform();
//        view->scale(down[-scaleLevel],down[-scaleLevel]);
//        scaleLevel++;


//    // qDebug()<<"matrix.x:"<<view->matrix().m11()<<endl<<"matrix.y:"<<view->matrix().m22()<<endl;
//    }
//    else if(event->delta()<=0&&scaleLevel>0&&scaleLevel<=5)  //鼠标滚轮向内
//    {
//        view->resetTransform();
//        view->scale(up[scaleLevel],up[scaleLevel]);
//        scaleLevel--;

//        // qDebug()<<"matrix.x:"<<view->matrix().m11()<<endl<<"matrix.y:"<<view->matrix().m22()<<endl;
//    }
//    else if(event->delta()>0&&scaleLevel>=0&&scaleLevel<=5)
//    {
//        view->resetTransform();
//        view->scale(up[scaleLevel],up[scaleLevel]);
//        scaleLevel++;
//    }
//    else if(event->delta()<0&&scaleLevel<=0&&scaleLevel>=-5)
//    {
//        view->resetTransform();
//        view->scale(down[-scaleLevel],down[-scaleLevel]);
//        scaleLevel--;
//    }
//    double r = view->matrix().m11();
//    qDebug()<<"scaleLevel"<<scaleLevel<<endl;
//    //m_scene->drawGridBackground(beishu*50);

//    */

//    qreal sc;
//            if(event->delta()>0) //鼠标滚轮向外
//            {
//            int numSteps = event->delta()/15/8;
//             sc = pow(1.01,numSteps);
//             view->scale(sc,sc);
//            }
//            if(event->delta()<0)  //鼠标滚轮向内
//            {
//             int numSteps = event->delta()/15/8;
//             sc= pow(1/1.01, - numSteps);

//             view ->scale(sc,sc);
//            }
//}


void MapDrawing::initToolBar()
{
    QToolBar *shapeBar= new QToolBar("Shape");
    //shapeBar->setAllowedAreas(Qt::ToolBarAreas );
   // shapeBar->allowedAreas(Qt::LeftToolBarArea);
    QActionGroup *shapeGroup = new QActionGroup(shapeBar);

    open_act = new QAction(QIcon(":/new/images/open.png"),"Open A Map", shapeBar);
    open_act->setCheckable(true);
    //save_act->setChecked(true);
    shapeGroup->addAction(open_act);
    shapeBar->addAction(open_act);

    save_act = new QAction(QIcon(":/new/images/save-5.png"),"Save the Map", shapeBar);
    save_act->setCheckable(true);
    //save_act->setChecked(true);
    shapeGroup->addAction(save_act);
    shapeBar->addAction(save_act);

    select_act = new QAction(QIcon(":/new/images/pointer.png"),"Select A Item", shapeBar);
    select_act->setCheckable(true);
    select_act->setChecked(true);
    shapeGroup->addAction(select_act);
    shapeBar->addAction(select_act);

    delete_act = new QAction(QIcon(":/new/images/delete.png"), "Delete A Item", shapeBar);
    delete_act->setShortcut(tr("Delete"));
    delete_act->setCheckable(true);
    shapeGroup->addAction(delete_act);
    shapeBar->addAction(delete_act);

    line_act = new QAction(QIcon(":/new/images/linecolor.png"), "Draw A Line", shapeBar);
    line_act->setCheckable(true);
    shapeGroup->addAction(line_act);
    shapeBar->addAction(line_act);

    bezier_act = new QAction(QIcon(":/new/images/bezier.svg"), "Draw A Bezier", shapeBar);
    bezier_act->setCheckable(true);
    shapeGroup->addAction(bezier_act);
    shapeBar->addAction(bezier_act);

    pie_act = new QAction(QIcon(":/new/images/pie.png"), "Draw A Bezier", shapeBar);
    pie_act->setCheckable(true);
    shapeGroup->addAction(pie_act);
    shapeBar->addAction(pie_act);

    circle_act = new QAction(QIcon(":/new/images/circle.png"), "Draw A Circle", shapeBar);
    circle_act->setCheckable(true);
    shapeGroup->addAction(circle_act);
    shapeBar->addAction(circle_act);

    rect_act = new QAction(QIcon(":/new/images/rectangle.png"), "Draw A Rect", shapeBar);
    rect_act->setCheckable(true);
    shapeGroup->addAction(rect_act);
    shapeBar->addAction(rect_act);

    bringtofont_act = new QAction(QIcon(":/new/images/bringtofront.png"), "Bring this Item to Font", shapeBar);
    bringtofont_act->setCheckable(true);
    shapeGroup->addAction(bringtofont_act);
    shapeBar->addAction(bringtofont_act);

    sendtoback_act = new QAction(QIcon(":/new/images/sendtoback.png"), "Send this item to back", shapeBar);
    sendtoback_act->setCheckable(true);
    shapeGroup->addAction(sendtoback_act);
    shapeBar->addAction(sendtoback_act);

    rotation_act = new QAction(QIcon(":/new/images/rotation.png"), "Ratate A Item ", shapeBar);
    rotation_act->setCheckable(true);
    shapeGroup->addAction(rotation_act);
    shapeBar->addAction(rotation_act);

    brush_act = new QAction(QIcon(":/new/images/brush.png"), "Set Item Brush ", shapeBar);
    brush_act->setShortcut(tr("Ctrl+B"));
    brush_act->setCheckable(true);
    shapeGroup->addAction(brush_act);
    shapeBar->addAction(brush_act);

    color_act = new QAction(QIcon(":/new/images/bound.png"), "Set Bound Color ", shapeBar);
    color_act->setShortcut(tr("Ctrl+C"));
    color_act->setCheckable(true);
    shapeGroup->addAction(color_act);
    shapeBar->addAction(color_act);

//    drawPath_act = new QAction(QIcon(":/new/images/way.png"), "Set Bound Color ", shapeBar);
//    //drawPath_act->setShortcut(tr("Ctrl+C"));
//    drawPath_act->setCheckable(true);
//    shapeGroup->addAction(drawPath_act);
//    shapeBar->addAction(drawPath_act);

/*
    back_act = new QAction(QIcon(":/image/bold.png"),"set the BackGround", shapeBar);
    back_act->setCheckable(true);
    save_act->setChecked(true);
    shapeGroup->addAction(back_act);
    shapeBar->addAction(back_act);
    shapeBar->setAllowedAreas(Qt::LeftToolBarArea);
*/
    this->addToolBar(shapeBar);

    QToolBar *operatorBar= new QToolBar("Operator");
    operatorBar->setAllowedAreas(Qt::LeftToolBarArea);

    slider1 = new QSlider();
    slider1->setOrientation(Qt::Horizontal);
    slider1->setFixedSize(150,20);
    slider1->setRange(1,10);
    slider1->setValue(1);
    operatorBar->addWidget(slider1);
    widthLabel = new QLabel("Size: 1");
    operatorBar->addWidget(widthLabel);

    slider2 = new QSlider();
    slider2->setOrientation(Qt::Horizontal);
    slider2->setFixedSize(150,20);
    slider2->setRange(1,100);
    slider2->setValue(100);
    operatorBar->addWidget(slider2);
    alphaLabel = new QLabel("Alpha: 100%");
    operatorBar->addWidget(alphaLabel);


    this->addToolBar(operatorBar);
    connect(open_act,SIGNAL(triggered()),m_scene,SLOT(open_file()));
    connect(save_act,SIGNAL(triggered()),m_scene,SLOT(save_file()));
    connect(select_act,SIGNAL(triggered()),this,SLOT(addShape()));
    connect(delete_act,SIGNAL(triggered()),this,SLOT(on_actionDelete_triggered()));
    connect(line_act,SIGNAL(triggered()),this,SLOT(addShape()));
    connect(bezier_act,SIGNAL(triggered()),this,SLOT(addShape()));
    connect(pie_act,SIGNAL(triggered()),this,SLOT(addShape()));
    connect(circle_act,SIGNAL(triggered()),this,SLOT(addShape()));
    connect(rect_act,SIGNAL(triggered()),this,SLOT(addShape()));
    connect(bringtofont_act,SIGNAL(triggered()),this,SLOT(on_actionBringToFront_triggered()));
    connect(sendtoback_act,SIGNAL(triggered()),this,SLOT(on_actionSendToBack_triggered()));
    connect(rotation_act,SIGNAL(triggered()),this,SLOT(addShape()));
    connect(brush_act,SIGNAL(triggered()),this,SLOT(brush_SLOT()));
    connect(color_act,SIGNAL(triggered()),this,SLOT(color_SLOT()));

    //connect(drawPath_act,SIGNAL(triggered()),this,SLOT(addWin()));

    //工具条栏的连接函数设置结束
    connect(slider1, SIGNAL(valueChanged(int)), m_scene, SLOT(set_width(int)));
    connect(slider1, SIGNAL(valueChanged(int)), this, SLOT(change_widthLabel(int)));
    connect(slider2, SIGNAL(valueChanged(int)), m_scene, SLOT(set_alpha(int)));
    connect(slider2, SIGNAL(valueChanged(int)), this, SLOT(change_alphaLabel(int)));


    /////////////////////m_scene交互信号槽/////////////////////////////
    connect(this, SIGNAL(color_change(QColor)), m_scene, SLOT(set_color(QColor)));
    connect(this, SIGNAL(brush_change(QColor)), m_scene, SLOT(set_brush(QColor)));
    connect(this, SIGNAL(change_straight(bool)), m_scene, SLOT(set_straight(bool)));

    connect(&m_timer,SIGNAL(timeout()),this,SLOT(updateUI()));

    m_timer.start(100);
}

void MapDrawing::getMapPath(int beginId,int endId){
    MyFile *qtFile1 = new MyFile();
    QString filename1 = "MapNode.txt";
    qtFile1->readFile(filename1);
    int vexNum = qtFile1->getRow();
    int vexs[vexNum];
    QString* strs = qtFile1->getBuffer();
    for(int i = 0;i <vexNum;i++){
           QStringList list = strs[i].split(" ");
           QPoint p(list.at(1).toDouble(),list.at(2).toDouble());
           m_allpoints.push_back(p);
           vexs[i]=list.at(0).toInt();
    }
  //将邻接表读出
    int prev[MAX] = {0};
    int dist[MAX] = {0};
    MyFile *qtFile2 = new MyFile();
    QString filename2 = "MapEdge.txt";
    qtFile2->readFile(filename2);
    int edgeNum = qtFile2->getRow();
     qDebug()<<edgeNum;
     EData *edges[edgeNum];
    QString* strs2 = qtFile2->getBuffer();
    for(int i = 0;i <edgeNum;i++){
        QStringList list2 = strs2[i].split(" ");
         int s = list2.at(0).toInt();
         int e = list2.at(1).toInt();
         int w = list2.at(2).toInt();
        // qDebug()<<s <<e<< w;
         edges[i] = new EData(s,e,w);
        // qDebug() <<edges[i]->weight;
    }
   DijkstraFindPath *dij = new DijkstraFindPath(vexs,vexNum,edges,edgeNum);
   QStack<int> st = dij->dijkstra(beginId,endId,prev,dist);
   //qDebug() << st.size();
       m_pathpoints.clear();
       //qDebug()<<m_allpoints[9];
       while(st.size()){
       m_pathpoints.push_back(m_allpoints[st.pop()]);
}
}


void MapDrawing::move(){
    m_moveball = new MoveItem();
    QTimeLine *timer = new QTimeLine(15000);
    timer->setFrameRange(0,100);
    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
    animation->setItem(m_moveball);
    animation->setTimeLine(timer);
    for(int i = 0; i < m_pathpoints.size(); ++i)
    animation->setPosAt(i / 50.0, QPointF(m_pathpoints[i]));
    timer->start();
}


void MapDrawing::drawPath(userPoint &data){
    qDebug()<<data.start;
    int start = m_map[data.start];
    int end = m_map[data.end];
    getMapPath(start,end);
   // m_route = new Route(m_pathpoints);
    m_newroute = new newRoute(m_pathpoints);
    m_scene->addItem(m_newroute);
   // m_scene->addItem(m_route);
    // update();
   // move();
    //m_scene->addItem(m_moveball);
}

void MapDrawing::addWin(){
    if(m_newroute!=nullptr)
    m_scene->removeItem(m_newroute);
    m_userPath = new userPath;
    m_userPath->show();
    connect(m_userPath,SIGNAL(userPointSignal(userPoint&)),this,SLOT(drawPath(userPoint&)));
}


void MapDrawing::setMap(){
   m_map.insert("243",0);
   m_map.insert("240",1);
   m_map.insert("229",2);
}




