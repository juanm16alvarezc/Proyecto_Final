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
private slots:
    void entrarNivel1();
    void entrarNivel2();
    void salirJuego();
    void verificarFinDelJuego();

private:
    Ui::Videojuego *ui;
    int nivelID;
    nivel* nivelActual;
    bool finDelJuego;
    QTimer* EndGame;


};

#endif // VIDEOJUEGO_H
