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
        drawChecked(painter, rect);
    else
        drawUnchecked(painter, rect);

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


void MenuCheckBox::drawChecked(QPainter *painter, const QRectF &rect)
{
    painter->drawRect(rect);
    painter->drawLine(rect.topLeft(), rect.bottomRight());
    painter->drawLine(rect.topRight(), rect.bottomLeft());
}

void MenuCheckBox::drawUnchecked(QPainter *painter, const QRectF &rect)
{
    painter->drawRect(rect);
}
