#ifndef PROTAGONISTA_H
#define PROTAGONISTA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
class nivel;



class Protagonista : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public slots:
    void mover();
private slots:
    void actualizarInmunidad();
public:
    explicit Protagonista(nivel *niv, QGraphicsScene *escena, int nivelID);

    void extracted();
    ~Protagonista();

    void moverArriba();
    void moverAbajo();
    void moverIzquierda();
    void moverDerecha();
    void golpear();
    void cargarSprites();
    void keyPressEvent(QKeyEvent *event);
    void configurarEventosNivel1(QKeyEvent *event);
    void configurarEventosNivel2(QKeyEvent *event);
    bool detectarColisiones() ;
    void recibirDanio(int cantidad);
    bool estaInmune() const;
    int getSalud() const;
    int getMuniciones() const;

private:
    int velocidad, velocidadX,velocidadY,Salud,nivelID;
    QVector<QPixmap> spritesIzquierda,spritesDerecha,spritesGolpeDerecha,spritesGolpeIzquierda;
    int indiceSprite = 0;
    QString ultimaDireccion;
    QTimer* mover_;
    QGraphicsScene * escena;
    int proyectilesDisponibles;
    bool inmune;
    QTimer* inmunidadTimer;
    nivel *Nivel;
};

#endif // PROTAGONISTA_H
