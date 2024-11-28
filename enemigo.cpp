#include "enemigo.h"
#include "protagonista.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QPixmap>
#include <QRect>

Enemigo::Enemigo(int nivelID, Protagonista& p)
    : nivelID(nivelID), velocidad(10), mirandoDerecha(true), protagonista(p) {

    int nuevoAncho = 64 / 1.3;
    int nuevoAlto = 128 / 1.3;

    QPixmap sprite;
    if (nivelID == 1) {
        sprite = QPixmap(":/imag/PoliciasAct.png");
        setPixmap(sprite.copy(69, 84, (20/1.1)-1, 40/1.4));
        setPixmap(pixmap().scaled(nuevoAncho, nuevoAlto));
        moverTimer = new QTimer(this);
        connect(moverTimer, SIGNAL(timeout()), this, SLOT(mover()));
        moverTimer->start(70);


    } else if (nivelID == 2) {
        sprite = QPixmap(":/images/enemigo2.png");
    }

}

Enemigo::~Enemigo() {
    if (moverTimer) {
        moverTimer->stop();
        delete moverTimer;
        moverTimer = nullptr;
    }
}

void Enemigo::mover() {
    QPointF posProtagonista = protagonista.pos();
    QPointF posEnemigo = pos();

    float deltaX = posProtagonista.x() - posEnemigo.x();
    float deltaY = posProtagonista.y() - posEnemigo.y();

    float distancia = std::sqrt(deltaX * deltaX + deltaY * deltaY);

    if (distancia > 0) {
        deltaX /= distancia;
        deltaY /= distancia;

        mirandoDerecha = (deltaX > 0);

        qreal nuevaX = x() + deltaX * velocidad;
        qreal nuevaY = y() + deltaY * velocidad;

        setPos(nuevaX, nuevaY);

        if (!detectarColisiones()) {
            bool movimientoRealizado = false;


            for (int i = 0; i < 4; ++i) {
                float angulo = i * (M_PI / 2);
                float offsetX = std::cos(angulo) * velocidad;
                float offsetY = std::sin(angulo) * velocidad;

                nuevaX = x() + offsetX;
                nuevaY = y() + offsetY;

                setPos(nuevaX, nuevaY);

                if (detectarColisiones()) {
                    movimientoRealizado = true;
                    break;
                }
            }
            if (!movimientoRealizado) {
                setPos(posEnemigo);
            }
        }
    }

    actualizarSprite();
}

bool Enemigo::detectarColisiones() {

    for (QGraphicsItem* item : collidingItems()) {


        if (Protagonista* protagonista = dynamic_cast<Protagonista*>(item)) {
            this->protagonista.recibirDanio(20);
        }

        if (dynamic_cast<Enemigo*>(item) == nullptr) {
            return false;
        }
    }
    return true;
}

void Enemigo::actualizarSprite() {
    QPixmap sprite;
    if (nivelID == 1) {
        sprite = QPixmap(":/imag/PoliciasAct.png");
    }
    if (mirandoDerecha) {
        setPixmap(sprite.copy(69, 84, (20/1.1)-1, 40/1.4));
    } else {
        QPixmap spriteIzquierda = sprite.copy(69, 84, (20/1.1)-2, 40/1.4);
        setPixmap(spriteIzquierda.transformed(QTransform().scale(-1, 1)));
    }

    setPixmap(pixmap().scaled(64 / 1.3, 128 / 1.3));
}
