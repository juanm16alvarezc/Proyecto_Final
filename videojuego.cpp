#include "videojuego.h"
#include <QMessageBox>
#include <qapplication.h>
#include "ui_videojuego.h"

Videojuego::Videojuego(QWidget *parent)
    : QMainWindow(parent), nivelID(0),
    ui(new Ui::Videojuego)
{

    ui->setupUi(this);

    QPixmap background(":/MenuDeOpciones.PNG");
    background = background.scaled(ui->label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(background);


    nivelActual=nullptr;
    connect(ui->nivel1Button, &QPushButton::clicked, this, &Videojuego::entrarNivel1);
    connect(ui->nivel2Button, &QPushButton::clicked, this, &Videojuego::entrarNivel2);
    connect(ui->salirButton, &QPushButton::clicked, this, &Videojuego::salirJuego);

}


Videojuego::~Videojuego()
{
    delete ui;
    if (nivelActual) {
        delete nivelActual;
    }
}


void Videojuego::entrarNivel1() {
    setNivelID(1);
    construirNivel();

}


void Videojuego::entrarNivel2() {
    setNivelID(2);
    construirNivel();

}


void Videojuego::salirJuego() {
    QMessageBox::StandardButton respuesta = QMessageBox::question(
        this, "Salir", "¿Estás seguro de que deseas salir?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (respuesta == QMessageBox::Yes) {
        QApplication::quit();
    }
}


void Videojuego::construirNivel() {

    ui->nivel1Button->setVisible(false);
    ui->nivel2Button->setVisible(false);
    ui->salirButton->setVisible(false);


    nivelActual = new nivel(nivelID);


    setCentralWidget(nivelActual->getVista());

    if (nivelID == 1) {
        QMessageBox::information(this, "Nivel 1", "Construyendo Nivel 1...");

        // prota como foco
        nivelActual->configurarFocoProtagonista();

        // añadir elementos gráficos, enemigos, etc. para el nivel 1
    } else if (nivelID == 2) {
        QMessageBox::information(this, "Nivel 2", "Construyendo Nivel 2...");

        nivelActual->configurarFocoProtagonista();

    }
    nivelActual = new nivel(nivelID);
}

void Videojuego::keyPressEvent(QKeyEvent *event) {
    if (nivelID == 1) {
        // logica para el Nivel 1
        configurarEventosNivel1(event);
    } else if (nivelID == 2) {
        // logica para el Nivel 2
        configurarEventosNivel2(event);
    }
}

void Videojuego::configurarEventosNivel1(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Up:
        //  mover al protagonista hacia arriba
        break;
    case Qt::Key_Down:
        //  mover al protagonista hacia abajo
        break;
    case Qt::Key_Left:
        //  mover al protagonista a la izquierda
        break;
    case Qt::Key_Right:
        //  mover al protagonista a la derecha
        break;
    case Qt::Key_Space:
        //  golpear
        break;
    }
}

void Videojuego::configurarEventosNivel2(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Left:
        //  mover al protagonista a la izquierda
        break;
    case Qt::Key_Right:
        //  mover al protagonista a la derecha
        break;
    case Qt::Key_Space:
        //  saltar
        break;
    }
}
void Videojuego::setNivelID(int nivelID) {
    this->nivelID = nivelID;

    if (nivelActual) {
        delete nivelActual;  // Eliminar el nivel anterior si existe
    }
}
