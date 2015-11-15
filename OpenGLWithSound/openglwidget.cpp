#include "openglwidget.h"

OpenGLWidget::OpenGLWidget( QWidget * parent ) : QOpenGLWidget(parent)
{

}

void OpenGLWidget::initializeGL()
{

}

void OpenGLWidget::paintGL()
{
    glClearColor( 1.0, 0.0, 0.0, 1.0 );
    glClear( GL_COLOR_BUFFER_BIT );


}

void OpenGLWidget::resizeGL(int w, int h)
{

}
