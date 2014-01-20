#ifndef ABILITYBUTTON_H
#define ABILITYBUTTON_H

#include <QPushButton>

class AbilityButton : public QPushButton
{
    Q_OBJECT
public:
    explicit AbilityButton(int _abilityId, QList<QPixmap *> *images, QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
private:
    int abilityId;
    QPixmap *releasedImg;
    QPixmap *pressedImg;
    bool etat;
    QTimer *buttonAnim;

signals:
    void pressAbility(int id);
public slots:

private slots:
    void releasedAnim();

};

#endif // ABILITYBUTTON_H
