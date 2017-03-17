#ifndef __GlCanvas_h_
#define __GlCanvas_h_

#include <QOpenGLWidget>
#include <QColor>
#include <QBrush>
#include <QPen>
#include <QThread>

class GlCanvas;

class RenderThread : public QThread
{

    Q_OBJECT

public:

    RenderThread();
    virtual ~RenderThread();
    void SetCanvas( GlCanvas * c );
    void SetLines( QList<QPointF> & lines ) { m_lines = lines; }

protected:

    virtual void run();

    QColor m_color;
    QBrush m_brush;
    QPen m_pen;

    GlCanvas * m_canvas;
    QList<QPointF> m_lines;
};

class GlCanvas : public QOpenGLWidget
{

    Q_OBJECT

public:

    GlCanvas( QWidget * parent = 0 );
    virtual ~GlCanvas();

protected slots:

    void startCompositing();
    void finishCompositing();

protected:

    // paintEvent does nothing as the painting is done in the render thread
    virtual void paintEvent( QPaintEvent * ) override {};

    void needRender();

    void tabletEvent(QTabletEvent *event) override;
    virtual void mousePressEvent(QMouseEvent*) override;
    virtual void mouseReleaseEvent(QMouseEvent*) override;
    virtual void mouseMoveEvent(QMouseEvent*) override;

    RenderThread * m_renderThread;

    bool m_drawing;
    QList<QPointF> m_lastPoints;
};

#endif
