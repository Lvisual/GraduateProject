/****************************************************************************

 This file is part of the GLC-lib library.
 Copyright (C) 2005-2008 Laurent Ribon (laumaya@users.sourceforge.net)
 http://glc-lib.sourceforge.net

 GLC-lib is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 GLC-lib is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with GLC-lib; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*****************************************************************************/

#include <QtDebug>
#include <QFile>
#include <QGLContext>

#include <GLC_UserInput>
#include <GLC_Context>
#include <GLC_Vector3d>
#include <GLC_Exception>
#include "glwidget.h"

// For VSYNC problem under Mac OS X
#if defined(Q_OS_MAC)
#include <OpenGL.h>
#endif

#define speed 500

QVector<QPoint> vFence={
    QPoint(17500,-20000),
    QPoint(35000,10000),
    QPoint(60000,10000),
    QPoint(60000,-30000),
    QPoint(35000,-40000)
};

GLfloatVector polyvertices =
{
    17500,7000,-20000,
    35000,7000,10000,
    60000,7000,10000,
    60000,7000,-30000,
    35000,7000,-40000
};
GLfloatVector normals =
{
    0.0,1.0,0.0,
    0.0,1.0,0.0,
    0.0,1.0,0.0,
    0.0,1.0,0.0,
    0.0,1.0,0.0
};

GLWidget::GLWidget(QWidget *p_parent)
: QGLWidget(new QGLContext(QGLFormat(QGL::SampleBuffers)), p_parent)
, m_MotionTimer()
, m_Light()
, m_GlView()
, m_TreeId()
, m_MoverController()
, m_Rectangle(GLC_Factory::instance()->createRectangle(GLC_Point3d(0.0,4000,0.0),GLC_Vector3d(0.0,1.0,0.0),140000,100000))
, m_PathCollection()
, m_Sphere()
, m_Polygon()
, elecFence(vFence,5)
{
//////////////////////////// GLC specific///////////////////////////////////////
    connect(&m_GlView, SIGNAL(updateOpenGL()), this, SLOT(updateGL()));
//    m_Light.setPosition(15.0, 15.0, 0.0);
//    m_Light.setAmbientColor(Qt::black);

//    m_GlView.cameraHandle()->setDefaultUpVector(glc::Z_AXIS);
//    m_GlView.cameraHandle()->setIsoView();


	QColor repColor;
//	repColor.setRgbF(1.0, 0.11372, 0.11372, 1.0);
    repColor.setRgbF(0.11372,1.0 , 0.11372, 1.0);
    m_MoverController= GLC_Factory::instance()->createDefaultMoverController(repColor, &m_GlView);
    m_Rectangle.geomAt(0)->replaceMasterMaterial(new GLC_Material(QColor(Qt::red)));

    vertices
//            <<GLC_Vector3d(-60000,500,-36000)
//           <<GLC_Vector3d(-60000,500,-10000)
//          <<GLC_Vector3d(-4000,500,-10000)
//         <<GLC_Vector3d(-4000,500,-44000)
//        <<GLC_Vector3d(4000,500,-44000)
       <<GLC_Vector3d(4000,500,-10000)
      <<GLC_Vector3d(63000,500,-10000)
     <<GLC_Vector3d(63000,500,-36000);
//    vertices
//            <<GLC_Vector3d(100.0,4000.0,-100.0)
//           <<GLC_Vector3d(35000.0,4000.0,-40000.0)
//           <<GLC_Vector3d(35000.0,4000.0,-100.0)
//          <<GLC_Vector3d(60000.0,4000.0,-100.0)
//          <<GLC_Vector3d(60000.0,4000.0,-40000.0);
	// Create objects to display
    CreateScene();
//    ComputePath();
//    SetSphere();

//    connect(&m_MotionTimer,SIGNAL(timeout()),this,SLOT(MoveObject()));

//////////////////////////End GLC specific/////////////////////////////////////
}

GLWidget::~GLWidget()
{
//    delete mypath;
}

