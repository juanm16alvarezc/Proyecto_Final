
#include <QApplication>
#include "videojuego.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Videojuego w;
    w.show();
    return a.exec();
}
