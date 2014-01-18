#include "gamesoundplayer.h"
#include <QMediaPlayer>

#include <QMediaPlaylist>

#include "option.h"

#include <QDebug>

const QString GameSoundPlayer::GAME_STARTED = "/ressources/sounds/game_started.wav";
const QString GameSoundPlayer::UNIT_KILLED = "/ressources/sounds/gamestarted.wav"; //TODO
const QString GameSoundPlayer::ENEMY_KILLED = "/ressources/sounds/gamestarted.wav";//TODO
const QString GameSoundPlayer::GAME_OVER = "/ressources/sounds/gamestarted.wav"; //TODO
const QString GameSoundPlayer::TRAP_DISABLED = "/ressources/sounds/trap_disabled.wav";
const QString GameSoundPlayer::ABILITY_ENABLED = "/ressources/sounds/chop.wav"; //TODO

const QString GameSoundPlayer::SOUND_IN_GAME = "/ressources/sounds/trap_disabled.wav";
const QString GameSoundPlayer::SOUND_MENU = "/ressources/sounds/HumanHeartBeat.wav"; //TODO

GameSoundPlayer::GameSoundPlayer(QString sound, Option *option, bool loop, QWidget *parent) : QWidget(parent)
{



    /*player = new QMediaPlayer();
    player->setVolume(option->getVolume());
    player->setMuted(option->isMute());
    player->setMedia(QMediaContent(QUrl::fromLocalFile(currentDir+sound)));

    if(loop)
    {
        QMediaPlaylist *playlist = new QMediaPlaylist();
        playlist->addMedia(player->media());
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        player->setPlaylist(playlist);
    }*/


}

GameSoundPlayer::GameSoundPlayer(Option *option, QWidget *parent) : QWidget(parent)
{
    playerList = new QList<QMediaPlayer*>();
    backgroundPlayer = new QMediaPlayer();
    playerList->append(backgroundPlayer);
    currentDir = QApplication::applicationDirPath();
    backgroundPlaylist = new QMediaPlaylist();

    backgroundPlaylist->addMedia(QMediaContent(QUrl::fromLocalFile(currentDir+SOUND_MENU)));
    backgroundPlaylist->addMedia(QMediaContent(QUrl::fromLocalFile(currentDir+SOUND_IN_GAME)));
    backgroundPlaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    backgroundPlaylist->setCurrentIndex(0);



     qDebug() << "Playlist yolo" << currentDir+SOUND_MENU;
    this->option = option;
    qDebug() << "Playlist yolo";
    backgroundPlayer->setPlaylist(backgroundPlaylist);
    backgroundPlayer->setVolume(option->getVolume());
    backgroundPlayer->setMuted(option->isMute());
    qDebug() << "Play background bitch0";
    backgroundPlayer->play();
    qDebug() << "Play background bitch";
}

GameSoundPlayer::~GameSoundPlayer()
{
    //playlist
    //player
}

void GameSoundPlayer::playSound(QString sound)
{
    currentDir = QApplication::applicationDirPath();

    QMediaPlayer *soundPlayer = new QMediaPlayer();
    playerList->append(soundPlayer);

    soundPlayer->setVolume(option->getVolume());
    soundPlayer->setMuted(option->isMute());
    soundPlayer->setMedia(QMediaContent(QUrl::fromLocalFile(currentDir+sound)));

    soundPlayer->play();
}

void GameSoundPlayer::setMuted(bool muted)
{
    //backgroundPlaylist->currentMedia()

}


// mode = 0 -> menus et mode = 1 -> in game
void GameSoundPlayer::setMode(SoundMode mode)
{
    switch (mode) {
    case GameSoundPlayer::menu:
        backgroundPlaylist->setCurrentIndex(0);
        break;
    case GameSoundPlayer::in_game:
        backgroundPlaylist->setCurrentIndex(1);
        break;

    }
    backgroundPlayer->playlist()->next();
    //qDeleteAll(*playerList);
}

