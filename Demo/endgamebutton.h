#ifndef ENDGAMEBUTTON_H
#define ENDGAMEBUTTON_H

#include <QPushButton>

class EndGameButton : public QPushButton
{
    Q_OBJECT
public:
    explicit EndGameButton(QString label, QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
signals:

public slots:

};

#endif // ENDGAMEBUTTON_H
