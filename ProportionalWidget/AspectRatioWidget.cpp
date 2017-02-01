#include "AspectRatioWidget.h"
#include <QResizeEvent>
#include <QBoxLayout>
#include <math.h>
#include "glWidget.h"

AspectRatioWidget::AspectRatioWidget(QWidget *parent) : QWidget(parent)
{
    layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    layout->setContentsMargins( 0, 0, 0, 0 );
    widget = new glWidget( this );

    // add spacer, then your widget, then spacer
    layout->addItem(new QSpacerItem(0, 0));
    layout->addWidget(widget);
    layout->addItem(new QSpacerItem(0, 0));
}

void AspectRatioWidget::resizeEvent(QResizeEvent *event)
{
    int w = event->size().width();
    int h = event->size().height();
    float widgetAspect = (float)w / h;
    float childAspect = 16.0 / 9.0;
    int widgetStretch, outerStretch;

    if( widgetAspect > childAspect ) // too wide
    {
        layout->setDirection(QBoxLayout::LeftToRight);
        widgetStretch = (int)round( h * childAspect);
        outerStretch = (int)round( ( w - widgetStretch ) * 0.5 );
    }
    else // too tall
    {
        layout->setDirection(QBoxLayout::TopToBottom);
        widgetStretch = (int)round( w / childAspect );
        outerStretch = (int)round( ( h - widgetStretch ) * 0.5 );
    }

    layout->setStretch(0, outerStretch);
    layout->setStretch(1, widgetStretch);
    layout->setStretch(2, outerStretch);
}
