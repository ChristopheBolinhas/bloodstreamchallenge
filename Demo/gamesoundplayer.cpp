#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDebug>

#include "gamesoundplayer.h"
#include "option.h"


const QString GameSoundPlayer::BOOST_USE = "/ressources/sounds/boost.wav";
const QString GameSoundPlayer::CAILLOT_USE = "/ressources/sounds/caillot.wav"; //TODO
const QString GameSoundPlayer::CHUTE_USE = "/ressources/sounds/chute.wav";//TODO
const QString GameSoundPlayer::DEVIATION_USE = "/ressources/sounds/deviation.wav"; //TODO
const QString GameSoundPlayer::BACTERIE_USE = "/ressources/sounds/bacterie.wav";
const QString GameSoundPlayer::DEATH_UNIT = "/ressources/sounds/death.wav"; //TODO

const QString GameSoundPlayer::SOUND_IN_GAME = "/ressources/sounds/in_game.mp3";
const QString GameSoundPlayer::SOUND_MENU = "/ressources/sounds/menu.mp3"; //TODO

GameSoundPlayer::GameSoundPlayer(Option *option, QWidget *parent) : QWidget(parent)
{
    this->option = option;
    currentDir = QApplication::applicationDirPath();
    volume = option->getVolume();
    backgroundPlayer = new QMediaPlayer();
    playerList = new QList<QMediaPlayer*>();

    backgroundPlaylist = new QMediaPlaylist();

    backgroundPlaylist->addMedia(QMediaContent(QUrl::fromLocalFile(currentDir+SOUND_MENU)));
    backgroundPlaylist->addMedia(QMediaContent(QUrl::fromLocalFile(currentDir+SOUND_IN_GAME)));
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

    soundPlayer->setVolume(volume);
    soundPlayer->setMuted(muted);
    soundPlayer->setMedia(QMediaContent(QUrl::fromLocalFile(currentDir+sound)));

    soundPlayer->play();
}

void GameSoundPlayer::setMuted(bool muted)
{
    backgroundPlayer->setMuted(muted);
    this->muted = muted;
    foreach (QMediaPlayer *src, *playerList) {
        if(src->state() == QMediaPlayer::PlayingState)
            src->setMuted(muted);
    }

}

void GameSoundPlayer::setSound(int volume, bool muted)
{
    this->muted = muted;
    this->volume = volume;
    if(muted)
    {

        backgroundPlayer->setMuted(muted);

    }
    else
    {
        backgroundPlayer->setVolume(volume);
        backgroundPlayer->setMuted(muted);
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
    //qDeleteAll(*playerList);
}

