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

const QString GameSoundPlayer::SOUND_IN_GAME = "/ressources/sounds/in_game.wav";
const QString GameSoundPlayer::SOUND_MENU = "/ressources/sounds/HumanHeartBeat.wav"; //TODO

GameSoundPlayer::GameSoundPlayer(QString sound, Option *option, bool loop, QWidget *parent) : QWidget(parent)
{
    currentDir = QApplication::applicationDirPath();

    player = new QMediaPlayer();
    qDebug() << "vol from option: " << option->getVolume();
    player->setVolume(option->getVolume());
    player->setMuted(option->isMute());
    player->setMedia(QMediaContent(QUrl::fromLocalFile(currentDir+sound)));
    qDebug() << "vol from player: " << player->volume();
    qDebug() << player->isMuted();
    qDebug() << currentDir+sound;

    if(loop)
    {
        QMediaPlaylist *playlist = new QMediaPlaylist();
        playlist->addMedia(player->media());
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        player->setPlaylist(playlist);
    }
}

GameSoundPlayer::~GameSoundPlayer()
{
    //playlist
    //player
}

void GameSoundPlayer::setMuted(bool muted)
{
    player->setMuted(muted);
}

void GameSoundPlayer::play()
{
    player->play();
}

void GameSoundPlayer::stop()
{
    player->stop();
}

void GameSoundPlayer::pause()
{
    player->pause();
}
