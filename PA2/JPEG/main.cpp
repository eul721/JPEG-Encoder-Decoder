#include "mainwindow.h"
#include <QtWidgets\qapplication.h>




int main( int argc, char** argv )
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

                                              // Wait for a keystroke in the window
    return a.exec();
}





