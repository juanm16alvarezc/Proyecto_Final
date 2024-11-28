#include "proyectil.h"
#include "enemigo.h"
#include "protagonista.h"
#include "nivel.h"
#include <QGraphicsScene>
#include <QTimer>
#include <cmath>

Proyectil::Proyectil(qreal x, qreal y, qreal direccionX, qreal direccionY, nivel *niv)
    : velocidad(2), aceleracion(1), direccionX(direccionX), direccionY(direccionY), Nivel(niv) {

    QPixmap sprite(":/imag/dona.png");
    setPixmap(sprite.scaled(20, 20));

    setPos(x, y);

    qreal magnitud = std::sqrt(direccionX * direccionX + direccionY * direccionY);
    this->direccionX /= magnitud;
    this->direccionY /= magnitud;

    moverTimer = new QTimer(this);
    connect(moverTimer, &QTimer::timeout, this, &Proyectil::mover);
    moverTimer->start(35);
}

Proyectil::~Proyectil() {
    delete moverTimer;
}

void Proyectil::mover() {
    velocidad += aceleracion;

    static double angulo = 45.0;
    angulo += 5;

    double radio = 25.0;
    double offsetX = radio * cos(angulo);
    double offsetY = radio * sin(angulo);

    setPos(x() + direccionX * velocidad + offsetX,y() + direccionY * velocidad + offsetY);

    for (QGraphicsItem* item : collidingItems()) {
        if (Enemigo* enemigo = dynamic_cast<Enemigo*>(item)) {
            if (Nivel) {
                Nivel->incrementarContadorEnemigosImpactados();
            }
            scene()->removeItem(enemigo);
            delete enemigo;
            enemigo = nullptr;

            Protagonista *P = this->Nivel->getProtagonista();
            P->reducirMuniciones();
            P->actualizarTextoMuniciones();
            scene()->removeItem(this);
            delete this;
            return;
        }
    }
    if (!scene()->sceneRect().contains(pos())) {
        Protagonista *P = this->Nivel->getProtagonista();
        P->reducirMuniciones();
        P->actualizarTextoMuniciones();
        scene()->removeItem(this);
        delete this;


    }
}
