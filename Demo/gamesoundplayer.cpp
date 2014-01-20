#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDebug>

#include "gamesoundplayer.h"
#include "option.h"


const QString GameSoundPlayer::GAME_STARTED = "/ressources/sounds/game_started.wav";
const QString GameSoundPlayer::UNIT_KILLED = "/ressources/sounds/gamestarted.wav"; //TODO
const QString GameSoundPlayer::ENEMY_KILLED = "/ressources/sounds/gamestarted.wav";//TODO
const QString GameSoundPlayer::GAME_OVER = "/ressources/sounds/gamestarted.wav"; //TODO
const QString GameSoundPlayer::TRAP_DISABLED = "/ressources/sounds/trap_disabled.wav";
const QString GameSoundPlayer::ABILITY_ENABLED = "/ressources/sounds/chop.wav"; //TODO

const QString GameSoundPlayer::SOUND_IN_GAME = "/ressources/sounds/ingamesound.wav";
const QString GameSoundPlayer::SOUND_MENU = "/ressources/sounds/HumanHeartBeat.wav"; //TODO

GameSoundPlayer::GameSoundPlayer(Option *option, QWidget *parent) : QWidget(parent)
{
    this->option = option;
    currentDir = QApplication::applicationDirPath();

    backgroundPlayer = new QMediaPlayer();
    playerList = new QList<QMediaPlayer*>();

    backgroundPlaylist = new QMediaPlaylist();

    backgroundPlaylist->addMedia(QMediaContent(QUrl::fromLocalFile(currentDir+SOUND_MENU)));
    //backgroundPlaylist->addMedia(QMediaContent(QUrl::fromLocalFile(currentDir+SOUND_IN_GAME)));
    backgroundPlaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    backgroundPlaylist->setCurrentIndex(0);
    backgroundPlayer->setPlaylist(backgroundPlaylist);
    backgroundPlayer->setVolume(option->getVolume());
    backgroundPlayer->setMuted(option->isMute());
    backgroundPlayer->play();

}

GameSoundPlayer::~GameSoundPlayer()
{
}

void GameSoundPlayer::playSound(QString sound)
{
    QMediaPlayer *soundPlayer = new QMediaPlayer();
    playerList->append(soundPlayer);

    soundPlayer->setVolume(option->getVolume());
    soundPlayer->setMuted(option->isMute());
    soundPlayer->setMedia(QMediaContent(QUrl::fromLocalFile(currentDir+sound)));

    soundPlayer->play();
}

void GameSoundPlayer::setMuted(bool muted)
{
    backgroundPlayer->setMuted(muted);
    foreach (QMediaPlayer *src, *playerList) {
        if(src->state() == QMediaPlayer::PlayingState)
            src->setMuted(muted);
    }

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
    qDeleteAll(*playerList);
}

