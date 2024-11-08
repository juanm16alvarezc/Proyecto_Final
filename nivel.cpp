#include "nivel.h"
#include <QGraphicsRectItem>  // ejemplos
#include <QBrush>
#include <QImage>

nivel::nivel(int nivelID) {
    // Crear la escena y vista
    escena = new QGraphicsScene();
    vista = new QGraphicsView(escena);

    if (nivelID == 1) {
        vista->setFixedSize(800,800);  // Tamaño de la vista
        escena->setSceneRect(0, 0, 800,800);  // Tamaño de la escena


        QImage fondo(":/imag/BackGroundCarcel.jpg");
        fondo = fondo.scaled(800, 800, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        // Establecer la imagen escalada como fondo de la escena
        escena->setBackgroundBrush(QBrush(fondo));


        prota = new Protagonista();
        prota->setPos(0, 0);
        escena->addItem(prota);



        // Ejemplo de enemigo
        Enemigo* enemigo1 = new Enemigo();
        enemigo1->setPos(400, 300);
        enemigos.push_back(enemigo1);
        escena->addItem(enemigo1);

    } else if (nivelID == 2) {


        escena->setSceneRect(0, 0, 1024, 768);
        vista->setFixedSize(1024, 768);
        escena->setBackgroundBrush(QBrush(QImage(":/../../../Downloads/BackGroundNoche.png")));

        // Agregar protagonista y enemigos específicos del nivel 2
        prota = new Protagonista();
        prota->setPos(200, 400);
        escena->addItem(prota);

        Enemigo* enemigo2 = new Enemigo();
        enemigo2->setPos(500, 400);
        enemigos.push_back(enemigo2);
        escena->addItem(enemigo2);
    }

    // Configurar el foco en el protagonista
    configurarFocoProtagonista();
}

void nivel::configurarFocoProtagonista() {
    if (prota) {
        vista->centerOn(prota);
        prota->setFlag(QGraphicsItem::ItemIsFocusable);
        prota->setFocus();
    }
}

QGraphicsScene *nivel::getEscena(){
    return escena;
}

QGraphicsView *nivel::getVista(){
    return vista;
}
