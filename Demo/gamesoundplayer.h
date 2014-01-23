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
    static const QString BOOST_USE;
    static const QString CHUTE_USE;
    static const QString DEVIATION_USE;
    static const QString BACTERIE_USE;
    static const QString CAILLOT_USE;
    static const QString DEATH_UNIT;

    // Sons d'ambiance
    static const QString SOUND_MENU;
    static const QString SOUND_IN_GAME;
    enum SoundMode {menu, in_game};
    void setMode(SoundMode mode);


public slots:
    void setMuted(bool muted);
    void setSound(int volume, bool muted);
private:
    QList<QMediaPlayer*> *playerList;
    QMediaPlaylist *backgroundPlaylist;
    Option *option;
    QMediaPlayer *backgroundPlayer;
    QString currentDir;
    int volume;
    bool muted;


};

#endif // GAMESOUNDPLAYER_H
