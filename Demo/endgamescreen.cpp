#include "endgamescreen.h"
#include <QtWidgets>
#include "endgamebutton.h"


EndGameScreen::EndGameScreen(QWidget *parent) :
    QWidget(parent)
{

    setFixedSize(640,360);
    scoreValue = new QLabel("XXXX", this);
    scoreValue->setFont(QFont("LetterOMatic!", 20));
    scoreValue->move(640/2-scoreValue->width(),100);
    resultLabel = new QLabel(tr("Victoire !"), this);
    resultLabel->setFont(QFont("LetterOMatic!", 30));
    resultLabel->move(640/2-resultLabel->width(),10);




    btnHome = new EndGameButton(tr("Retour aux menus"), this);
    btnHome->setFont(QFont("LetterOMatic!", 12));
    btnHome->setGeometry(340,200,250,125);
    btnRetry = new EndGameButton(tr("Reessayer"), this);
    btnRetry->setFont(QFont("LetterOMatic!", 12));
    btnRetry->setGeometry(50,200,250,125);

    connect(btnHome,SIGNAL(clicked()),this,SIGNAL(homeSignal()));
    connect(btnRetry,SIGNAL(clicked()),this,SIGNAL(retrySignal()));
    bg = new QPixmap(":/menu/ressources/img/menu/endgamebackground.png");

}

void EndGameScreen::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,640,360,*bg);

}

void EndGameScreen::setScreen(QString score, int victory)
{
    if(victory)
    {
        resultLabel->setText(tr("Victoire !"));
        scoreValue->setText(tr("Score : ") + score);
        scoreValue->show();
    }
    else
    {
        resultLabel->setText(tr("Defaite !"));
        scoreValue->hide();
    }
}
