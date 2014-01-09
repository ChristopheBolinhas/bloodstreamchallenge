#ifndef MENUCHECKBOX_H
#define MENUCHECKBOX_H

#include <QGraphicsItem>

class MenuCheckBox : public QGraphicsItem
{
public:
    MenuCheckBox(QRectF rect, bool _checked);
    virtual ~MenuCheckBox();

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
    void drawChecked(QPainter *painter, const QRectF &rect);
    void drawUnchecked(QPainter *painter, const QRectF &rect);

};

#endif // MENUCHECKBOX_H
