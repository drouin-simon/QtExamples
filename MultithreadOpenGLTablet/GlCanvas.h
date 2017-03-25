#ifndef __GlCanvas_h_
#define __GlCanvas_h_

#include <QOpenGLWidget>
#include <QThread>

class GlCanvas;
class Renderer;
class RenderThread;

class RenderThread : public QThread
{
    Q_OBJECT
public:

    RenderThread();
    virtual ~RenderThread();
    void SetCanvas( GlCanvas * c );
    void SetRenderer( Renderer * ren );

protected:

    virtual void run();

    GlCanvas * m_canvas;
    Renderer * m_renderer;
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
    void StartResize();
    void FinishResize();

protected:

    // paintEvent does nothing as the painting is done in the render thread
    virtual void paintEvent( QPaintEvent * ) override {};
    virtual void initializeGL() override;

    void tabletEvent(QTabletEvent *event) override;
    virtual void mousePressEvent(QMouseEvent*) override;
    virtual void mouseReleaseEvent(QMouseEvent*) override;
    virtual void mouseMoveEvent(QMouseEvent*) override;

    void tryRender();

    RenderThread * m_renderThread;
    Renderer * m_renderer;
    bool m_drawing;
};

#endif
