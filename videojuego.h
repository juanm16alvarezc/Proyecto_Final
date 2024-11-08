#ifndef VIDEOJUEGO_H
#define VIDEOJUEGO_H

#include <QMainWindow>
#include "ui_videojuego.h"
#include "nivel.h"
#include <QKeyEvent>

using namespace std;
namespace Ui {
class Videojuego;
}

class Videojuego : public QMainWindow
{
    Q_OBJECT

public:
    explicit Videojuego(QWidget *parent = nullptr);
    ~Videojuego();
    void setNivelID(int id);
    void construirNivel();


    void keyPressEvent(QKeyEvent *event) override;
    void configurarEventosNivel1(QKeyEvent *event);
    void configurarEventosNivel2(QKeyEvent *event);

private slots:
    void entrarNivel1();
    void entrarNivel2();
    void salirJuego();

private:
    Ui::Videojuego *ui;
    int nivelID;
    nivel* nivelActual;


};

#endif // VIDEOJUEGO_H
