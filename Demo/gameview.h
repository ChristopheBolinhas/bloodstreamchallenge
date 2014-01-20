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
    void setMode(int mode, bool sound);
    void wheelEvent ( QWheelEvent * event );
signals:
    void sendAbility(int id);
    void closeRender();
    void pauseGame(bool pause);
    void setScore(QString score);
    void setUnitCount(QString count);
    void setSound(bool mute);
public slots:
    void setStartInfo(int step);
private:
    AbilityButton *abi1;
    AbilityButton *abi2;
    AbilityButton *abi3;
    AbilityButton *abi4;
    AbilityButton *abi5;
    VolumeButton *volumeButton;
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

    bool endGame;

    void loadHudImages();
    void loadHudElements();
};

#endif // GAMEVIEW_H
