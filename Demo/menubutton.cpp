#include "menubutton.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

#include <QDebug>

MenuButton::MenuButton(QPointF position, QString label, QObject *parent) :
    QObject(parent)
{
    this->image = new QPixmap(":/menu/ressources/img/menu/bouton.png");
    this->rectImage = new QRectF(position.x(),position.y(), this->image->width(),this->image->height());
    this->label = label;

    //Permet la gestion du clic relaché
    setFlags(QGraphicsItem::ItemIsSelectable);
}

MenuButton::~MenuButton()
{

}

QRectF MenuButton::boundingRect() const
{
    return *rectImage;
}

void MenuButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(rectImage->toRect(),*image);
    painter->setFont(QFont("LetterOMatic!", 20));
    painter->drawText(*rectImage,Qt::AlignCenter,this->getLabel());
}
QString MenuButton::getLabel() const
{
    return label;
}

void MenuButton::setLabel(const QString &value)
{
    label = value;
}

void MenuButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "clic pressé " << this->getLabel();
    update();
    QGraphicsItem::mousePressEvent(event);
}

void MenuButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF downPos = event->pos();
    if(event->button()==Qt::LeftButton && isMouseReleaseInRectImage(downPos))
    {
        //qDebug() << "clic relaché " << this->getLabel();
        update();
        QGraphicsItem::mouseReleaseEvent(event);
        emit clicked();
    }
}

bool MenuButton::isMouseReleaseInRectImage(QPointF downPos)
{
    return downPos.x() >= rectImage->x() && downPos.x() <= rectImage->x()+rectImage->width() &&  downPos.y() >= rectImage->y() && downPos.y() <= rectImage->y()+rectImage->height();
}
