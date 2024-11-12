#ifndef NIVEL_H
#define NIVEL_H

#include "enemigo.h"
#include "protagonista.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include"QObject"

using namespace std;
class nivel: public QObject , public QGraphicsPixmapItem
{
     Q_OBJECT
public:

    ~nivel();
    nivel(int nivelID);
    void configurarFocoProtagonista();
    QGraphicsScene* getEscena();
    QGraphicsView* getVista();
    void dibujarPared(int x, int y, int ancho, int alto);
    void dibujarPared(int x, int y, int ancho, int alto, QColor color);
    Protagonista* getProtagonista();
    QList<QRect> getAreasOcupadas() const;
    void incrementarContadorEnemigosImpactados();
    bool getFinDelJuego();

private:
    Protagonista* prota;
    QGraphicsView *vista;
    QGraphicsScene *escena;
    QList<QRect> areasOcupadas;

    vector<Enemigo*> enemigos;
    QTimer* spawnTimer;
    int maxEnemigos;
    int enemigosActuales,enemigosImpactados;


    bool ganar;
    bool perder;
    bool finDelJuego;
private slots:
    void spawnearEnemigo();
    void comprobarCondiciones();


};

#endif // NIVEL_H
