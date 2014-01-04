#ifndef OBSTACLE_H
#define OBSTACLE_H


class Obstacle
{

public:
    Obstacle();
    bool isEnabled();
    virtual ~Obstacle();


protected:
    bool enabled;


private:

};

#endif // OBSTACLE_H
