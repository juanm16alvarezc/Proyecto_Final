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

public: //metodos
    explicit Protagonista(nivel *niv, QGraphicsScene *escena, int nivelID);
    Protagonista();
    ~Protagonista();
    void moverIzquierda();
    void moverDerecha();
    void cargarSprites();
    int getSalud() const;
    int getMuniciones() const;
    void recibirDanio(int cantidad);
    void moverAbajo();
    void moverArriba();
    void golpear();
    bool detectarColisiones() ;
    bool estaInmune() const;
    void actualizarTextoSalud();
    void actualizarTextoMuniciones();
    void saltar();
private: //atributos
    void keyPressEvent(QKeyEvent *event);
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
