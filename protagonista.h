#ifndef PROTAGONISTA_H
#define PROTAGONISTA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
class nivel;



class Protagonista : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

private slots:
    void actualizarInmunidad();
    void mover();

public: //metodos
    explicit Protagonista(nivel *niv, QGraphicsScene *escena, int nivelID);
    Protagonista();
    ~Protagonista();
    void cargarSprites();
    int getSalud() const;
    int getMuniciones() const;
    void recibirDanio(int cantidad);
    void golpear();
    bool estaInmune() const;
    void saltar();
    void reducirMuniciones();
    void actualizarTextoSalud();
    void actualizarTextoMuniciones();
private: //atributos
    void moverIzquierda();
    void moverDerecha();
    void moverAbajo();
    void moverArriba();
    void keyPressEvent(QKeyEvent *event);
    bool detectarColisiones();
    int Salud;
    QVector<QPixmap> spritesGolpeDerecha,spritesGolpeIzquierda;
    int proyectilesDisponibles;
    bool inmune;
    QTimer* inmunidadTimer;
    QGraphicsTextItem *textoSalud;
    QGraphicsTextItem *textoMuniciones;
public://atributos
    QString ultimaDireccion;
    QGraphicsScene * escena;
    int velocidad, velocidadX,velocidadY,nivelID;
    QVector<QPixmap> spritesIzquierda,spritesDerecha;
    int indiceSprite = 0;
    QTimer* mover_;
    nivel *Nivel;
};

#endif // PROTAGONISTA_H
