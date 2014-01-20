#ifndef MENURADIOBUTTON_H
#define MENURADIOBUTTON_H

#include <QGraphicsItem>
#include <QObject>

class MenuRadioButton : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    MenuRadioButton(QRectF rect, bool _checked);
    virtual ~MenuRadioButton();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    bool getChecked() const;
    void setChecked(bool value);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QRectF rect;
    bool checked;
    QPixmap *imgOn;
    QPixmap *imgOff;

signals:
    void checkStateChanged(MenuRadioButton *mrbtn);

};

#endif // MENURADIOBUTTON_H
