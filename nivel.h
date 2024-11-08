#ifndef NIVEL_H
#define NIVEL_H

#include "enemigo.h"
#include "protagonista.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

using namespace std;
class nivel: public QGraphicsPixmapItem
{
public:
    nivel();
    nivel(int nivelID);
    void configurarFocoProtagonista();
    QGraphicsScene* getEscena();
    QGraphicsView* getVista();


private:
    Protagonista* prota;
    vector<Enemigo*> enemigos;
    QGraphicsView *vista;
    QGraphicsScene *escena;

};

#endif // NIVEL_H
