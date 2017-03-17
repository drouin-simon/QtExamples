#include <QtWidgets>

#include "mainwindow.h"
#include "GlCanvas.h"


MainWindow::MainWindow()
{
    m_canvas = new GlCanvas( this );
    createMenus();
    setWindowTitle(tr("Multithread OpenGL tablet Example"));
    setCentralWidget( m_canvas );
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("Multithread OpenGL"), tr("This demonstrates how to render in a separate thread with QOpenGLWidget."));
}

void MainWindow::createMenus()
{
    QMenu * fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(tr("E&xit"), this, &MainWindow::close, QKeySequence::Quit);

    QMenu *helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(tr("A&bout"), this, &MainWindow::about);
    helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);
}
