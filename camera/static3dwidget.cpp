#include <QtGui>
#include "static3dwidget.h"
#include "tglwidget.h"
Static3DWidget::Static3DWidget()
: p_GLWidget(NULL)
{
    p_GLWidget= new TGLWidget(this);
    H_Layout = new QHBoxLayout(this);
    H_Layout->addWidget(p_GLWidget);
}
