#ifndef PLAYPAUSEBUTTON_H
#define PLAYPAUSEBUTTON_H

#include <QPushButton>

class PlayPauseButton : public QPushButton
{
    Q_OBJECT
public:
    explicit PlayPauseButton(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void setMode(bool _play);
signals:
    void setPlayPause(bool play);
public slots:

private:
    bool play;
    QPixmap *playImg;
    QPixmap *pauseImg;
};

#endif // PLAYPAUSEBUTTON_H
