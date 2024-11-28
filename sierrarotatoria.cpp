#include "sierrarotatoria.h"
#include <QTimer>
#include <QtMath>

SierraRotatoria::SierraRotatoria(qreal xCentro, qreal yCentro, qreal radio, qreal velocidadAngular, qreal velocidadRotacion, int sX, int sY,int X, int Y)
    : centro(QPointF(xCentro, yCentro)), radio(radio),
    anguloActual(0), velocidadAngular(velocidadAngular),
    rotacionActual(0), velocidadRotacion(velocidadRotacion),scaledX(sX),scaledY(sY),X(X),Y(Y) {

    setPixmap(QPixmap(":/imag/Sierra-removebg-preview (1).png").scaled( scaledX, scaledY));
    setTransformOriginPoint(boundingRect().center());

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SierraRotatoria::mover);
    timer->start(16);
}

void SierraRotatoria::mover() {
    anguloActual += velocidadAngular;
    if (anguloActual >= 360) anguloActual -= 360;

    qreal radianes = qDegreesToRadians(anguloActual);
    qreal x = X + centro.x() + radio * qCos(radianes);
    qreal y = Y + centro.y() + radio * qSin(radianes);
    setPos(x, y);

    rotacionActual += velocidadRotacion;
    if (rotacionActual >= 360) rotacionActual -= 360;

    setRotation(rotacionActual);

}

