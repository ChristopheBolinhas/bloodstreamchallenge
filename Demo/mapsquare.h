#ifndef MAPSQUARE_H
#define MAPSQUARE_H

class MapSquare
{
public:
    MapSquare(MapSquare *next = 0, int x = 0, int y = 0);



    MapSquare* getNext();
    int getX();
    int getY();
private:
    MapSquare *next;
    int x;
    int y;

};

#endif // MAPSQUARE_H
