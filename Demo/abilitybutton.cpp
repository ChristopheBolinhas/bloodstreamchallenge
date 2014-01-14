#include "abilitybutton.h"
#include <QtWidgets>

AbilityButton::AbilityButton(int _abilityId, QList<QPixmap*> *images, QWidget *parent) :
    QPushButton(parent)
{
    //setGeometry(0,0,68,68);
    abilityId = _abilityId;
    releasedImg = images->at(0);
    pressedImg = images->at(1);
    buttonAnim = new QTimer(this);
    buttonAnim->setInterval(200);
    connect(buttonAnim,SIGNAL(timeout()),this,SLOT(releasedAnim()));
}

void AbilityButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(etat)
    {
        painter.drawPixmap(0,0,68,68,*pressedImg);
    }
    else
    {
        painter.drawPixmap(0,0,68,68,*releasedImg);
    }
}

void AbilityButton::mousePressEvent(QMouseEvent *e)
{
    etat = true;
    buttonAnim->start();
    emit pressAbility(abilityId);

    qDebug() << "PRESSED";
}

void AbilityButton::releasedAnim()
{
    etat = false;
    update();
    qDebug() << "Released";
    buttonAnim->stop();
}
