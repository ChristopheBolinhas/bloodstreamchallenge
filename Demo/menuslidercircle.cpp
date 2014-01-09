#include "menuslidercircle.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QRectF>

#include <QDebug>

MenuSliderCircle::MenuSliderCircle(QPoint position, int size, int minimum, int maximum, int lenght = 1)
{
    setFlags(ItemIsMovable|ItemSendsGeometryChanges);
    this->position = position;
    this->size = size;
    this->minimum = minimum;
    this->maximum = maximum;
    this->lenght = lenght;
}

MenuSliderCircle::~MenuSliderCircle()
{

}

QRectF MenuSliderCircle::boundingRect() const
{
    return QRectF(position,QSize(size,size));
}

void MenuSliderCircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    painter->drawEllipse(rect.center(),size/2,size/2);
    //TODO: a remplacer par une image, le plus vite possible bug d'affichage uniquement
    painter->drawLine(position.x()+(size/2)-this->pos().x(),position.y()+size/2,position.x()+(size/2)+maximum*lenght/*+size/2*/,position.y()+size/2);
    painter->drawRect(position.x()-this->pos().x(),position.y(),maximum*lenght+size,size);
}

int MenuSliderCircle::getValue() const
{
    return this->pos().x()/lenght;
}

void MenuSliderCircle::setValue(int value)
{
    //on reset la position du slider à son minimum avant de set la value
    this->moveBy(-maximum*lenght,0);
    this->moveBy(value*lenght,0);
}

QVariant MenuSliderCircle::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange) {
        QPointF newPos = value.toPointF();
        int xValue = newPos.x();
        newPos.setX(qMax(qMin(maximum*lenght,xValue),minimum));
        newPos.setY(0);
        return QGraphicsItem::itemChange(change, newPos);
    }
    return QGraphicsItem::itemChange(change, value);
}

void MenuSliderCircle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void MenuSliderCircle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
int MenuSliderCircle::getLenght() const
{
    return lenght;
}

void MenuSliderCircle::setLenght(int value)
{
    lenght = value;
}

int MenuSliderCircle::getSize() const
{
    return size;
}

void MenuSliderCircle::setSize(int value)
{
    size = value;
}

QPoint MenuSliderCircle::getPosition() const
{
    return position;
}

void MenuSliderCircle::setPosition(const QPoint &value)
{
    position = value;
}

int MenuSliderCircle::getMaximum() const
{
    return maximum;
}

void MenuSliderCircle::setMaximum(int value)
{
    maximum = value;
}

int MenuSliderCircle::getMinimum() const
{
    return minimum;
}

void MenuSliderCircle::setMinimum(int value)
{
    minimum = value;
}
