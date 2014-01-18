#include "chute.h"
#include "level.h"

Chute::Chute(int _x, int _y, int _orientation, QList<QPixmap*> *_images, Level *level) : Obstacle(_x,_y,_orientation, _images, level)
{
}




