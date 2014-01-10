#ifndef RENDER_H
#define RENDER_H

#include <QWidget>
#include <QGraphicsScene>
class QGraphicsView;
class QGraphicsItemGroup;
class QTimer;
class MapSquare;
class Level;
class Unit;
class Obstacle;
class QTimer;
class GameView;
class Render : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit Render(GameView *_view, Level *level, QWidget *parent = 0);
    ~Render();
signals:
    void moveUnits();
public slots:
    void setAbilitySlot(int id);
private slots:
    void updateCenter();
    void startGame();
    void toggleGame();

private:
    //QGraphicsItemGroup *units;
    MapSquare* generatePath(int currentX, int currentY, Level *level);
    Level *renderedLevel;
    GameView *view;
    QList<Unit*> *listUnit;
    Unit *mainUnit;
    QTimer *mainTimer;
    QTimer *startTimer;
    int startCountDown = 3;
    void keyPressEvent(QKeyEvent *event);
    int xFromOrientation(int x, int orientation);
    int yFromOrientation(int y, int orientation);

    //Tableaux des images des composants
    QList<QPixmap*> *unitImages;
    QList<QPixmap*> *boostImages;
    QList<QPixmap*> *caillotImages;
    QList<QPixmap*> *deviationImages;


    void loadImages();
};

#endif // RENDER_H
