#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>

class AudioDecoder;

class OpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:

    OpenGLWidget( QWidget * parent = 0 );

    void SetCurrentFrame( int frame );
    int GetNumberOfFrames();

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

protected:

    AudioDecoder * m_audioDecoder;
    float * m_frameData;
};

#endif
