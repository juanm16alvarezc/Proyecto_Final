#ifndef PROYECTIL_H
#define PROYECTIL_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class nivel;
class Proyectil : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Proyectil(qreal x, qreal y, qreal direccionX, qreal direccionY, nivel* niv);
    ~Proyectil();

private slots:
    void mover();

private:
    qreal velocidad;
    qreal aceleracion;
    qreal direccionX;
    qreal direccionY;
    QTimer* moverTimer;
    nivel* Nivel;
};

#endif // PROYECTIL_H
