#include "nivel.h"
#include "protagonistagravedad.h"
#include <QGraphicsRectItem>
#include <QBrush>
#include <QImage>
#include "objetoganar.h"
#include "sierrarotatoria.h"
#include "pincho.h"
nivel::nivel(int nivelID) :nivelID(nivelID),ganar(false), perder(false),finDelJuego(false){
    escena = new QGraphicsScene();
    vista = new QGraphicsView(escena);


    if (nivelID == 1) {
        textoEnemigosImpactados = new QGraphicsTextItem("Enemigos impactados: 0/10");
        textoEnemigosImpactados->setFont(QFont("Times New Roman", 20));
        textoEnemigosImpactados->setDefaultTextColor(Qt::green);
        textoEnemigosImpactados->setPos(30, 750);
        escena->addItem(textoEnemigosImpactados);
        this->enemigosImpactados=0;
        this->maxEnemigos=10;
        this->enemigosActuales=0;
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
        connect(spawnTimer, SIGNAL(timeout()), this, SLOT(spawnearEnemigo()));
        spawnTimer->start(2000);

        comprobacionTimer = new QTimer;
        connect(comprobacionTimer, SIGNAL(timeout()), this, SLOT(comprobarCondiciones()));
        comprobacionTimer->start(1000);
        prota->setFlag(QGraphicsItem::ItemIsFocusable);
        prota->setFocus();

        configurarFocoProtagonista();

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


            QRect(0, 0, 20, 800),
            QRect(20, 186, 150, 20),

            QRect(280, 0, 20, 650),
            QRect(130, 300, 150, 20),
            QRect(20, 430, 100, 20),
            QRect(210, 430, 70, 20),
            QRect(20, 600, 150, 20),

            QRect(280, 650, 500, 20),
            QRect(460, 500, 470, 20),
            QRect(280, 600, 70, 70),

            QRect(630, 250, 30, 20),
            QRect(450, 190, 50, 20),//salto

            QRect(930, 230, 20, 70),
            QRect(930, 500, 20, 330),
            QRect(930, 710, 60, 20),
            QRect(1100, 600, -40, 20),
            QRect(780, 230, 150, 20),



            QRect(1100, 0, 20, 600),
            QRect(1050, 400, 70, 20),
            QRect(950, 280, 40, 20),

            QRect(1100, 600, 200, 20),
            QRect(1100, 470, 60, 20),
            QRect(1100, 340, 60, 20),
            QRect(1100, 210, 60, 20),
            QRect(1300, 320, 200, 20),
            QRect(1300, 200, 20, 140),

            QRect(1450, 700, 100, 100),

            QRect(1450, 200, 300, 20),
            QRect(1600, 530, 450, 20),
            QRect(1650, 380, 400, 20),

            QRect(1750, 0, 300, 400),
            QRect(1750, 530, 300, 300),


            QRect(2050, 530, 150, 20),
            QRect(2050, 330, 150, 20),
            QRect(2300, 430, 150, 20),
            QRect(2050, 130, 170, 20),
            QRect(2470, 220, -140, 20),
            QRect(2450, 20, 20, 200),


            QRect(2600, 630, 150, 20),
            QRect(2870, 530, 150, 20),


        };

        for (const QRect& area : areasOcupadas) {
            dibujarPared(area.x(), area.y(), area.width(), area.height(),QColorConstants::Black);
        }
        this->areasOcupadas = areasOcupadas;


        agregarBolsas();
        prota_ = new ProtagonistaGravedad(this,escena,2);
        prota_->setPos(30, 30);
        escena->addItem(prota_);
        prota_->setFlag(QGraphicsItem::ItemIsFocusable);
        prota_->setFocus();
        configurarFocoProtagonista_();
        comprobacionTimer = new QTimer;
        connect(comprobacionTimer, SIGNAL(timeout()), this, SLOT(comprobarCondiciones()));
        comprobacionTimer->start(1000);


        sierra = new SierraRotatoria(300, 300, 200, 1.3, 6,200,200,2000,0);
        escena->addItem(sierra);

        sierra2 = new SierraRotatoria(300, 300, 200, 1.3, 6,70,70,1100,100);
        escena->addItem(sierra2);

        sierra3 = new SierraRotatoria(300, 300, 50, 1.3, 6,40,40,330,-50);
        escena->addItem(sierra3);


        for (int x = 2100; x < 3600; x += 50) {
            Pincho* pincho = new Pincho();
            pinchos.push_back(pincho);
        }


        agregarPinchos();

        this->centrarCam = new QTimer;
        connect(centrarCam, SIGNAL(timeout()), this,SLOT(actualizarVistaConProtagonista()));
        centrarCam->start(16);



    }

}

