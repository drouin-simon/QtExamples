#ifndef __MainWindow_h_
#define __MainWindow_h_

#include <QMainWindow>

class GlCanvas;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow();

private slots:

    void about();

private:

    void createMenus();

    GlCanvas * m_canvas;
};

#endif
