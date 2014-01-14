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
    void updateScore(QString score);
    void updateUnitCount(QString count);
public slots:
    void setAbilitySlot(int id);
    void unitUse(Unit *unit);
    void unitDie(Unit *unit);
private slots:
    void gameTimer();
    void startGame();
    void toggleGame(bool _play);

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

    //Configuration partie
    int unitCount;
    int unitDead = 0;
    int unitUsed = 0;
    int unitMinima;
    int unitToInit;

    bool play;

    int score; //Score = (total-minima / survivants) *1000 - 50*deces
              //Score initial

    //Tableaux des images des composants
    QList<QPixmap*> *unitImages;
    QList<QPixmap*> *boostImages;
    QList<QPixmap*> *caillotImages;
    QList<QPixmap*> *deviationImages;

    void calculateScore();
    void loadImages();
    void initializeGame();
    void deleteImages(QList<QPixmap*> *list);
    void deleteUnits(QList<Unit *> *list);
};

#endif // RENDER_H
