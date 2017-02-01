#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>

class glWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit glWidget( QWidget * parent=0 );
    ~glWidget();

protected:

    void paintGL();
};

#endif
