#ifndef ENUMOBSTACLE_H
#define ENUMOBSTACLE_H

#include <QtGui>

class EnumObstacle
{
    Q_ENUMS(TypeObstacle);
public:
    EnumObstacle();
    enum TypeObstacle{deviation,caillot,monstre,chute,boostvitesse};
};

#endif // ENUMOBSTACLE_H
