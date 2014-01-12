#include "menuslidercircle.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QRectF>

#include <QDebug>

MenuSliderCircle::MenuSliderCircle(QPoint position, int size, int minimum, int maximum, int lenght, QGraphicsScene *scene)
{
    setFlags(ItemIsMovable|ItemSendsGeometryChanges);
    this->position = position;
    this->size = size;
    this->minimum = minimum;
    this->maximum = maximum;
    this->lenght = lenght;
    this->scene = scene;
}

MenuSliderCircle::~MenuSliderCircle()
{

}

QRectF MenuSliderCircle::boundingRect() const
{
    return QRectF(position,QSize(100*lenght,size));
}

void MenuSliderCircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(position.x()-pos().x()+size/2,position.y()-pos().y(),QPixmap(":/menu/ressources/img/menu/Slider_bar.png"));
    painter->drawPixmap(position.x(), position.y()-size/4,QPixmap(":/menu/ressources/img/menu/Slider_dot.png"));
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
        this->scene->update();
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
