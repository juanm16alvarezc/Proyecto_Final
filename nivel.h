#ifndef NIVEL_H
#define NIVEL_H

#include "enemigo.h"
#include "protagonista.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include"QObject"
#include "protagonistagravedad.h"
#include "objetoganar.h"
#include "sierrarotatoria.h"
#include "pincho.h"

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
    void agregarBolsas();
    void agregarPinchos();

    void actualizarPosicionCronometro();
    void iniciarCronometro(int segundosIniciales);

private:
    Protagonista* prota;
    ProtagonistaGravedad* prota_;
    QGraphicsView *vista;
    QGraphicsScene *escena;
    QList<QRect> areasOcupadas;

    vector<Enemigo*> enemigos;
    vector<ObjetoGanar*> bolsas;
    vector<Pincho*> pinchos;
    QTimer* spawnTimer;
    QTimer* comprobacionTimer;
    QTimer* centrarCam;
    int maxEnemigos;
    int enemigosActuales,enemigosImpactados;
    QGraphicsTextItem* textoEnemigosImpactados;
    int nivelID;

    bool ganar;
    bool perder;
    bool finDelJuego;
    SierraRotatoria* sierra, *sierra2, *sierra3;

    QGraphicsTextItem* textoCronometro;
    QTimer* timerCronometro;
    int tiempoRestante;





private slots:
    void spawnearEnemigo();
    void comprobarCondiciones();
    void actualizarVistaConProtagonista();
    void actualizarTiempo();



};

#endif // NIVEL_H
