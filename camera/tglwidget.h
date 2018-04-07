#ifndef TGLWIDGET_H
#define TGLWIDGET_H
#include <QGLWidget>

//////////////////////////// GLC specific///////////////////////////////////////
// The factory
#include <GLC_Factory>
// Light
#include <GLC_Light>
// Material
#include <GLC_Material>
// The Viewport with a default camera
#include <GLC_Viewport>
// The World which manage GLC_object
#include <GLC_World>
// The Mover controller is used to change the point of view
#include <GLC_MoverController>

#include <GLC_3DViewCollection>

//////////////////////////End GLC specific/////////////////////////////////////

class TGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    TGLWidget(QWidget *p_parent);
    ~TGLWidget();
private:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    // Create GLC_Object to display
    void CreateScene();
    GLC_Light m_Light;
    GLC_World m_World;
    GLC_Viewport m_GlView;
};

#endif // TGLWIDGET_H
