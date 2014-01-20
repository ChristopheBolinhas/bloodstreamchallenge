#include "endgamebutton.h"
#include <QtWidgets>

EndGameButton::EndGameButton(QString label, QWidget *parent) :
    QPushButton(parent)
{
    setText(label);
    setGeometry(0,0,250,125);
    img = new QPixmap(":/menu/ressources/img/menu/endgamebutton.png");
}

void EndGameButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(img->rect(),*img);
    painter.setFont(QFont("LetterOMatic!", 14));
    painter.drawText(this->rect(),Qt::AlignCenter,this->text());
}
