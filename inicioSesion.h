#ifndef INICIOSESION_H
#define INICIOSESION_H

#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <QString>
#include <QTextStream>
#include "ui_inicioSesion.h"

namespace Ui {
class InicioSesion;
}

class InicioSesion : public QDialog
{
    Q_OBJECT

public:
    explicit InicioSesion(QWidget *parent = nullptr);
    ~InicioSesion();

    bool isLoggedIn() const { return loggedIn; }

private slots:
    void on_buttonIniciarSesion_clicked();
    void on_buttonRegistrar_clicked();

private:
    Ui::InicioSesion *ui;
    bool loggedIn;

    bool verificarUsuario(const QString &usuario, const QString &contrasena);
    bool registrarUsuario(const QString &usuario, const QString &contrasena);
    void guardarUsuario(const QString &usuario, const QString &contrasena);
};

#endif // INICIOSESION_H
