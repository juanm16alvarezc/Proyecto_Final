#include "protagonistagravedad.h"
#include <qevent.h>
#include "objetoganar.h"
#include "pincho.h"
#include "sierrarotatoria.h"

ProtagonistaGravedad::ProtagonistaGravedad(nivel *niv, QGraphicsScene *escena, int nivelID)
    :aceleracionY(9.8), enSuelo(false),llegarMeta(false),Perder(false),objetosRecolectados(0){

    this->nivelID=nivelID;
    this->escena=escena;
    this->Nivel=niv;
    this->velocidad=15;
    this->velocidadX=0;
    this->velocidadY=0;
    this->mover_= new QTimer;
    this->TimerG= new QTimer;
    this->TimerMeta= new QTimer;
    int anchoOriginalSprite = 65;
    int altoOriginalSprite = 140;

    int nuevoAncho = 64/1.3;
    int nuevoAlto = 128/1.3;
    int framesPorDireccion = 2;
    QPixmap hojaSprites(":/imag/HomerSpritesAct.png");
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
    setPixmap(spritesDerecha[0]);
    connect(mover_,SIGNAL(timeout()),this,SLOT(moverTwo()));
    mover_->start(80);
    connect(TimerG,SIGNAL(timeout()), this, SLOT(actualizarMovimiento()));
    TimerG->start(50);
    connect(TimerMeta,SIGNAL(timeout()),this,SLOT(comprobarMeta()));
    TimerMeta->start(30);
}

ProtagonistaGravedad::~ProtagonistaGravedad() {
}

void ProtagonistaGravedad::actualizarMovimiento() {
    if (!enSuelo) {
        velocidadY += aceleracionY*0.25 ;
    }

    if (ultimaDireccion=="Izquierda"){

        setPos(x(), y() + velocidadY);
         if (!detectarColisiones()) {
            setPos(x(), y() - velocidadY);
            velocidadY=0;
            enSuelo=true;
        } else {
            enSuelo=false;
        }
    }
    else{
        setPos(x(), y() + velocidadY);
        if (!detectarColisiones()) {
            setPos(x(), y() - velocidadY);
            velocidadY=0;
            enSuelo=true;
        } else {
            enSuelo=false;
        }
    }
    ultimaDireccion="Abajo";

}

void ProtagonistaGravedad::saltar() {
    //if (enSuelo) {
        velocidadY = -30;
        enSuelo = false;
   // }
}

void ProtagonistaGravedad::keyPressEvent(QKeyEvent *event) {

    if(nivelID==2){
        switch (event->key()) {
        case Qt::Key_Left:
            velocidadX=-velocidad;
            break;
        case Qt::Key_Right:
            velocidadX=velocidad;
            break;


        case Qt::Key_Down:
            velocidadX=0;
            break;

        case Qt::Key_Space:
            this->saltar();
            break;
        }
    }
}
void ProtagonistaGravedad::moverTwo(){

   if(nivelID==2){
        if (velocidadX>0){
            this->moverDerecha();
        }
        if (velocidadX<0){
            this->moverIzquierda();
        }

    }
}

void ProtagonistaGravedad::comprobarMeta() {
    qDebug() << y();
    if (x() > 2870 && y()<=430 && objetosRecolectados >= totalObjetosParaGanar) {
        llegarMeta = true;
        TimerMeta->stop();
        qDebug() << "meta alcanzada";
    }
}
bool ProtagonistaGravedad::getMeta() const{
    return llegarMeta;
}
bool ProtagonistaGravedad::getPerder() {
    //qDebug() << Perder;
    return Perder;
}
void ProtagonistaGravedad::setPerder(bool P){
    TimerG->stop();
    mover_->stop();
    TimerMeta->stop();
    Perder=P;
    qDebug() << "perdiste";
}

void ProtagonistaGravedad::recolectarObjeto() {
    objetosRecolectados++;
}
bool ProtagonistaGravedad::detectarColisiones() {
    if (nivelID==2){
        for (QGraphicsItem* item : collidingItems()) {
            if (ObjetoGanar* bolsa = dynamic_cast<ObjetoGanar*>(item)) {
             recolectarObjeto();
             scene()->removeItem(bolsa);
             delete bolsa;
             bolsa=nullptr;

            }
            if (SierraRotatoria* sierra=dynamic_cast<SierraRotatoria*>(item)) {
                setPerder(true);
            }
            if (Pincho* pincho= dynamic_cast<Pincho*>(item)) {
                setPerder(true);
            }

        }
        int n = collidingItems().size();
        if (n > 0) {
            return false;
        }
        return true;
    }
}

void ProtagonistaGravedad::moverIzquierda() {
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

void ProtagonistaGravedad::moverDerecha() {
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


