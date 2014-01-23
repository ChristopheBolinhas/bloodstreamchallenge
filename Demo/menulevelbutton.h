#ifndef MENULEVELBUTTON_H
#define MENULEVELBUTTON_H
#include <QGraphicsItem>
#include <QObject>
class QPainter;
class QGraphicsItem;
class QGraphicsPixmapItem;
class QRectF;
class Level;
class GameSoundPlayer;

class MenuLevelButton : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    MenuLevelButton(QPointF &position, Level *level, bool locked);
    virtual ~MenuLevelButton();
    QPixmap *getImage() const;
    void setImage(QPixmap *value);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


private:
    QPixmap *image;
    QPixmap *imageLocked;
    QPointF position;
    QRectF *rectImage;
    static const int MARGE_TOP_BOTTOM = 15;
    QString labelScore;
    QString labelLevelOrder;
    bool locked;
    Level* level;

    void createRectImageMargin(int marge);
    bool isMouseReleaseInRectImage(QPointF downPos);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    void startLevel(Level *level);
};

#endif // MENULEVELBUTTON_H