void GLWidget::initializeGL()
{

	// For VSYNC problem under Mac OS X
	#if defined(Q_OS_MAC)
	const GLint swapInterval = 1;
	CGLSetParameter(CGLGetCurrentContext(), kCGLCPSwapInterval, &swapInterval);
	#endif
//    initializeOpenGLFunctions();

	// OpenGL initialisation
    m_GlView.initGl();
    m_GlView.loadBackGroundImage("E:/3DMap/MyModel/background.png");

    m_Light.setTwoSided(true);
    m_Light.setPosition(1.0, 1.0, 1.0);

	// Reframe the scene on the loaded mesh
    m_GlView.reframe(m_World.boundingBox());
    m_GlView.cameraHandle()->rotateAroundTarget(glc::X_AXIS,-glc::PI/4);
    m_GlView.cameraHandle()->setDistEyeTarget(160000);
//    m_MotionTimer.start(30);
//    MoveAlongPath();


}

void GLWidget::paintGL()
{
    try
    {
    // Clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Load identity matrix
    GLC_Context::current()->glcLoadIdentity();
//    glLoadIdentity();

	// Calculate camera depth of view
    m_GlView.setDistMinAndMax(m_World.boundingBox());

	// define the light
	m_Light.glExecute();

	// define view matrix
	m_GlView.glExecuteCam();

//    glEnable(GL_MULTISAMPLE);
    // Render the scene
    m_World.render(0, glc::ShadingFlag);
    m_World.render(0, glc::TransparentRenderFlag);
    m_World.render(1, glc::ShadingFlag);
//    m_World.render(1, glc::TransparentRenderFlag);

    m_PathCollection.render(0,glc::ShadingFlag);

    m_Sphere.render();

    m_Polygon.render(0,glc::TransparentRenderFlag);
//    glDisable(GL_MULTISAMPLE);


//    m_Rectangle.render();

	// Display UI Info (orbit circle)
//    m_MoverController.drawActiveMoverRep();
    }
    catch (GLC_Exception &e)
    {
        qDebug() << e.what();
    }
}

void GLWidget::resizeGL(int width, int height)
{
//////////////////////////// GLC specific///////////////////////////////////////
	m_GlView.setWinGLSize(width, height);	// Compute window aspect ratio
//////////////////////////End GLC specific/////////////////////////////////////

}

// Create GLC_Object to display
void GLWidget::CreateScene()
{
	// Load mesh from a file
//    QFile manFile(":a.obj");
//    QFile manFile("man.obj");
//    QFile manFile("E:/GLC_lib-master/src/examples/map/21A.3ds");
    QFile manFile("E:/3DMap/MyModel/21A.3ds");
    m_World= GLC_Factory::instance()->createWorldFromFile(manFile);

    m_World.rootOccurrence()->structInstance()->move(GLC_Matrix4x4(glc::X_AXIS,-glc::PI/2));
    m_World.rootOccurrence()->updateChildrenAbsoluteMatrix();
}

