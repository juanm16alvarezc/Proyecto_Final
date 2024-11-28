#include "videojuego.h"
#include <QMessageBox>
#include <qapplication.h>
#include "ui_videojuego.h"

Videojuego::Videojuego(QWidget *parent)
    : QMainWindow(parent), nivelID(0),
    ui(new Ui::Videojuego)
{

    ui->setupUi(this);

    QPixmap background(":/imag/Menu inicial simpsons.jpg");
    background = background.scaled(ui->label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label->setPixmap(background);
    nivelActual=nullptr;
    connect(ui->nivel1Button, &QPushButton::clicked, this, &Videojuego::entrarNivel1);
    connect(ui->nivel2Button, &QPushButton::clicked, this, &Videojuego::entrarNivel2);
    connect(ui->salirButton, &QPushButton::clicked, this, &Videojuego::salirJuego);

    EndGame= new QTimer(this);
    connect(EndGame, SIGNAL(timeout()), this, SLOT(verificarFinDelJuego()));
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
    } else if (nivelID == 2) {
        QMessageBox::information(this, "Nivel 2", "Construyendo Nivel 2...");

    }
    EndGame->start(5000);
}


void Videojuego::setNivelID(int nivelID) {
    this->nivelID = nivelID;

    if (nivelActual) {
        delete nivelActual;
    }
}


void Videojuego::verificarFinDelJuego(){

    if(this->nivelActual->getFinDelJuego()){
        EndGame->stop();

        delete nivelActual;
        nivelActual= nullptr;
        ui->setupUi(this);
        QPixmap background(":/imag/Menu inicial simpsons.jpg");
        background = background.scaled(ui->label->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->label->setPixmap(background);
        ui->nivel1Button->setVisible(true);
        ui->nivel2Button->setVisible(true);
        ui->salirButton->setVisible(true);
        connect(ui->nivel1Button, &QPushButton::clicked, this, &Videojuego::entrarNivel1);
        connect(ui->nivel2Button, &QPushButton::clicked, this, &Videojuego::entrarNivel2);
        connect(ui->salirButton, &QPushButton::clicked, this, &Videojuego::salirJuego);


    }

}
