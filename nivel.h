#ifndef NIVEL_H
#define NIVEL_H

#include "enemigo.h"
#include "protagonista.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include"QObject"
#include "protagonistagravedad.h"

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
    void actualizarTextoEnemigosImpactados();
    void configurarFocoProtagonista_();

private:
    Protagonista* prota;
    ProtagonistaGravedad* prota_;
    QGraphicsView *vista;
    QGraphicsScene *escena;
    QList<QRect> areasOcupadas;

    vector<Enemigo*> enemigos;
    QTimer* spawnTimer;
    QTimer* comprobacionTimer;
    QTimer* centrarCam;
    int maxEnemigos;
    int enemigosActuales,enemigosImpactados;
    QGraphicsTextItem* textoEnemigosImpactados;


    bool ganar;
    bool perder;
    bool finDelJuego;
private slots:
    void spawnearEnemigo();
    void comprobarCondiciones();
    void actualizarVistaConProtagonista();


};

#endif // NIVEL_H
