#include <QtDebug>
#include <QFile>
#include <QGLContext>

#include <GLC_UserInput>
#include <GLC_Context>
#include <GLC_Vector3d>
#include <GLC_Exception>
#include "tglwidget.h"

TGLWidget::TGLWidget(QWidget *p_parent)
: QGLWidget(new QGLContext(QGLFormat(QGL::SampleBuffers)), p_parent)
, m_Light()
, m_World()
, m_GlView()
{
    connect(&m_GlView, SIGNAL(updateOpenGL()), this, SLOT(updateGL()));
    CreateScene();
}

TGLWidget::~TGLWidget()
{

}

void TGLWidget::initializeGL()
{
    m_GlView.initGl();
    m_GlView.loadBackGroundImage("E:/3DMap/MyModel/background.png");

    m_Light.setTwoSided(true);
    m_Light.setPosition(1.0, 1.0, 1.0);

    // Reframe the scene on the loaded mesh
    m_GlView.reframe(m_World.boundingBox());
    m_GlView.cameraHandle()->rotateAroundTarget(glc::X_AXIS,-glc::PI/4);
    m_GlView.cameraHandle()->setDistEyeTarget(160000);
}

void TGLWidget::paintGL()
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

void TGLWidget::resizeGL(int width, int height)
{
    m_GlView.setWinGLSize(width, height);	// Compute window aspect ratio
}

void TGLWidget::CreateScene()
{
    QFile manFile("E:/3DMap/MyModel/21A.3ds");
    m_World= GLC_Factory::instance()->createWorldFromFile(manFile);
    m_World.rootOccurrence()->structInstance()->move(GLC_Matrix4x4(glc::X_AXIS,-glc::PI/2));
    m_World.rootOccurrence()->updateChildrenAbsoluteMatrix();
}
