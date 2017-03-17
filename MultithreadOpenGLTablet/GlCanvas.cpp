#include "GlCanvas.h"
#include <QTabletEvent>
#include <QPainter>
#include <QOpenGLContext>
#include <QApplication>

RenderThread::RenderThread()
    : QThread()
    , m_color(Qt::red)
    , m_brush(m_color)
    , m_pen(m_brush, 10.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
    , m_canvas(0)
{
}

RenderThread::~RenderThread()
{
}

void RenderThread::SetCanvas( GlCanvas * c )
{
    m_canvas = c;
}

void RenderThread::run()
{
    m_canvas->makeCurrent();
    QPainter painter( m_canvas );
    painter.setRenderHint( QPainter::Antialiasing );
    painter.setPen( m_pen );
    for( int i = 0; i < m_lines.size() - 1; ++i )
    {
        painter.drawLine( m_lines[i], m_lines[i+1] );
    }
    painter.end();
    m_canvas->doneCurrent();

    // return context to main thread
    m_canvas->context()->moveToThread(QApplication::instance()->thread());

    // tell main thread to swap the buffer
    m_canvas->update();
}

GlCanvas::GlCanvas( QWidget * parent )
    : QOpenGLWidget( parent )

{
    setUpdateBehavior( QOpenGLWidget::PartialUpdate );
    m_drawing = false;
    m_renderThread = new RenderThread;
    m_renderThread->SetCanvas( this );

    connect( this, SIGNAL(aboutToCompose()), this, SLOT(startCompositing()), Qt::DirectConnection );
    connect( this, SIGNAL(frameSwapped()), this, SLOT(finishCompositing()), Qt::DirectConnection );
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
    needRender();
}

void GlCanvas::needRender()
{
    if( m_lastPoints.size() < 2 )
        return;
    if( !m_renderThread->isRunning() )
    {
        // Start rendering thread
        context()->moveToThread( m_renderThread );
        m_renderThread->SetLines( m_lastPoints );
        m_renderThread->start();

        // Clear list of points to render
        QPointF temp = m_lastPoints[ m_lastPoints.size() - 1 ];
        m_lastPoints.clear();
        m_lastPoints.push_back( temp );
    }
}

void GlCanvas::tabletEvent( QTabletEvent * e )
{
    if( e->type() == QEvent::TabletPress )
    {
        m_drawing = true;
        m_lastPoints.clear();
        m_lastPoints.push_back( e->posF() );
    }
    else if( e->type() == QEvent::TabletRelease )
    {
        m_drawing = false;
    }
    else if( e->type() == QEvent::TabletMove && m_drawing )
    {
        m_lastPoints.push_back( e->posF() );
        needRender();
    }
    e->accept();
}

void GlCanvas::mousePressEvent( QMouseEvent * e )
{
    m_drawing = true;
    m_lastPoints.clear();
    m_lastPoints.push_back( e->pos() );
}

void GlCanvas::mouseReleaseEvent(QMouseEvent*)
{
    m_drawing = false;
}

void GlCanvas::mouseMoveEvent(QMouseEvent*e)
{
    m_lastPoints.push_back( e->pos() );
    needRender();
}
