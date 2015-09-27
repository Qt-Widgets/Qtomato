#include "qtomato.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Qtomato w;
    w.show();

    return a.exec();
}
