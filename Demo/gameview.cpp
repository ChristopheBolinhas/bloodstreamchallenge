#include "gameview.h"
#include <QtGui>
#include <QtWidgets>
#include "abilitybutton.h"
#include "volumebutton.h"
#include "playpausebutton.h"
#include "closebutton.h"
#include "menubutton.h"

GameView::GameView(QWidget *parent) :
    QGraphicsView(parent)
{

    loadHudImages();
    loadHudElements();

    //Connexion des signaux
    connect(this, SIGNAL(setScore(QString)),score,SLOT(setText(QString)));
    connect(this, SIGNAL(setUnitCount(QString)),unitsCount,SLOT(setText(QString)));

    connect(playButton,SIGNAL(setPlayPause(bool)),SIGNAL(pauseGame(bool)));
    connect(volumeButton,SIGNAL(setSound(bool)),this,SIGNAL(setSound(bool)));
    connect(closeButton, SIGNAL(clicked()),this,SIGNAL(closeRender()));
    connect(abi1,SIGNAL(pressAbility(int)),this,SIGNAL(sendAbility(int)));
    connect(abi2,SIGNAL(pressAbility(int)),this,SIGNAL(sendAbility(int)));
    connect(abi3,SIGNAL(pressAbility(int)),this,SIGNAL(sendAbility(int)));
    connect(abi4,SIGNAL(pressAbility(int)),this,SIGNAL(sendAbility(int)));
    connect(abi5,SIGNAL(pressAbility(int)),this,SIGNAL(sendAbility(int)));
    endGame = true;
    setMode(0,true);



}

void GameView::setStartInfo(int step)
{
    if(step > 0)
    {
        startLabel->setText(QString::number(step));
        startLabel->show();
    }
    else
    {
        startLabel->hide();
    }
}

void GameView::loadHudElements()
{


    //Element coin supérieur gauche
        //Label d'affichages
    scoreInfo = new QLabel(tr("Score :"),this);
    scoreInfo->setGeometry(10,10,100,40);
    scoreInfo->setFont(QFont("LetterOMatic!", 10));
    unitInfo = new QLabel(tr("Unités : "),this);
    unitInfo->setFont(QFont("LetterOMatic!", 10));
    unitInfo->setGeometry(10,50,200,50);

        //Labels d'information
    score = new QLabel(this);
    score->setFont(QFont("LetterOMatic!", 10));
    score->setGeometry(110,10,100,40);
    unitsCount = new QLabel(this);
    unitsCount->setGeometry(110,50,100,40);
    unitsCount->setFont(QFont("LetterOMatic!", 10));


    //Element d'abilités
    abi1 = new AbilityButton(1,acidImg,this);
    abi1->setGeometry(290,467,68,68);

    abi2 = new AbilityButton(2,spikeImg,this);
    abi2->setGeometry(368,467,68,68);

    abi3 = new AbilityButton(3,deviationImg,this);
    abi3->setGeometry(446,467,68,68);

    abi4 = new AbilityButton(4,iceImg,this);
    abi4->setGeometry(524,467,68,68);

    abi5 = new AbilityButton(5,bridgeImg,this);
    abi5->setGeometry(602,467,68,68);


    //Boutons de contrôle coin supérieur droit
    playButton = new PlayPauseButton(this);
    playButton->setGeometry(825,5,40,40);
    volumeButton = new VolumeButton(this);
    volumeButton->setGeometry(870,5,40,40);
    closeButton = new CloseButton(this);
    closeButton->setGeometry(915,5,40,40);

    startLabel = new QLabel(this);
    startLabel->move(960/2,540/2);
    startLabel->hide();
    startLabel->setFont(QFont("LetterOMatic!", 30));

}



void GameView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
}

void GameView::update()
{
    QGraphicsView::update();
}

void GameView::setEndGame(bool victory)
{


}

//Mode de la vue, permet d'afficher/masquer les bouttons du hud
void GameView::setMode(int mode, bool sound)
{
    switch(mode)
    {
    case 0:
        abi1->hide();
        abi2->hide();
        abi3->hide();
        abi4->hide();
        abi5->hide();
        volumeButton->hide();
        playButton->hide();
        closeButton->hide();
        score->hide();
        scoreInfo->hide();
        unitInfo->hide();
        unitsCount->hide();
        startLabel->hide();

        break;
    case 1:
        abi1->show();
        abi2->show();
        abi3->show();
        abi4->show();
        abi5->show();
        volumeButton->show();
        volumeButton->setMode(sound);
        playButton->show();
        playButton->setMode(true);
        closeButton->show();
        score->show();
        scoreInfo->show();
        unitInfo->show();
        unitsCount->show();
        startLabel->hide();
        break;
    }
}

void GameView::wheelEvent(QWheelEvent *event)
{

}

void GameView::loadHudImages()
{
    acidImg = new QList<QPixmap*>();
    bridgeImg = new QList<QPixmap*>();
    deviationImg = new QList<QPixmap*>();
    iceImg = new QList<QPixmap*>();
    spikeImg = new QList<QPixmap*>();

    acidImg->append(new QPixmap(":/hud/ressources/img/HUD_Icon/acid_1.png"));
    acidImg->append(new QPixmap(":/hud/ressources/img/HUD_Icon/acid_2.png"));

    bridgeImg->append(new QPixmap(":/hud/ressources/img/HUD_Icon/bridge_1.png"));
    bridgeImg->append(new QPixmap(":/hud/ressources/img/HUD_Icon/bridge_2.png"));

    deviationImg->append(new QPixmap(":/hud/ressources/img/HUD_Icon/deviation_1.png"));
    deviationImg->append(new QPixmap(":/hud/ressources/img/HUD_Icon/deviation_2.png"));

    iceImg->append(new QPixmap(":/hud/ressources/img/HUD_Icon/ice_1.png"));
    iceImg->append(new QPixmap(":/hud/ressources/img/HUD_Icon/ice_2.png"));

    spikeImg->append(new QPixmap(":/hud/ressources/img/HUD_Icon/spike_1.png"));
    spikeImg->append(new QPixmap(":/hud/ressources/img/HUD_Icon/spike_2.png"));



}
