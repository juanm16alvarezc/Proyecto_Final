#include "protagonista.h"
#include <QPainter>
#include <QPixmap>
#include <QKeyEvent>
#include <qobject.h>
#include <qtimer.h>
#include "proyectil.h"

Protagonista::Protagonista(nivel* niv, QGraphicsScene* escena, int id)
    : nivelID(id), velocidad(10), indiceSprite(0), velocidadX(0), velocidadY(0),proyectilesDisponibles(12),inmune(false), Salud(100){
    if (nivelID==1){
        cargarSprites();
        textoSalud = new QGraphicsTextItem("Vida: " + QString::number(Salud));
        textoSalud->setFont(QFont("Times New Roman", 20));
        textoSalud->setDefaultTextColor(Qt::yellow);
        textoSalud->setPos(600, 740);
        escena->addItem(textoSalud);

        textoMuniciones = new QGraphicsTextItem("Municiones: " + QString::number(proyectilesDisponibles));
        textoMuniciones->setFont(QFont("Times New Roman", 20));
        textoMuniciones->setDefaultTextColor(Qt::yellow);
        textoMuniciones->setPos(600, 770);
        escena->addItem(textoMuniciones);
        Nivel=niv;
        this->mover_= new QTimer;
        this->escena= escena;
        connect(mover_,SIGNAL(timeout()),this,SLOT(mover()));
        mover_->start(80);

        inmunidadTimer = new QTimer(this);
        connect(inmunidadTimer, &QTimer::timeout, this, &Protagonista::actualizarInmunidad);

    }
}
Protagonista::Protagonista(){

}
Protagonista::~Protagonista(){
    if(mover_!=nullptr){delete mover_;}
    if(inmunidadTimer!=nullptr){delete inmunidadTimer;}
}


