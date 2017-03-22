#ifndef __Renderer_h_
#define __Renderer_h_

#include <QList>
#include <QMutex>
#include <QPointF>
#include <QColor>
#include <QBrush>
#include <QPen>

class Renderer
{

public:

    Renderer();

    bool NeedsRender();
    void Render( QPainter & painter );

    void StartLine( double x, double y );
    void AddPoint( double x, double y );

protected:

    bool m_drawing;
    QMutex m_lastPointsMutex;
    QList<QPointF> m_lastPoints;

    QColor m_color;
    QBrush m_brush;
    QPen m_pen;
};

#endif
