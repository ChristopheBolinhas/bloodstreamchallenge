#ifndef BACTERIE_H
#define BACTERIE_H

#include "obstacle.h"

class Bacterie : public Obstacle
{
public:
    Bacterie(int _x, int _y, int _orientation, QList<QPixmap *> *_images, Level *level);

};

#endif // BACTERIE_H
