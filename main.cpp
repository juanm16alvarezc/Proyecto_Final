#include "videojuego.h"
#include "inicioSesion.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    InicioSesion inicioSesion;
    if (inicioSesion.exec() == QDialog::Accepted) {
        Videojuego w;
        w.show();
        return a.exec();
    }

    return 0;
}