nivel::~nivel(){
    if(nivelID==1){
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
    else if(nivelID==2){
        if (centrarCam) {
            centrarCam->stop();
            delete centrarCam;
            centrarCam = nullptr;
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
void nivel::configurarFocoProtagonista_() {

    vista->centerOn(prota_);
    prota_->setFlag(QGraphicsItem::ItemIsFocusable);
    prota_->setFocus();

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
    if (nivelID==1){
        if (prota->getSalud() <= 0 || (prota->getMuniciones() <= 0 && enemigosImpactados<10)) {
            perder = true;
            comprobacionTimer->stop();
            spawnTimer->stop();
        }
        if (enemigosImpactados >= 10) {
            ganar = true;
            comprobacionTimer->stop();
            spawnTimer->stop();
        }
        //qDebug()<<"la vida es"<< this->getProtagonista()->getSalud()<<Qt::endl;


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
            loseText->setPos(20, 800 / 2);
            escena->addItem(loseText);
            finDelJuego=true;
        }
    }
    else if(nivelID==2){
        if (prota_->getMeta()==true){
            ganar=true;
        }
        else if(prota_->getPerder()==true){
            perder=true;
        }
        if (ganar) {
            escena->setSceneRect(0, 0, 800,800);
            escena->clear();
            escena->setBackgroundBrush(QColor(QColorConstants::Black));
            QGraphicsTextItem* winText = new QGraphicsTextItem("    GOOD JOB\n NOW ENJOY YOUR\n     FREEDOM ");
            winText->setDefaultTextColor(Qt::yellow);
            winText->setFont(QFont("Courier New", 50, QFont::Bold));
            winText->setPos(50, 300);
            escena->addItem(winText);
            QTimer::singleShot(2000, this, [this]() {
                finDelJuego=true;
            });
        } else if (perder) {
            escena->setSceneRect(0, 0, 800,800);
            escena->clear();
            escena->setBackgroundBrush(QColor(QColorConstants::Black));
            QGraphicsTextItem* loseText = new QGraphicsTextItem("YOU LOSE");
            loseText->setDefaultTextColor(Qt::red);
            loseText->setFont(QFont("Courier New", 120, QFont::Bold));
            loseText->setPos(20, 800 / 2);
            escena->addItem(loseText);
            QTimer::singleShot(2000, this, [this]() {
                finDelJuego=true;
            });
        }

    }

}
bool nivel::getFinDelJuego(){
    return finDelJuego;
}

void nivel::actualizarVistaConProtagonista() {
    qreal posXProtagonista = prota_->x();
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

void nivel::agregarBolsas(){
    ObjetoGanar * bolsa= new ObjetoGanar();
    escena->addItem(bolsa);
    bolsa->setPos(450,135);
    bolsas.push_back(bolsa);
    ObjetoGanar * bolsaTwo= new ObjetoGanar();
    escena->addItem(bolsaTwo);
    bolsaTwo->setPos(1680,315);
    bolsas.push_back(bolsaTwo);
    ObjetoGanar * bolsaThree= new ObjetoGanar();
    escena->addItem(bolsaThree);
    bolsaThree->setPos(2060,65);
    bolsas.push_back(bolsaThree);
}

void nivel::agregarPinchos() {

    qDebug() << pinchos.size();
    int x = 2050;
    int altoPincho = 50;
    int yPinchos =700;

    for (auto pincho : pinchos) {
        escena->addItem(pincho);
        pincho->setPos(x, yPinchos);
        x += 50;
    }
}
