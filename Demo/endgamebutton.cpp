#include "endgamebutton.h"
#include <QtWidgets>

EndGameButton::EndGameButton(QString label, QWidget *parent) :
    QPushButton(parent)
{
    setText(label);
    setGeometry(0,0,250,125);

}

void EndGameButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap *img = new QPixmap(":/menu/ressources/img/menu/endgamebutton.png");

    painter.drawPixmap(img->rect(),*img);
    painter.drawText(this->rect(),Qt::AlignCenter,this->text());
}
