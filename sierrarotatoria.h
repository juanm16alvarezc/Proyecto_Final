#ifndef SIERRAROTATORIA_H
#define SIERRAROTATORIA_H

#include <QGraphicsPixmapItem>
#include <QPointF>


class SierraRotatoria : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:

    SierraRotatoria(qreal xCentro, qreal yCentro, qreal radio,
                    qreal velocidadAngular, qreal velocidadRotacion, int sX, int sY, int X, int Y);

private slots:

    void mover();

private:
    QPointF centro;
    qreal radio;
    qreal anguloActual;
    qreal velocidadAngular;
    qreal rotacionActual;
    qreal velocidadRotacion;
    int scaledX,scaledY, X,Y;
};

#endif // SIERRAROTATORIA_H
