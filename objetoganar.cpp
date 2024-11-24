#include "objetoganar.h"
#include <QGraphicsScene>


ObjetoGanar::ObjetoGanar() {
    setPixmap(QPixmap(":/imag/cadaverNoFondo.png").scaled(70, 70));

}

ObjetoGanar::~ObjetoGanar() {}


