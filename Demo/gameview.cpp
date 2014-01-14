#include "gameview.h"
#include <QtGui>
#include <QtWidgets>
#include "abilitybutton.h"
#include "volumebutton.h"
#include "playpausebutton.h"
#include "closebutton.h"

GameView::GameView(QWidget *parent) :
    QGraphicsView(parent)
{

    loadHudImages();

    scoreInfo = new QLabel(tr("Score :"),this);
    scoreInfo->setGeometry(10,10,100,50);

    score = new QLabel(this);
    score->setGeometry(110,10,100,50);
    connect(this, SIGNAL(setScore(QString)),score,SLOT(setText(QString)));

    unitsCount = new QLabel(this);
    unitsCount->setGeometry(10,60,100,50);
    connect(this, SIGNAL(setUnitCount(QString)),unitsCount,SLOT(setText(QString)));

    unitInfo = new QLabel(tr("Unités restantes : "),this);
    unitInfo->setGeometry(10,60,100,50);
    //QGridLayout *grid = new QGridLayout(this);
    //QRect geo(240,410,480,130);
    //grid->setGeometry(geo);



    abi1 = new AbilityButton(1,acidImg,this);
    abi1->setGeometry(290,467,68,68);

    abi2 = new AbilityButton(2,spikeImg,this);
    abi2->setGeometry(368,467,68,68);

    abi3 = new AbilityButton(1,deviationImg,this);
    abi3->setGeometry(446,467,68,68);

    abi4 = new AbilityButton(1,iceImg,this);
    abi4->setGeometry(524,467,68,68);

    abi5 = new AbilityButton(1,bridgeImg,this);
    abi5->setGeometry(602,467,68,68);

    playButton = new PlayPauseButton(this);
    playButton->setGeometry(825,5,40,40);

    volume = new VolumeButton(this);
    volume->setGeometry(870,5,40,40);

    closeButton = new CloseButton(this);
    closeButton->setGeometry(915,5,40,40);

    connect(closeButton, SIGNAL(clicked()),this,SIGNAL(closeRender()));
    connect(abi1,SIGNAL(pressAbility(int)),this,SIGNAL(sendAbility(int)));
    connect(abi2,SIGNAL(pressAbility(int)),this,SIGNAL(sendAbility(int)));
    connect(abi3,SIGNAL(pressAbility(int)),this,SIGNAL(sendAbility(int)));
    connect(abi4,SIGNAL(pressAbility(int)),this,SIGNAL(sendAbility(int)));
    connect(abi5,SIGNAL(pressAbility(int)),this,SIGNAL(sendAbility(int)));
    //grid->addWidget(abi1,0,0);
    setMode(0);
}

void GameView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);

    QPainter painter(viewport());

    //painter.drawText(300,300,"yolo");
}

void GameView::update()
{
    QGraphicsView::update();
}

//Mode de la vue, permet d'afficher/masquer les bouttons du hud
void GameView::setMode(int mode)
{
    switch(mode)
    {
    case 0:
        abi1->hide();
        abi2->hide();
        abi3->hide();
        abi4->hide();
        abi5->hide();
        volume->hide();
        playButton->hide();
        closeButton->hide();
        score->hide();
        scoreInfo->hide();
        unitInfo->hide();
        unitsCount->hide();
        break;
    case 1:
        abi1->show();
        abi2->show();
        abi3->show();
        abi4->show();
        abi5->show();
        volume->show();
        playButton->show();
        closeButton->show();
        score->show();
        scoreInfo->show();
        unitInfo->show();
        unitsCount->show();
        break;
    }
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
