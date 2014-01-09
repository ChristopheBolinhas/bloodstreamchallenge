#include "menuradiobutton.h"
#include <QPainter>

#include <QDebug>

MenuRadioButton::MenuRadioButton(QRectF rect, bool _checked)
{
    this->rect = rect;
    this->checked = _checked;
}

MenuRadioButton::~MenuRadioButton()
{

}

QRectF MenuRadioButton::boundingRect() const
{
    return rect;
}

void MenuRadioButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    painter->drawEllipse(rect.center(),rect.width()/2,rect.height()/2);

    if(checked)
        drawChecked(painter, rect);
    else
        drawUnchecked(painter);

}

void MenuRadioButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
    qDebug() << "signal emit";
    emit checkStateChanged(this);
}

void MenuRadioButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
bool MenuRadioButton::getChecked() const
{
    return checked;
}

void MenuRadioButton::setChecked(bool value)
{
    checked = value;
}


void MenuRadioButton::drawChecked(QPainter *painter, QRectF &rect)
{
    painter->setBrush(QBrush(Qt::black));
    painter->drawEllipse(rect.center(),rect.width()/6,rect.height()/6);

}

void MenuRadioButton::drawUnchecked(QPainter *painter)
{

}
