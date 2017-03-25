#include "GlCanvas.h"
#include "Renderer.h"

#include <QTabletEvent>
#include <QPainter>
#include <QOpenGLContext>
#include <QApplication>

#include <iostream>
using namespace  std;

RenderThread::RenderThread() : QThread(), m_canvas(0)
{
}

RenderThread::~RenderThread()
{
}

void RenderThread::SetCanvas( GlCanvas * c )
{
    m_canvas = c;
}

void RenderThread::SetRenderer( Renderer * ren )
{
    m_renderer = ren;
}

void RenderThread::run()
{
    // Do the rendering
    m_canvas->makeCurrent();
    QPainter painter( m_canvas );
    painter.setRenderHint( QPainter::Antialiasing );
    m_renderer->Render( painter );
    m_canvas->doneCurrent();

    // return context to main thread
    m_canvas->context()->moveToThread(QApplication::instance()->thread());

    // tell main thread to swap the buffer
    m_canvas->update();
}

GlCanvas::GlCanvas( QWidget * parent ) : QOpenGLWidget( parent )
{
    setUpdateBehavior( QOpenGLWidget::PartialUpdate );
    m_drawing = false;
    m_renderThread = new RenderThread;
    m_renderThread->SetCanvas( this );
    m_renderer = new Renderer;
    m_renderThread->SetRenderer( m_renderer );

    connect( this, SIGNAL(aboutToCompose()), this, SLOT(startCompositing()), Qt::DirectConnection );
    connect( this, SIGNAL(frameSwapped()), this, SLOT(finishCompositing()), Qt::DirectConnection );
    connect( this, SIGNAL(aboutToResize()), this, SLOT(StartResize()), Qt::DirectConnection );
    connect( this, SIGNAL(resized()), this, SLOT(FinishResize()), Qt::DirectConnection );
}

GlCanvas::~GlCanvas()
{
    m_renderThread->terminate();
    delete m_renderThread;
}

void GlCanvas::startCompositing()
{
    // need to wait for render thread to return context, in case it is running
    m_renderThread->wait();
}

void GlCanvas::finishCompositing()
{
    // buffer has just been swapped, we can start rendering again if there are pending lines to draw
    tryRender();
}

void GlCanvas::StartResize()
{
    // need to wait for render thread to return context, in case it is running
    m_renderThread->wait();
}

void GlCanvas::FinishResize()
{
    // This operation is padded by wait calls, i.e. renders
    // after a resize need to happen before this call returns
    // as Qt's event handling seem to require OpenGL context
    // to be owned by the GUI thread at some point after this
    // call and it is not notifying us. If the render thread
    // is launched at this point and we return, Qt crashes the
    // program because the main thread doesn't own the context
    // somewhere down the line.
    m_renderThread->wait();
    m_renderer->Resize( width(), height() );
    context()->moveToThread( m_renderThread );
    m_renderThread->start();
    m_renderThread->wait();
}

void GlCanvas::initializeGL()
{
    cout << "Support threaded opengl: " << (this->context()->supportsThreadedOpenGL() ? "true" : "false") << endl;
}

void GlCanvas::tryRender()
{
    if( !m_renderThread->isRunning() && m_renderer->NeedsRender() )
    {
        // Start rendering thread
        context()->moveToThread( m_renderThread );
        m_renderThread->start();
    }
}

void GlCanvas::tabletEvent( QTabletEvent * e )
{
    if( e->type() == QEvent::TabletPress )
    {
        m_drawing = true;
        m_renderer->StartLine( (double)e->pos().x(), (double)e->pos().y() );
    }
    else if( e->type() == QEvent::TabletRelease )
    {
        m_drawing = false;
    }
    else if( e->type() == QEvent::TabletMove && m_drawing )
    {
        m_renderer->AddPoint( (double)e->pos().x(), (double)e->pos().y() );
        tryRender();
    }
    e->accept();
}

void GlCanvas::mousePressEvent( QMouseEvent * e )
{
    m_drawing = true;
    m_renderer->StartLine( (double)e->pos().x(), (double)e->pos().y() );
}

void GlCanvas::mouseReleaseEvent(QMouseEvent*)
{
    m_drawing = false;
}

void GlCanvas::mouseMoveEvent(QMouseEvent*e)
{
    m_renderer->AddPoint( (double)e->pos().x(), (double)e->pos().y() );
    tryRender();
}
