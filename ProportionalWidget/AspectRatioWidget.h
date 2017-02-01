#ifndef ASPECTRATIOWIDGET_H
#define ASPECTRATIOWIDGET_H

#include <QWidget>

class glWidget;
class QBoxLayout;

class AspectRatioWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AspectRatioWidget(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *event);

private:
    QBoxLayout * layout;
    glWidget * widget;
};

#endif
