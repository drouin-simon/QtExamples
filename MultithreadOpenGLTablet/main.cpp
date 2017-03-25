#include <QtWidgets>

#include "mainwindow.h"

int main(int argv, char *args[])
{
    QApplication app(argv, args);
    MainWindow mainWindow;
    mainWindow.resize( 800, 600 );
    mainWindow.show();
    return app.exec();
}

