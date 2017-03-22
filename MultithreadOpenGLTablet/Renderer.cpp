#include "Renderer.h"
#include <QPainter>

Renderer::Renderer()
    : m_color(Qt::red)
    , m_brush(m_color)
    , m_pen(m_brush, 10.0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin)
{
}

bool Renderer::NeedsRender()
{
    return m_lastPoints.size() >= 2;
}

void Renderer::Render( QPainter & painter )
{
    // Take a copy of accumulated points to avoid locking access to
    // the cue for too long
    m_lastPointsMutex.lock();
    QList<QPointF> lines( m_lastPoints );
    QPointF temp = m_lastPoints[ m_lastPoints.size() - 1 ];
    m_lastPoints.clear();
    m_lastPoints.push_back( temp );
    m_lastPointsMutex.unlock();

    // Do the drawing
    painter.setPen( m_pen );
    for( int i = 0; i < lines.size() - 1; ++i )
    {
        painter.drawLine( lines[i], lines[i+1] );
    }
    painter.end();
}

void Renderer::StartLine( double x, double y )
{
    m_lastPointsMutex.lock();
    m_lastPoints.clear();
    m_lastPoints.push_back( QPointF( x, y ) );
    m_lastPointsMutex.unlock();
}

void Renderer::AddPoint( double x, double y )
{
    m_lastPointsMutex.lock();
    m_lastPoints.push_back( QPointF( x, y ) );
    m_lastPointsMutex.unlock();
}
