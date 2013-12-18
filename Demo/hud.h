#ifndef HUD_H
#define HUD_H


#include <QtWidgets>

class hud : public QWidget
{
    Q_OBJECT
public:
    explicit hud(QGraphicsView *view,QWidget *parent = 0);

signals:


private:
    QGraphicsTextItem *timeText;


public slots:

};

#endif // HUD_H
