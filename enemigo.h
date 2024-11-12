#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class Protagonista;

class Enemigo : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Enemigo(int nivelID, Protagonista& p);
    ~Enemigo();

private slots:
    void mover();

private:
    bool detectarColisiones();
    void actualizarSprite();

    int velocidad;
    int nivelID;
    QTimer* moverTimer;
    Protagonista& protagonista;
    bool mirandoDerecha;
};

#endif // ENEMIGO_H
