#include "endgamescreen.h"
#include <QtWidgets>
#include "endgamebutton.h"


EndGameScreen::EndGameScreen(QWidget *parent) :
    QWidget(parent)
{

    setFixedSize(640,360);
    scoreDisplay = new QLabel(tr("Score :"), this);
    scoreDisplay->setFont(QFont("LetterOMatic!", 20));
    scoreDisplay->move(10,100);
    scoreValue = new QLabel("0", this);
    scoreValue->setFont(QFont("LetterOMatic!", 20));
    scoreValue->move(scoreDisplay->width()+60,100);
    resultLabel = new QLabel("Victoire !", this);
    resultLabel->setFont(QFont("LetterOMatic!", 30));
   // resultLabel->setGeometry(640/2-resultLabel->width()/2,10,resultLabel->width(),resultLabel->height());
    resultLabel->move(640/2-resultLabel->width()/2-20,10);




    btnHome = new EndGameButton(tr("Retour aux menus"), this);
    btnHome->setFont(QFont("LetterOMatic!", 12));
    btnHome->setGeometry(340,200,250,125);
    btnRetry = new EndGameButton(tr("Reessayer"), this);
    btnRetry->setFont(QFont("LetterOMatic!", 12));
    btnRetry->setGeometry(50,200,250,125);

    connect(btnHome,SIGNAL(clicked()),this,SIGNAL(homeSignal()));
    connect(btnRetry,SIGNAL(clicked()),this,SIGNAL(retrySignal()));

}

void EndGameScreen::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap bg(":/menu/ressources/img/menu/endgamebackground.png");
    painter.drawPixmap(0,0,640,360,bg);

}

void EndGameScreen::setScreen(QString score, int victory)
{
    if(victory)
    {
        resultLabel->setText(tr("Victoire !"));
        scoreValue->setText(score);
        scoreDisplay->show();
        scoreValue->show();
    }
    else
    {
        resultLabel->setText(tr("Defaite !"));
        scoreDisplay->hide();
        scoreValue->hide();
    }
}
