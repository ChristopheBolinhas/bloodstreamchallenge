#ifndef OPTIONBUTTON_H
#define OPTIONBUTTON_H

#include <QPushButton>
class VolumeButton : public QPushButton
{
    Q_OBJECT
public:
    explicit VolumeButton(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
signals:
    void setSound(bool sound);
public slots:

private:
    bool sound = true;
    QPixmap *muteImg;
    QPixmap *unmuteImg;

};

#endif // OPTIONBUTTON_H
