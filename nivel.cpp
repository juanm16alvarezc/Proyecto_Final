#include "nivel.h"
#include <QGraphicsRectItem>  // ejemplos
#include <QBrush>
#include <QImage>

nivel::nivel(int nivelID) :ganar(false), perder(false),finDelJuego(false){
    escena = new QGraphicsScene();
    vista = new QGraphicsView(escena);


    if (nivelID == 1) {
        textoEnemigosImpactados = new QGraphicsTextItem("Enemigos impactados: 0/10");
        textoEnemigosImpactados->setFont(QFont("Times New Roman", 20));
        textoEnemigosImpactados->setDefaultTextColor(Qt::green);
        textoEnemigosImpactados->setPos(30, 750);
        escena->addItem(textoEnemigosImpactados);
        enemigosImpactados=0;
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

        comprobacionTimer = new QTimer;
        connect(comprobacionTimer, &QTimer::timeout, this, &nivel::comprobarCondiciones);
        comprobacionTimer->start(1000);

    } else if (nivelID == 2) {

        vista->setFixedSize(800, 800);
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

        QList<QRect> rectangulosNivel2 = {
            QRect(0, 0, 20, 800),
            QRect(20, 186, 150, 20),
            QRect(280, 0, 20, 550),
            QRect(130, 300, 150, 20),
            QRect(20, 430, 100, 20),
            QRect(210, 430, 70, 20),
            QRect(20, 600, 150, 20),
            QRect(20, 690, 3600, 20),
            QRect(280, 650, 150, 20),
            QRect(380, 610, 150, 20),
            QRect(620, 610, 200, 20),
            QRect(780, 570, 150, 20),
            QRect(460, 470, 300, 20),
            QRect(300, 420, 70, 20),
            QRect(460, 320, 300, 20),
            QRect(930, 230, 20, 460),
            QRect(780, 230, 150, 20),
            QRect(1030, 200, 300, 20),
            QRect(1450, 200, 300, 20),
            QRect(1750, 0, 20, 400),
            QRect(1750, 530, 20, 160),
            QRect(1300, 300, 200, 20),
            QRect(1650, 380, 400, 20),
            QRect(1600, 530, 450, 20),
            QRect(1000, 400, 200, 20),
            QRect(1100, 600, 200, 20),
            QRect(1350, 500, 100, 20),
            QRect(20, 0, 3600, 20),
            QRect(2100, 500, 150, 20),
            QRect(2300, 430, 150, 20),
            QRect(2100, 320, 150, 20),
            QRect(2450, 20, 20, 200),
            QRect(2600, 630, 150, 20),
            QRect(2800, 580, 150, 20),
            QRect(3000, 530, 400, 20),
        };

        for (const QRect& area : areasOcupadas) {
            dibujarPared(area.x(), area.y(), area.width(), area.height(),QColorConstants::Black);
        }

        for (const QRect& rect : rectangulosNivel2) {
            dibujarPared(rect.x(), rect.y(), rect.width(), rect.height(), QColorConstants::Gray);
        }

        this->areasOcupadas = areasOcupadas + rectangulosNivel2;

        prota = new Protagonista(this,escena,2);
        prota->setPos(20, 100);
        escena->addItem(prota);

        this->centrarCam = new QTimer;
        connect(centrarCam, SIGNAL(timeout()), this,SLOT(actualizarVistaConProtagonista()));
        centrarCam->start(16);
    }

    prota->setFlag(QGraphicsItem::ItemIsFocusable);
    prota->setFocus();

    configurarFocoProtagonista();
}

nivel::~nivel(){
    if (spawnTimer) {
        spawnTimer->stop();
        delete spawnTimer;
        spawnTimer = nullptr;
    }

    if (vista) {
        vista->setParent(nullptr);
        delete vista;
        vista = nullptr;
    }

    if (escena) {
        delete escena;
        escena = nullptr;
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
    actualizarTextoEnemigosImpactados();
}
void nivel::actualizarTextoEnemigosImpactados() {
    textoEnemigosImpactados->setPlainText("Enemigos impactados: " + QString::number(enemigosImpactados) + "/10");
}

void nivel::comprobarCondiciones() {
    if (prota->getSalud() <= 0 || (prota->getMuniciones() == 0 && enemigosImpactados<10)) {
        perder = true;
        comprobacionTimer->stop();
        spawnTimer->stop();
    }
    if (enemigosImpactados >= 10) {
        ganar = true;
        comprobacionTimer->stop();
        spawnTimer->stop();
    }
    qDebug()<<"la vida es"<< this->getProtagonista()->getSalud()<<Qt::endl;


    if (ganar) {
        escena->clear();
        escena->setBackgroundBrush(QColor(QColorConstants::Black));
        QGraphicsTextItem* winText = new QGraphicsTextItem("YOU WON HIS TRUST ");
        winText->setDefaultTextColor(Qt::yellow);
        winText->setFont(QFont("Courier New", 50, QFont::Bold));
        winText->setPos(50, 800 / 2);
        escena->addItem(winText);
        finDelJuego=true;
    } else if (perder) {
        escena->clear();
        escena->setBackgroundBrush(QColor(QColorConstants::Black));
        QGraphicsTextItem* loseText = new QGraphicsTextItem("YOU LOSE");
        loseText->setDefaultTextColor(Qt::red);
        loseText->setFont(QFont("Courier New", 120, QFont::Bold));
        loseText->setPos(50, 800 / 2);
        escena->addItem(loseText);
        finDelJuego=true;
    }
}
bool nivel::getFinDelJuego(){
    return finDelJuego;
}

void nivel::actualizarVistaConProtagonista() {
    qreal posXProtagonista = prota->x();
    int anchoVista = vista->width();
    int anchoEscena = escena->width();


    qreal nuevoCentroX = posXProtagonista - anchoVista / 2.0;


    if (nuevoCentroX < 0) {
        nuevoCentroX = 0;
    } else if (nuevoCentroX + anchoVista > anchoEscena) {
        nuevoCentroX = anchoEscena - anchoVista;
    }

    vista->setSceneRect(nuevoCentroX, 0, anchoVista, escena->height());
}
