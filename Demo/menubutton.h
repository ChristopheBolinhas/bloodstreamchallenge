#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QObject>
#include <QGraphicsItem>

class MenuButton : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit MenuButton(QRectF *rectImage, QString label, QObject *parent = 0);
    virtual ~MenuButton();
    QPixmap *getImage() const;
    void setImage(QPixmap *value);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QString getLabel() const;
    void setLabel(const QString &value);

private:
    QPixmap *image;
    QRectF *rectImage;
    QString label;

    bool isMouseReleaseInRectImage(QPointF downPos);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    void clicked();

};

#endif // MENUBUTTON_H
