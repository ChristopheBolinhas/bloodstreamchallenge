#include "menucheckbox.h"
#include <QPainter>

#include <QDebug>

MenuCheckBox::MenuCheckBox(QRectF rect, bool _checked)
{
    this->rect = rect;
    this->checked = _checked;
}

MenuCheckBox::~MenuCheckBox()
{

}

QRectF MenuCheckBox::boundingRect() const
{
    return rect;
}

void MenuCheckBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    if(checked)
        painter->drawPixmap(rect.toRect(), QPixmap(":/menu/ressources/img/menu/checked.png"));
    else
        painter->drawPixmap(rect.toRect(), QPixmap(":/menu/ressources/img/menu/unchecked.png"));

}

void MenuCheckBox::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    checked = !checked;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void MenuCheckBox::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
bool MenuCheckBox::getChecked() const
{
    return checked;
}

void MenuCheckBox::setChecked(bool value)
{
    checked = value;
    update();
}
