#ifndef PROTAGONISTAGRAVEDAD_H
#define PROTAGONISTAGRAVEDAD_H

#include "protagonista.h"
#include <QTimer>

class ProtagonistaGravedad : public Protagonista {
    Q_OBJECT
public slots:
    void actualizarMovimiento();
    void moverTwo();
    void comprobarMeta();

public:
    ProtagonistaGravedad(nivel *niv, QGraphicsScene *escena, int nivelID);
    ~ProtagonistaGravedad();


    void saltar();
    void keyPressEvent(QKeyEvent *event) ;
    bool getMeta()const;
    bool getPerder();
    void recolectarObjeto();
    bool detectarColisiones();
    void setPerder(bool P);
    void moverIzquierda();
    void moverDerecha();

private:
    float aceleracionY;
    bool enSuelo;
    QTimer* TimerG, *TimerMeta;
    bool llegarMeta,Perder;
    int objetosRecolectados;
    const int totalObjetosParaGanar = 3;

};

#endif // PROTAGONISTAGRAVEDAD_H
