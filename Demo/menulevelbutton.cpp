#include "menulevelbutton.h"
#include "level.h"
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QRect>
#include <QPainter>

MenuLevelButton::MenuLevelButton(QRectF *rectangle, Level *lvl)
{
    this->level = lvl;
    this->image = new QPixmap("://ressources/img/disc.png");
    this->rectImage = rectangle;
    createRectImageMargin(MARGE_TOP_BOTTOM);

    this->labelScore = QString::number(level->getScore());
    this->labelLevelName = level->getName();

    //Permet la gestion du clic relaché
    setFlags(QGraphicsItem::ItemIsSelectable);
}

MenuLevelButton::~MenuLevelButton()
{

}

void MenuLevelButton::createRectImageMargin(int marge)
{
    rectImageMargin = new QRectF(*rectImage);
    rectImageMargin->setHeight(rectImageMargin->height()+2*marge);
    rectImageMargin->translate(0,-marge);
}

QPixmap *MenuLevelButton::getImage() const
{
    return image;
}

void MenuLevelButton::setImage(QPixmap *value)
{
    image = value;
}

QRectF MenuLevelButton::boundingRect() const
{
    return *rectImageMargin;
}

void MenuLevelButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(rectImage->toRect(),*image);
    painter->drawRect(rectImageMargin->toRect());

    painter->drawText(*rectImageMargin,Qt::AlignHCenter,labelLevelName);
    painter->drawText(*rectImageMargin,Qt::AlignHCenter|Qt::AlignBottom,labelScore);
}

void MenuLevelButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "clic pressé";
    update();
    QGraphicsItem::mousePressEvent(event);
}

void MenuLevelButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF downPos = event->pos();
    if(isMouseReleaseInRectImage(downPos))
    {
        //qDebug() << "clic relaché";
        update();
        QGraphicsItem::mouseReleaseEvent(event);
        //qDebug() << "before emit " << this->level->getName();
        emit startLevel(level);
    }
}

bool MenuLevelButton::isMouseReleaseInRectImage(QPointF downPos)
{
    return downPos.x() >= rectImageMargin->x() && downPos.x() <= rectImageMargin->x()+rectImageMargin->width() &&  downPos.y() >= rectImageMargin->y() && downPos.y() <= rectImageMargin->y()+rectImageMargin->height();
}
