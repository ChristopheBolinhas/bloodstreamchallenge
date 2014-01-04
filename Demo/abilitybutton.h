#ifndef ABILITYBUTTON_H
#define ABILITYBUTTON_H

#include <QPushButton>

class AbilityButton : public QPushButton
{
    Q_OBJECT
public:
    explicit AbilityButton(int _abilityId, QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
private:
    int abilityId = 0;

signals:
    void pressAbility(int id);
public slots:

};

#endif // ABILITYBUTTON_H
