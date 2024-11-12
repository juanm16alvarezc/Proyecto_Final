#include "nivel.h"
#include <QGraphicsRectItem>  // ejemplos
#include <QBrush>
#include <QImage>

nivel::nivel(int nivelID) :ganar(false), perder(false),finDelJuego(false){
    // Crear la escena y vista
    escena = new QGraphicsScene();
    vista = new QGraphicsView(escena);


    if (nivelID == 1) {
        maxEnemigos=10;
        enemigosActuales=0;
        vista->setFixedSize(800,800);
        escena->setSceneRect(0, 0, 800,800);
        QImage fondo(":/imag/BackGroundCarcel.jpg");
        fondo = fondo.scaled(800, 800, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        escena->setBackgroundBrush(QBrush(fondo));


        int anchoEscena = 800;
        int altoEscena = 800;
        int grosorPared = 30;


        QList<QRect> areasOcupadas = {
            QRect(0, 0, anchoEscena, grosorPared*2.6),
            QRect(0,altoEscena - grosorPared*2.6, anchoEscena, grosorPared*2.6),
            QRect(0, 0, grosorPared, altoEscena),
            QRect(anchoEscena - grosorPared, 0, grosorPared, altoEscena),
            QRect(grosorPared, grosorPared*2.6, grosorPared*8.5, grosorPared*1.5),
            QRect(grosorPared, grosorPared*1.5, grosorPared*2.5, grosorPared*11.5),
            QRect(grosorPared, grosorPared*15.2, grosorPared*2.5, grosorPared*3.8),
            QRect(anchoEscena - grosorPared*9, grosorPared*2.6,grosorPared*8, grosorPared*1.5),
            QRect(anchoEscena - grosorPared, grosorPared*15+5,-grosorPared*2.2, grosorPared*3.5),
            QRect(anchoEscena - grosorPared, grosorPared*11-5,-grosorPared*2.2-5, grosorPared*3),


            QRect(grosorPared*7, grosorPared*5.21+6, grosorPared*2.4, grosorPared*2.4-6),//mesa 1
            QRect(grosorPared*8.2, grosorPared*10+3, grosorPared*2.4, grosorPared*2.4-3), //mesa 2
            QRect(grosorPared*8.2, grosorPared*16, grosorPared*2.4, grosorPared*2.4), //mesa 3
            QRect(grosorPared*4, grosorPared*19.2, grosorPared*2.4, grosorPared*2.4),//mesa 4
            QRect(anchoEscena-grosorPared*7.1, grosorPared*5.2+7, grosorPared*2.4, grosorPared*2.4-7),//mesa 5
            QRect(grosorPared*15.5, grosorPared*10+10, grosorPared*2.4, grosorPared*2.4-10),//mesa 6
            QRect(grosorPared*14.6, grosorPared*16, grosorPared*2.4, grosorPared*2.4),//mesa 7
            QRect(grosorPared*19.5, grosorPared*19.2, grosorPared*2.4, grosorPared*2.4),//mesa 8
        };
        for (const QRect& area : areasOcupadas) {
            dibujarPared(area.x(), area.y(), area.width(), area.height());
        }
        this->areasOcupadas = areasOcupadas;


        prota = new Protagonista(this,escena,1);
        prota->setPos(400, 400);
        escena->addItem(prota);
        prota->setFlag(QGraphicsItem::ItemIsFocusable);
        prota->setFocus();


        this->spawnTimer = new QTimer;
        connect(spawnTimer, &QTimer::timeout, this, &nivel::spawnearEnemigo);
        spawnTimer->start(3000);

        QTimer* comprobacionTimer = new QTimer(this);
        connect(comprobacionTimer, &QTimer::timeout, this, &nivel::comprobarCondiciones);
        comprobacionTimer->start(1000);

    } else if (nivelID == 2) {

        vista->setFixedSize(1200, 800);
        escena->setSceneRect(0, 0, 3600, 800);
        QImage fondo(":/imag/BackGroundNocheRecortado.png");
        fondo = fondo.scaled(3600, 800, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        escena->setBackgroundBrush(QBrush(fondo));


        int anchoEscena = 3600;
        int altoEscena = 800;
        int grosorPared = 20;

        QList<QRect> areasOcupadas = {
            QRect(0, 0, anchoEscena, grosorPared),
            QRect(0, altoEscena - grosorPared, anchoEscena, grosorPared),
            QRect(0, 0, grosorPared, altoEscena),
            QRect(anchoEscena - grosorPared, 0, grosorPared, altoEscena),

        };

        for (const QRect& area : areasOcupadas) {
            dibujarPared(area.x(), area.y(), area.width(), area.height(),QColorConstants::Black);
        }
        this->areasOcupadas = areasOcupadas;



        prota = new Protagonista(this,escena,2);
        prota->setPos(200, 400);
        escena->addItem(prota);

        /*Enemigo* enemigo2 = new Enemigo(2,*prota);
        enemigo2->setPos(500, 400);
        enemigos.push_back(enemigo2);
        escena->addItem(enemigo2);*/
    }

    prota->setFlag(QGraphicsItem::ItemIsFocusable);
    prota->setFocus();

    configurarFocoProtagonista();
}

nivel::~nivel(){
    if (spawnTimer!=nullptr){delete spawnTimer;}
    if (vista!=nullptr){delete vista;}
    if (escena!=nullptr){delete escena;}
    if (prota!=nullptr){delete prota;}

    for (auto enemigo : enemigos) {
        if (enemigo!=nullptr){delete enemigo;}
    }
}

void nivel::dibujarPared(int x, int y, int ancho, int alto) {
    QGraphicsRectItem* pared = new QGraphicsRectItem(x, y, ancho, alto);
    pared->setBrush(QBrush(QColor(QColorConstants::Transparent)));
    escena->addItem(pared);
}

void nivel::dibujarPared(int x, int y, int ancho, int alto, QColor color) {
    QGraphicsRectItem* pared = new QGraphicsRectItem(x, y, ancho, alto);
    pared->setBrush(QBrush(QColor(color)));
    escena->addItem(pared);
}

void nivel::configurarFocoProtagonista() {

    vista->centerOn(prota);
    prota->setFlag(QGraphicsItem::ItemIsFocusable);
    prota->setFocus();

}

QGraphicsScene *nivel::getEscena(){
    return escena;
}

QGraphicsView *nivel::getVista(){
    return vista;
}

Protagonista* nivel::getProtagonista(){
    return prota;
}

void nivel::spawnearEnemigo() {
    if(this->getProtagonista()->getSalud()<=0){
        return;
    }
    if (enemigosActuales < maxEnemigos) {
        QList<QPoint> posicionesSpawn = {
            QPoint(120, 150),
            QPoint(500, 150),
            QPoint(300, 630),
        };

        int index = rand() % posicionesSpawn.size();
        QPoint posicionElegida = posicionesSpawn[index];

        // Crear un enemigo y pasar el puntero al protagonista
        Enemigo* enemigo = new Enemigo(1, *prota);
        enemigo->setPos(posicionElegida);

        escena->addItem(enemigo);
        enemigos.push_back(enemigo);
        enemigosActuales++;
    }
}

QList<QRect> nivel::getAreasOcupadas() const {
    return areasOcupadas;
}


void nivel::incrementarContadorEnemigosImpactados() {
    enemigosImpactados++;
}

void nivel::comprobarCondiciones() {
    if (prota->getSalud() <= 0 || (prota->getMuniciones() == 0 && enemigosImpactados<10)) {
        perder = true;
    }

    if (enemigosImpactados >= 10) {
        ganar = true;
    }
    qDebug() << "Vida actual: nivel" << this->prota->getSalud();

    if (ganar) {
        escena->clear();
        escena->setBackgroundBrush(QColor(QColorConstants::Black));
        QGraphicsTextItem* winText = new QGraphicsTextItem("YOU WIN");
        winText->setDefaultTextColor(Qt::green);
        winText->setFont(QFont("Courier New", 120, QFont::Bold));
        winText->setPos(0, 800 / 2);
        escena->addItem(winText);
        finDelJuego=true;
    } else if (perder) {
        escena->clear();
        escena->setBackgroundBrush(QColor(QColorConstants::Black));
        QGraphicsTextItem* loseText = new QGraphicsTextItem("YOU LOSE");
        loseText->setDefaultTextColor(Qt::red);
        loseText->setFont(QFont("Courier New", 120, QFont::Bold));
        loseText->setPos(0, 800 / 2);
        escena->addItem(loseText);
        finDelJuego=true;
    }
}
bool nivel::getFinDelJuego(){
    return finDelJuego;
}
