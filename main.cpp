#include "qtomato.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

    Qtomato q;
    q.show();

    return a.exec();
}
