#include "videojuego.h"
#include <QMessageBox>
#include <qapplication.h>
#include "ui_videojuego.h"

Videojuego::Videojuego(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::Videojuego)
{

    ui->setupUi(this);  // Configura la interfaz de usuario

    // Conectar los botones con las funciones correspondientes
    connect(ui->nivel1Button, &QPushButton::clicked, this, &Videojuego::entrarNivel1);
    connect(ui->nivel2Button, &QPushButton::clicked, this, &Videojuego::entrarNivel2);
    connect(ui->salirButton, &QPushButton::clicked, this, &Videojuego::salirJuego);
}


Videojuego::~Videojuego()
{
    delete ui;
}


void Videojuego::entrarNivel1() {
    QMessageBox::information(this, "Nivel 1", "¡Entrando al Nivel 1!");

}


void Videojuego::entrarNivel2() {
    QMessageBox::information(this, "Nivel 2", "¡Entrando al Nivel 2!");

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

