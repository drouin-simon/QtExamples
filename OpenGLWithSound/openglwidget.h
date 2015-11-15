#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>

class OpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:

    OpenGLWidget( QWidget * parent = 0 );

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
};

#endif
