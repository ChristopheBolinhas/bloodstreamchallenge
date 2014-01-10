#include "boost.h"
#include "level.h"

Boost::Boost(int _x, int _y, int _orientation, QList<QPixmap*> *_images, Level *level) : Obstacle(_x,_y,_orientation)
{

    images = _images;
    timerAnim = new QTimer(this);
    timerAnim->setInterval(200);
    connect(timerAnim, SIGNAL(timeout()),this,SLOT(disableAnim()));
    setPos(Obstacle::x*level->getTileWidth(),Obstacle::y*level->getTileHeight());
    setZValue(2);
}

Boost::~Boost()
{

}


void Boost::paint( QPainter *painter, const QStyleOptionGraphicsItem*,QWidget *)
{
    QPixmap *currentPixmap = images->at(etat);

    //painter->rotate(45*Obstacle::rotation);
    //currentPixmap->transformed(t);
    painter->drawPixmap(0,0,width,height, *currentPixmap);


}

void Boost::disable()
{
    timerAnim->start();
    enabled = false;

}

void Boost::disableAnim()
{
    if(enabled)
    {
        etat = 0;
    }
    else
    {
        if(etat < 3) etat++;
        update(this->boundingRect());
        if(etat >= 3) timerAnim->stop();

    }


}
