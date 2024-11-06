#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QObject>

#include <QGraphicsPixmapItem>
class Personaje: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Personaje();
};

#endif // PERSONAJE_H
