#include "abilitybutton.h"
#include <QtWidgets>

AbilityButton::AbilityButton(int _abilityId, QWidget *parent) :
    QPushButton(parent)
{
    setGeometry(0,0,180,130);
    abilityId = _abilityId;
}

void AbilityButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);//Globalement osef des rect, l'image suffit
    QPixmap img("://ressources/img/1.png");
    painter.drawPixmap(0,0,180,130,img);
    painter.setBrush(Qt::lightGray);
    painter.drawRect(this->geometry());
    painter.setPen(Qt::black);
    QString id(abilityId);
    painter.drawText(0,0,40,40,Qt::AlignCenter,id);

}

void AbilityButton::mousePressEvent(QMouseEvent *e)
{
    emit pressAbility(abilityId);
}
