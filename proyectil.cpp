#include "proyectil.h"
#include "enemigo.h"
#include "nivel.h"
#include <QGraphicsScene>
#include <QTimer>
#include <cmath>

Proyectil::Proyectil(qreal x, qreal y, qreal direccionX, qreal direccionY, nivel *niv)
    : velocidad(5), aceleracion(3), direccionX(direccionX), direccionY(direccionY), Nivel(niv) {

    QPixmap sprite(":/imag/dona.png");
    setPixmap(sprite.scaled(20, 20));

    setPos(x, y);

    qreal magnitud = std::sqrt(direccionX * direccionX + direccionY * direccionY);
    this->direccionX /= magnitud;
    this->direccionY /= magnitud;

    moverTimer = new QTimer(this);
    connect(moverTimer, &QTimer::timeout, this, &Proyectil::mover);
    moverTimer->start(50);
}

Proyectil::~Proyectil() {
    delete moverTimer;
}

void Proyectil::mover() {
    velocidad += aceleracion;

    setPos(x() + direccionX * velocidad, y() + direccionY * velocidad);

    for (QGraphicsItem* item : collidingItems()) {
        if (Enemigo* enemigo = dynamic_cast<Enemigo*>(item)) {
            if (Nivel){
                Nivel->incrementarContadorEnemigosImpactados();
            }
            scene()->removeItem(enemigo);
            delete enemigo;
            enemigo=nullptr;
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    if (!scene()->sceneRect().contains(pos())) {
        scene()->removeItem(this);
        delete this;
    }
}
