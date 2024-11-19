#ifndef PROTAGONISTAGRAVEDAD_H
#define PROTAGONISTAGRAVEDAD_H

#include "protagonista.h"
#include <QTimer>

class ProtagonistaGravedad : public Protagonista {
    Q_OBJECT
public slots:
    void actualizarMovimiento();
    void moverTwo();

public:
    ProtagonistaGravedad(nivel *niv, QGraphicsScene *escena, int nivelID);
    ~ProtagonistaGravedad();

    void aplicarFuerza(float fuerzaX, float fuerzaY);
    void detectarColisionConSuelo();
    void saltar();
    void keyPressEvent(QKeyEvent *event) ;
private:
    float aceleracionY;
    bool enSuelo;
    QTimer* TimerG;

};

#endif // PROTAGONISTAGRAVEDAD_H
