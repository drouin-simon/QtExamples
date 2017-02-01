#include "glWidget.h"

glWidget::glWidget( QWidget * parent ) : QOpenGLWidget(parent)
{

}

glWidget::~glWidget()
{

}

void glWidget::paintGL()
{
    glClearColor( 0.0, 0.0, 0.0, 1.0 );
    glClear( GL_COLOR_BUFFER_BIT );
}
