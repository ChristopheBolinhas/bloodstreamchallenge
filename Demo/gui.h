#ifndef GUI_H
#define GUI_H

#include <QtWidgets>
#include "level.h"

class Level;
class QGraphicsScene;
class QGraphicsView;
class Gui : public QWidget
{
    Q_OBJECT
public:
    explicit Gui(QWidget *parent = 0);
private:
    QList<Level> *levels;
    void startLevel(Level *level);
    QGraphicsView *view;
signals:

public slots:

};

#endif // GUI_H
