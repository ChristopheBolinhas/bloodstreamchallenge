#ifndef GAMESOUNDPLAYER_H
#define GAMESOUNDPLAYER_H

#include <QtWidgets>
#include <QMediaPlayer>

class Option;
class GameSoundPlayer : public QWidget
{
    Q_OBJECT
public:
    GameSoundPlayer(Option *option, QWidget *parent = 0);
    ~GameSoundPlayer();

    void playSound(QString sound);
    // Bruitages
    static const QString GAME_STARTED;
    static const QString UNIT_KILLED;
    static const QString ENEMY_KILLED;
    static const QString GAME_OVER;
    static const QString TRAP_DISABLED;
    static const QString ABILITY_ENABLED;

    // Sons d'ambiance
    static const QString SOUND_MENU;
    static const QString SOUND_IN_GAME;
    enum SoundMode {menu, in_game};
    void setMode(SoundMode mode);


public slots:
    void setMuted(bool muted);

private:
    QList<QMediaPlayer*> *playerList;
    QMediaPlaylist *backgroundPlaylist;
    Option *option;
    QMediaPlayer *backgroundPlayer;
    QString currentDir;

};

#endif // GAMESOUNDPLAYER_H
