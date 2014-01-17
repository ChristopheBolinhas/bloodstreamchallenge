#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
class AbilityButton;
class VolumeButton;
class PlayPauseButton;
class CloseButton;
class QLabel;
class EndGameInfos;
class MenuButton;
class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameView(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    void update();
    void setMode(int mode);
    void wheelEvent ( QWheelEvent * event )
    {
    //None
    }
signals:
    void sendAbility(int id);
    void closeRender();
    void pauseGame(bool pause);
    void setScore(QString score);
    void setUnitCount(QString count);
public slots:

    void setEndGame(bool victory);
    void setStartInfo(int step);
private:
    AbilityButton *abi1;
    AbilityButton *abi2;
    AbilityButton *abi3;
    AbilityButton *abi4;
    AbilityButton *abi5;
    VolumeButton *volume;
    PlayPauseButton *playButton;
    CloseButton *closeButton;
    QLabel *score;
    QLabel *unitsCount;
    QLabel *scoreInfo;
    QLabel *unitInfo;
    QLabel *startLabel;
    QList<QPixmap*> *acidImg;
    QList<QPixmap*> *bridgeImg;
    QList<QPixmap*> *deviationImg;
    QList<QPixmap*> *iceImg;
    QList<QPixmap*> *spikeImg;

    //Ecran de fin de partie
    /*QLabel *endGameResult;
    QLabel *endGameScore;
    QLabel *endGameScoreValue;
    MenuButton *endGameRestart;
    MenuButton *endGameMenu;*/
    bool endGame;




    void loadHudImages();
    void loadHudElements();
};

#endif // GAMEVIEW_H