void GLWidget::ComputePath()
{
    QColor matBlue,matGreen;
    matBlue.setRgbF(0.5, 0.8, 1.0, 1.0);
    matGreen.setRgb(129,255,129);
//    matGreen.setHsl(80,240,182);
    GLC_Texture* cTex = new GLC_Texture(QImage("E:/3DMap/MyModel/circle.jpg"));
//    QVector<GLC_Vector3d> vertices;
//    vertices
//            <<GLC_Vector3d(100.0,4000.0,-100.0)
//           <<GLC_Vector3d(35000.0,4000.0,-40000.0)
//           <<GLC_Vector3d(35000.0,4000.0,-100.0)
//          <<GLC_Vector3d(60000.0,4000.0,-100.0)
//          <<GLC_Vector3d(60000.0,4000.0,-30000.0);
    GLC_3DViewInstance circle(GLC_Factory::instance()->createCylinder(
                                  1500,1));
//    circle.geomAt(0)->replaceMasterMaterial(new GLC_Material(matGreen));
//    circle.geomAt(0)->replaceMasterMaterial(new GLC_Material(QColor(Qt::green)));
    circle.geomAt(0)->replaceMasterMaterial(new GLC_Material(cTex));
    GLC_Matrix4x4 rot(glc::X_AXIS,-glc::PI/2);
    circle.multMatrix(rot);
    circle.translate(vertices[0]);
    m_PathCollection.add(circle);
    for(int i=1;i<vertices.length();++i)
    {
        GLC_Texture* pTexture = new GLC_Texture(QImage("E:/3DMap/MyModel/allright.jpg"));
        GLC_Texture* ccTex = new GLC_Texture(QImage("E:/3DMap/MyModel/circle.jpg"));
        circle = GLC_Factory::instance()->createCylinder(1500,1);
//        circle.geomAt(0)->replaceMasterMaterial(new GLC_Material(matGreen));
//        circle.geomAt(0)->replaceMasterMaterial(new GLC_Material(QColor(Qt::green)));
        circle.geomAt(0)->replaceMasterMaterial(new GLC_Material(ccTex));
        circle.multMatrix(GLC_Matrix4x4(glc::X_AXIS,-glc::PI/2));
        circle.translate(vertices[i]);
        m_PathCollection.add(circle);
        GLC_Vector3d v = vertices[i]-vertices[i-1];
        GLC_Vector3d n = v ^ glc::Y_AXIS;
        n = n.normalize();
        GLfloatVector points,p_normals,p_texels;
        GLC_Vector3d mid[4];
        p_normals = {
            0.0,1.0,0.0,
            0.0,1.0,0.0,
            0.0,1.0,0.0,
            0.0,1.0,0.0
        };
        mid[3] = vertices[i-1]-n*1500;
        mid[0] = vertices[i-1]+n*1500;
        mid[1] = vertices[i]+n*1500;
        mid[2] = vertices[i]-n*1500;
//        points<<mid[0].x()<<mid[0].y()<<mid[0].z();
        for(int j=0;j<4;j++)
            points<<mid[j].x()<<mid[j].y()<<mid[j].z();
        p_texels<<0.0<<0.0;
        p_texels<<v.length()*0.0001<<0.0;
        p_texels<<v.length()*0.0001<<1.0;
        p_texels<<0.0<<1.0;

        GLC_Mesh p_mesh;
        p_mesh.addVertice(points);
        p_mesh.addNormals(p_normals);
        p_mesh.addTexels(p_texels);
        GLC_Material *m = new GLC_Material(pTexture);
        IndexList index = {0,1,3,2};
        p_mesh.addTrianglesStrip(m,index);
        p_mesh.finish();
        GLC_3DViewInstance instance(p_mesh.clone());

//        instance.geomAt(0)->replaceMasterMaterial(new GLC_Material(pTexture));
        m_PathCollection.add(instance);
    }
}

void GLWidget::MakePath()
{
    QColor matBlue;
    matBlue.setRgbF(0.5, 0.8, 1.0, 1.0);
    GLC_3DViewInstance circle(GLC_Factory::instance()->createCylinder(
                                  1500,1));
    circle.geomAt(0)->replaceMasterMaterial(new GLC_Material(matBlue));
    GLC_Matrix4x4 rot(glc::X_AXIS,-glc::PI/2);
    circle.multMatrix(rot);
    circle.translate(vertices[0]);
    m_PathCollection.add(circle);
    for(int i=1;i<vertices.length();++i)
    {
//        GLC_Texture* pTexture = new GLC_Texture(QImage("E:/3DMap/MyModel/arrow.jpg"));
        circle = GLC_Factory::instance()->createCylinder(1500,1);
        circle.geomAt(0)->replaceMasterMaterial(new GLC_Material(matBlue));
        circle.multMatrix(GLC_Matrix4x4(glc::X_AXIS,-glc::PI/2));
        circle.translate(vertices[i]);
        m_PathCollection.add(circle);
        GLC_Vector3d v = vertices[i]-vertices[i-1];
        GLC_Vector3d p = (vertices[i]+vertices[i-1])*0.5;
        GLC_3DViewInstance instance(GLC_Factory::instance()->createRectangle(GLC_Point3d(0.0,0.0,0.0),
                                        glc::Y_AXIS,v.length(),3000));
        instance.geomAt(0)->replaceMasterMaterial(new GLC_Material(matBlue));
//        instance.geomAt(0)->replaceMasterMaterial(new GLC_Material(pTexture));
        double angle = v.angleWithVect(glc::X_AXIS);
        if(v.angleWithVect(glc::Z_AXIS) < glc::PI/2)
        {
            angle = -angle;
        }
        GLC_Matrix4x4 matRot(glc::Y_AXIS,angle);
        instance.multMatrix(matRot);
        instance.translate(p);
        m_PathCollection.add(instance);
    }
}

