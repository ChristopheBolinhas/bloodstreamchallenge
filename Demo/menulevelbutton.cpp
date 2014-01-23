#include "menulevelbutton.h"
#include "level.h"
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QRect>
#include <QPainter>

MenuLevelButton::MenuLevelButton(QPointF &position, Level *lvl, bool locked)
{
    this->locked = locked;
    this->level = lvl;
    this->image = new QPixmap(":/menu/ressources/img/menu/level.png");
	this->imageLocked = new QPixmap(":/menu/ressources/img/menu/level_disabled.png");
    this->position = position;
    this->rectImage = new QRectF(position,QSize(this->image->width(),this->image->height()));

    this->labelLevelOrder = QString::number(level->getOrder());
    this->labelScore = QString::number(level->getScore());

    //Permet la gestion du clic relaché
    setFlags(QGraphicsItem::ItemIsSelectable);
}

MenuLevelButton::~MenuLevelButton()
{

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
    return this->rectImage->toRect();
}

void MenuLevelButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //Level image
    if(locked && level->getOrder() != 1)
        painter->drawPixmap(position,*imageLocked);
    else
        painter->drawPixmap(position,*image);

    // Level order
    painter->setFont(QFont("LetterOMatic!",24));
    int heightWithoutBlackRegion = this->rectImage->height()-27.0;
    QRectF rectOrange(position, QSizeF(this->image->rect().width(),heightWithoutBlackRegion));
    painter->drawText(rectOrange,Qt::AlignCenter,labelLevelOrder);

    // Level score
    int heightWithoutOrangeRegion = this->rectImage->height() - heightWithoutBlackRegion;
    painter->setPen(QColor::fromRgb(255,255,255));
    painter->setFont(QFont("LetterOMatic!",10));
    QRectF rectBlack(position.x(),position.y()+heightWithoutBlackRegion, this->image->rect().width(),heightWithoutOrangeRegion);
    painter->drawText(rectBlack,Qt::AlignCenter,labelScore);
}

void MenuLevelButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void MenuLevelButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF downPos = event->pos();
    if(isMouseReleaseInRectImage(downPos) && (!locked || level->getOrder()==1))
    {
        update();
        QGraphicsItem::mouseReleaseEvent(event);
        emit startLevel(level);
    }
}

bool MenuLevelButton::isMouseReleaseInRectImage(QPointF downPos)
{
    return downPos.x() >= rectImage->x() && downPos.x() <= rectImage->x()+rectImage->width() &&  downPos.y() >= rectImage->y() && downPos.y() <= rectImage->y()+rectImage->height();
}
