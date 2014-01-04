#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
class AbilityButton;
class VolumeButton;
class PlayPauseButton;
class CloseButton;
class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameView(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    void update();
    void setMode(int mode);
signals:
    void sendAbility(int id);
    void closeRender();
public slots:

private:
    AbilityButton *abi1;
    VolumeButton *volume;
    PlayPauseButton *playButton;
    CloseButton *closeButton;

};

#endif // GAMEVIEW_H
