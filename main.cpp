#include <QtGui>
#include "controlbar.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ControlBar w;
    w.show();

    return a.exec();
}
