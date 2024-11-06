#ifndef VIDEOJUEGO_H
#define VIDEOJUEGO_H

#include <QMainWindow>
#include "ui_videojuego.h"
namespace Ui {
class Videojuego;
}

class Videojuego : public QMainWindow
{
    Q_OBJECT

public:
    explicit Videojuego(QWidget *parent = nullptr);
    ~Videojuego();

private slots:
    void entrarNivel1();
    void entrarNivel2();
    void salirJuego();

private:
    Ui::Videojuego *ui;
};

#endif // VIDEOJUEGO_H