void Protagonista::cargarSprites() {
    QPixmap hojaSprites(":/imag/HomerSpritesAct.png");

    //  sprites en la hoja
    int anchoOriginalSprite = 65;
    int altoOriginalSprite = 140;

    int nuevoAncho = 64/1.3;
    int nuevoAlto = 128/1.3;


    int framesPorDireccion = 2;

    // Cargar los sprites de derecha (2 frames)
    for (int i = 0; i < framesPorDireccion; ++i) {
        if(i==0){
            QPixmap spriteDerecha = hojaSprites.copy(i * anchoOriginalSprite+100, altoOriginalSprite, anchoOriginalSprite, altoOriginalSprite);
            spritesDerecha.append(spriteDerecha.scaled(nuevoAncho, nuevoAlto, Qt::KeepAspectRatio, Qt::SmoothTransformation));

        }
        else if(i==1){
            QPixmap spriteDerecha = hojaSprites.copy(4.5*i * anchoOriginalSprite+100, altoOriginalSprite, anchoOriginalSprite, altoOriginalSprite);
            spritesDerecha.append(spriteDerecha.scaled(nuevoAncho, nuevoAlto, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }

    // Cargar los sprites de izquierda (2 frames) (volteados horizontalmente)
    for (int i = 0; i < framesPorDireccion; ++i) {
        if(i==0){
            QPixmap spriteIzquierda = hojaSprites.copy(i * anchoOriginalSprite+100, altoOriginalSprite, anchoOriginalSprite, altoOriginalSprite);
            QPixmap spriteIzquierdaVolteado = spriteIzquierda.transformed(QTransform().scale(-1, 1)); // Volteo horizontal
            spritesIzquierda.append(spriteIzquierdaVolteado.scaled(nuevoAncho, nuevoAlto, Qt::KeepAspectRatio, Qt::SmoothTransformation));

        }
        else if(i==1){
            QPixmap spriteIzquierda = hojaSprites.copy(4.5*i * anchoOriginalSprite+100, altoOriginalSprite, anchoOriginalSprite, altoOriginalSprite);
            QPixmap spriteIzquierdaVolteado = spriteIzquierda.transformed(QTransform().scale(-1, 1)); // Volteo horizontal
            spritesIzquierda.append(spriteIzquierdaVolteado.scaled(nuevoAncho, nuevoAlto, Qt::KeepAspectRatio, Qt::SmoothTransformation));

        }
    }
    for (int i = 0; i < framesPorDireccion; ++i) {

        QPixmap spriteGolpe = hojaSprites.copy(17.8 * anchoOriginalSprite, altoOriginalSprite * 8.7, anchoOriginalSprite, altoOriginalSprite);
        spritesGolpeDerecha.append(spriteGolpe.scaled(nuevoAncho, nuevoAlto, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    for (int i = 0; i < framesPorDireccion; ++i) {
        QPixmap spriteGolpe = hojaSprites.copy(17.8 * anchoOriginalSprite, altoOriginalSprite * 8.7, anchoOriginalSprite, altoOriginalSprite);
        QPixmap spriteGolpeIzquierda = spriteGolpe.transformed(QTransform().scale(-1, 1));  // voltear horizontal
        spritesGolpeIzquierda.append(spriteGolpeIzquierda.scaled(nuevoAncho, nuevoAlto, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    setPixmap(spritesDerecha[0]);
}


void Protagonista::moverArriba() {
    if (ultimaDireccion=="Izquierda"){

        setPos(x(), y() - velocidad);
        if (!detectarColisiones()) {
            setPixmap(spritesIzquierda[indiceSprite]);
            setPos(x(), y() + velocidad);
        } else {
            setPixmap(spritesIzquierda[indiceSprite]);
            indiceSprite = (indiceSprite + 1) % spritesIzquierda.size();
        }
    }
    else{
        setPos(x(), y() - velocidad);
        if (!detectarColisiones()) {
            setPixmap(spritesDerecha[indiceSprite]);
            setPos(x(), y() + velocidad);
        } else {
            setPixmap(spritesDerecha[indiceSprite]);
            indiceSprite = (indiceSprite + 1) % spritesDerecha.size();
        }

    }
    ultimaDireccion="Arriba";
}

void Protagonista::moverAbajo() {
    if (ultimaDireccion=="Izquierda"){

        setPos(x(), y() + velocidad);
        if (!detectarColisiones()) {
            setPixmap(spritesIzquierda[indiceSprite]);
            setPos(x(), y() - velocidad);
        } else {
            setPixmap(spritesIzquierda[indiceSprite]);
            indiceSprite = (indiceSprite + 1) % spritesIzquierda.size();
        }
    }
    else{
        setPos(x(), y() + velocidad);
        if (!detectarColisiones()) {
            setPixmap(spritesDerecha[indiceSprite]);
            setPos(x(), y() - velocidad);
        } else {
            setPixmap(spritesDerecha[indiceSprite]);
            indiceSprite = (indiceSprite + 1) % spritesDerecha.size();
        }

    }
    ultimaDireccion="Abajo";
}

void Protagonista::moverIzquierda() {
    setPos(x() - velocidad, y());
    if (!detectarColisiones()) {
        setPixmap(spritesIzquierda[indiceSprite]);
        setPos(x() + velocidad, y());
    } else {
        setPixmap(spritesIzquierda[indiceSprite]);
        indiceSprite = (indiceSprite + 1) % spritesIzquierda.size();
    }
    ultimaDireccion = "Izquierda";
}

void Protagonista::moverDerecha() {
    setPos(x() + velocidad, y());
    if (!detectarColisiones()) {
        setPixmap(spritesDerecha[indiceSprite]);
        setPos(x() - velocidad, y());
    } else {
        setPixmap(spritesDerecha[indiceSprite]);
        indiceSprite = (indiceSprite + 1) % spritesDerecha.size();
    }
    ultimaDireccion = "Derecha";
}
void Protagonista::golpear(){
    if (ultimaDireccion == "Derecha" || ultimaDireccion == "Arriba") {
        setPixmap(spritesGolpeDerecha[indiceSprite]);
    } else if (ultimaDireccion == "Izquierda"|| ultimaDireccion == "Abajo") {
        setPixmap(spritesGolpeIzquierda[indiceSprite]);
    }

    if (proyectilesDisponibles <= 0) {
        return;
    }

    indiceSprite = (indiceSprite + 1) % spritesGolpeDerecha.size();
    qreal direccionX = 0;
    qreal direccionY = 0;
    if (ultimaDireccion == "Derecha") {
        direccionX = 1;
    } else if (ultimaDireccion == "Izquierda") {
        direccionX = -1;
    }else if (ultimaDireccion=="Arriba"){
        direccionY=-1;
    }else if (ultimaDireccion=="Abajo"){
        direccionY=1;
    }
    Proyectil* proyectil = new Proyectil(x() + boundingRect().width() / 2,y() + boundingRect().height() / 2, direccionX, direccionY, Nivel);
    escena->addItem(proyectil);

}
void Protagonista::reducirMuniciones(){
    proyectilesDisponibles--;
}

void Protagonista::keyPressEvent(QKeyEvent *event) {
    if (nivelID==1){
        switch (event->key()) {
        case Qt::Key_Up:
            velocidadY=-velocidad;
            velocidadX=0;
            break;
        case Qt::Key_Down:
            velocidadY=velocidad;
            velocidadX=0;
            break;
        case Qt::Key_Left:
            velocidadX=-velocidad;
            velocidadY=0;
            break;
        case Qt::Key_Right:
            velocidadX=velocidad;
            velocidadY=0;
            break;
        case Qt::Key_Space:
            velocidadX=0;
            velocidadY=0;
            this->golpear();
            break;
        }
    }

}




bool Protagonista::detectarColisiones() {
    if (nivelID==1){
        int n = collidingItems().size();
        if (n > 0) {
            return false;
        }
        return true;
    }
}


void Protagonista::mover(){
    if(nivelID==1){
        if (velocidadY>0){
            this->moverAbajo();
        }
        if (velocidadY<0){
            this->moverArriba();
        }
        if (velocidadX>0){
            this->moverDerecha();
        }
        if (velocidadX<0){
            this->moverIzquierda();
        }

    }
}

void Protagonista::recibirDanio(int cantidad) {
    if (estaInmune()) return;

    Salud -= cantidad;
    if(Salud<0){
        Salud=0;
    }
    qDebug() << "Vid" << Salud;
    inmune = true;
    inmunidadTimer->start(500);
    actualizarTextoSalud();

}

bool Protagonista::estaInmune() const {
    return inmune;
}

void Protagonista::actualizarInmunidad() {
    inmune = false;
    inmunidadTimer->stop();
}

int Protagonista::getSalud() const{
    return Salud;
}
int Protagonista::getMuniciones() const {
    return proyectilesDisponibles;
}

void Protagonista::actualizarTextoSalud() {
    textoSalud->setPlainText("Vida: " + QString::number(Salud));
}

void Protagonista::actualizarTextoMuniciones() {
    textoMuniciones->setPlainText("Municiones: " + QString::number(proyectilesDisponibles));
}

