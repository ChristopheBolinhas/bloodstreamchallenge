#ifndef MENULEVELBUTTON_H
#define MENULEVELBUTTON_H
#include <QGraphicsItem>
#include <QObject>
class QPainter;
class QGraphicsItem;
class QGraphicsPixmapItem;
class QRectF;
class Level;

class MenuLevelButton : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    MenuLevelButton(QRectF *rectImage, Level *level);
    virtual ~MenuLevelButton();
    QPixmap *getImage() const;
    void setImage(QPixmap *value);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


private:
    QPixmap *image;
    QRectF *rectImage;
    QRectF *rectImageMargin; // Rectangle avec une marge en haut et en bas pour afficher le nom et le score
    static const int MARGE_TOP_BOTTOM = 15;
    QString labelScore;
    QString labelLevelName;

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