void GLWidget::MoveAlongPath()
{
    vi = 1;
    direction = vertices[vi]-vertices[vi-1];
    GLC_Vector3d mid = direction;
    unit = mid.normalize() * speed;
    record = GLC_Vector3d(0,0,0);
//    qDebug()<<record.length();
    connect(&m_MotionTimer,SIGNAL(timeout()),this,SLOT(MoveObject()));
}

void GLWidget::SetSphere()
{
    m_Sphere = GLC_Factory::instance()->createSphere(1500);
    m_Sphere.geomAt(0)->replaceMasterMaterial(new GLC_Material(Qt::red));
    m_Sphere.translate(vertices[0]);
    m_Sphere.translate(glc::Y_AXIS * 1500);
}

void GLWidget::Select(const int x, const int y)
{
    setAutoBufferSwap(false);
    GLC_uint SelectionID = m_GlView.renderAndSelect(x, y);
    setAutoBufferSwap(true);
    if(SelectionID != 0 && m_World.containsOccurrence(SelectionID))
    {
//        qDebug()<<"---------------------------------------";
//        qDebug()<<"SelectionID:   "<<SelectionID;
//        qDebug()<<"---------------------------------------";
//        m_World.unselectAll();
//        GLC_3DViewInstance instance(*m_World.collection()->instanceHandle(SelectionID));
//        instance.geomAt(0)->firstMaterial()->setAmbientColor(Qt::blue);
//        instance.geomAt(0)->firstMaterial()->setDiffuseColor(QColor::fromRgbF(0.5,0.8,1.0,0.2));
        m_World.unselectAll();
        m_World.select(SelectionID);
    }
    updateGL();
}

