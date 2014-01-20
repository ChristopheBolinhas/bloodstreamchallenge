#ifndef CLOSEBUTTON_H
#define CLOSEBUTTON_H

#include <QPushButton>

class CloseButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CloseButton(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
signals:

public slots:

private:
    QPixmap *closeImg;

};

#endif // CLOSEBUTTON_H
