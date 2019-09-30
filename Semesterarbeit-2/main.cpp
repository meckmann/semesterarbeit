#include "myDevice.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myDevice w;
    w.show();

    return a.exec();
}
