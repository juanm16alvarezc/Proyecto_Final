#include "pincho.h"
#include <QGraphicsPixmapItem>
#include <qgraphicsscene.h>


Pincho::Pincho() {
    setPixmap(QPixmap(":/imag/pincho-removebg-preview.png").scaled(80, 80));
}
