#include "inicioSesion.h"
#include "ui_inicioSesion.h"
#include <qpushbutton.h>

#include <QDebug>
#include <QFileInfo>

InicioSesion::InicioSesion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InicioSesion),
    loggedIn(false)
{
    ui->setupUi(this);
    connect(ui->btnIniciarSesion, &QPushButton::clicked, this, &InicioSesion::on_buttonIniciarSesion_clicked);
    connect(ui->btnRegistrar, &QPushButton::clicked, this, &InicioSesion::on_buttonRegistrar_clicked );
    ui->lineEditContrasena->setEchoMode(QLineEdit::Password);
}

InicioSesion::~InicioSesion()
{
    delete ui;
}

bool InicioSesion::verificarUsuario(const QString& usuario, const QString& contrasena) {
    QFile archivo("../usuarios.txt");

    if (archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&archivo);
        QString linea;

        while (!in.atEnd()) {
            linea = in.readLine();
            QStringList datos = linea.split(":");
            if (datos[0] == usuario && datos[1] == contrasena) {
                archivo.close();
                return true;
            }
        }
        archivo.close();
    }

    return false;
}


#include <QDebug>
#include <QFileInfo>

bool InicioSesion::registrarUsuario(const QString& usuario, const QString& contrasena) {
    QFile archivo("../usuarios.txt");

    if (!archivo.exists()) {
        qDebug() << "El archivo usuarios.txt no existe en la ruta:" << QFileInfo(archivo).absoluteFilePath();
    } else {
        qDebug() << "El archivo usuarios.txt fue encontrado en la ruta:" << QFileInfo(archivo).absoluteFilePath();
    }

    if (archivo.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&archivo);
        out << usuario << ":" << contrasena << "\n";
        archivo.close();
        return true;
    }

    qDebug() << "No se pudo abrir el archivo para escritura.";
    return false;
}

void InicioSesion::on_buttonIniciarSesion_clicked() {
    QString usuario = ui->lineEditUsuario->text();
    QString contrasena = ui->lineEditContrasena->text();

    if (verificarUsuario(usuario, contrasena)) {
        loggedIn = true;
        QMessageBox::information(this, "Éxito", "Inicio de sesión correcto.");
        accept();
    } else {
        QMessageBox::warning(this, "Error", "Usuario o contraseña incorrectos.");
    }
}

void InicioSesion::on_buttonRegistrar_clicked() {
    QString usuario = ui->lineEditUsuario->text();
    QString contrasena = ui->lineEditContrasena->text();


    registrarUsuario(usuario, contrasena);
}

void InicioSesion::guardarUsuario(const QString &usuario, const QString &contrasena)
{
    QString rutaArchivo = "../usuarios.txt";
    QFile archivo(rutaArchivo);

    if (!archivo.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo guardar el usuario en el archivo.");
        return;
    }

    QTextStream out(&archivo);
    out << usuario << "," << contrasena << "\n";
    archivo.close();

    QMessageBox::information(this, "Guardado", "Usuario registrado correctamente en: " + rutaArchivo);
}