void GLWidget::mousePressEvent(QMouseEvent *e)
{

    lastMousePosition = e->pos();


    e->accept();
    if(e->buttons() & Qt::LeftButton)
    {
//        qDebug()<<"x: "<<e->pos().x()<<"   y: "<<e->pos().y();
        GLC_Point3d p = m_GlView.unproject(e->pos().x(),e->pos().y());
//        qDebug()<<"x: "<<p.x()<<" z: "<<p.z();
        emit coordinateMod(p.x(),p.z());
//        Select(e->x(), e->y());
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent * e)
{
//    qDebug()<<"x: "<<e->pos().x()<<"   y: "<<e->pos().y();
    if (m_MoverController.hasActiveMover())
	{
        m_MoverController.move(GLC_UserInput(e->x(), e->y()));
        m_GlView.setDistMinAndMax(m_World.boundingBox());
		updateGL();
	}

    if(e->buttons() & Qt::LeftButton)
    {
        int deltaX = e->x() - lastMousePosition.x();
        int deltaY = e->y() - lastMousePosition.y();
        GLC_Vector3d F_B = m_GlView.cameraHandle()->forward();
        F_B.setY(0);
        GLC_Vector3d L_R = -m_GlView.cameraHandle()->sideVector();
        F_B.normalize();
        L_R.normalize();
        cameraTrans = F_B * deltaY + L_R * deltaX;
        m_GlView.cameraHandle()->translate(F_B * deltaY * 10.0 +
                                           L_R * deltaX * 10.0);
//        qDebug()<<"deltaX:  "<<deltaX<<"deltaY:   "<<deltaY;
        updateGL();
    }

    if(e->buttons() & Qt::RightButton)
    {
        int deltaX = e->x() - lastMousePosition.x();
        int deltaY = e->y() - lastMousePosition.y();
        double a = deltaX * (glc::PI / static_cast<double>(1800));
        double b = deltaY * (glc::PI / static_cast<double>(1800));
        GLC_Vector3d up = GLC_Vector3d(0,1,0);
//        GLC_Vector3d side = m_GlView.cameraHandle()->sideVector();
//        qDebug()<<"angle forward:   "<<m_GlView.cameraHandle()->forward().angleWithVect(up);
//        qDebug()<<"angle up:   "<<m_GlView.cameraHandle()->upVector().angleWithVect(up);
//        if(b > 0)
//        {
//            if(m_GlView.cameraHandle()->upVector().angleWithVect(up) > glc::PI / static_cast<double>(2))
//                b = 0;
//        }
//        if(b < 0)
//        {
//            if(m_GlView.cameraHandle()->forward().angleWithVect(up) <glc::PI / static_cast<double>(2))
//                b = 0;
//        }
        m_GlView.cameraHandle()->rotateAroundTarget(up,-a);
        m_GlView.cameraHandle()->rotateAroundTarget(m_GlView.cameraHandle()->sideVector(),-b);
        updateGL();

    }
    lastMousePosition = e->pos();
    e->accept();
//    qDebug()<<"x: "<<e->pos().x()<<"   y: "<<e->pos().y();

}

void GLWidget::mouseReleaseEvent(QMouseEvent*)
{
	if (m_MoverController.hasActiveMover())
	{
		m_MoverController.setNoMover();
		updateGL();
	}
    //    e->ignore();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    if(event->delta() < 0)
    {
        m_GlView.cameraHandle()->setDistEyeTarget(m_GlView.cameraHandle()->distEyeTarget() * 1.02);
        updateGL();
    }
    if(event->delta() > 0)
    {
        m_GlView.cameraHandle()->setDistEyeTarget(m_GlView.cameraHandle()->distEyeTarget() * 0.98);
        updateGL();
    }
}

void GLWidget::MoveObject()
{
//    qDebug()<<"(record+unit).length()"<<(record+unit).length();
//    qDebug()<<"direction.length()"<<direction.length();
    if((record+unit).length() > direction.length())
    {
        m_Sphere.translate(direction-record);
        const double *tm = m_Sphere.matrix().getData();
        if(fenceFlag)
        emit fenceWarning(elecFence.PtInPolygon(QPoint(tm[12],tm[14])));
//        qDebug()<<elecFence.PtInPolygon(QPoint(tm[12],tm[14]));
//        m_GlView.cameraHandle()->setTargetCam(GLC_Point3d(tm[12],0,tm[14]));
        updateGL();
        vi++;
        if(vi > vertices.length()-1)
        {
            m_MotionTimer.stop();
            return;
        }
        direction = vertices[vi]-vertices[vi-1];
        GLC_Vector3d mid = direction;
        unit = mid.normalize() * speed;
        record = GLC_Vector3d(0,0,0);
        return;
    }
    m_Sphere.translate(unit);
    const double *tm = m_Sphere.matrix().getData();
    if(fenceFlag)
    emit fenceWarning(elecFence.PtInPolygon(QPoint(tm[12],tm[14])));
//    qDebug()<<elecFence.PtInPolygon(QPoint(tm[12],tm[14]));
//    m_GlView.cameraHandle()->setTargetCam(GLC_Point3d(tm[12],0,tm[14]));
//    for(int i=0;i<16;i++)
//        qDebug()<<tm[i];
//    qDebug()<<"-----------------------------------";
    record = record + unit;
//    qDebug()<<"record:   "<<record.length();
    updateGL();
}

void GLWidget::trace()
{
    ComputePath();
    SetSphere();
    m_MotionTimer.start(60);
    MoveAlongPath();
}

void GLWidget::isoView1()
{
    qDebug()<<"isoView1";
    GLC_Camera newCam = m_GlView.cameraHandle()->topView();
//    m_GlView.cameraHandle()->setCam(newCam);
    m_GlView.cameraHandle()->setCam(newCam.eye(),newCam.target(),m_GlView.cameraHandle()->upVector());
    updateGL();

}

void GLWidget::isoView2()
{
    qDebug()<<"isoView2";
    GLC_Camera newCam ;
    newCam.setDistEyeTarget(m_GlView.cameraHandle()->distEyeTarget());
    newCam.rotateAroundTarget(glc::X_AXIS,-glc::PI/4);
    newCam.setTargetCam(m_GlView.cameraHandle()->target());
    newCam.setUpCam(m_GlView.cameraHandle()->upVector());
    m_GlView.cameraHandle()->setCam(newCam);
    updateGL();
}

void GLWidget::makePolygon()
{
    emit isFence(true);
    GLC_Mesh m_Mesh;
    m_Mesh.addVertice(polyvertices);
    m_Mesh.addNormals(normals);
    GLC_Material *m = new GLC_Material(QColor(Qt::blue));
    m->setOpacity(0.5);
    IndexList li = {0,1,2,3,4};
    m_Mesh.addTrianglesFan(m,li);
    m_Mesh.finish();
    GLC_3DViewInstance ins(m_Mesh.clone());
    m_Polygon.clear();
    m_Polygon.add(ins);
    updateGL();
}

void GLWidget::changeFlag(bool tf)
{
    fenceFlag = tf;
}
