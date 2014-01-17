#ifndef ENDGAMESCREEN_H
#define ENDGAMESCREEN_H

#include <QWidget>

class QLabel;
class EndGameButton;
class EndGameScreen : public QWidget
{
    Q_OBJECT
public:
    explicit EndGameScreen(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void setScreen(QString score, int victory);
signals:
    void retrySignal();
    void homeSignal();
public slots:

private:
    QLabel *resultLabel;
    QLabel *scoreDisplay;
    QLabel *scoreValue;
    EndGameButton *btnRetry;
    EndGameButton *btnHome;
};

#endif // ENDGAMESCREEN_H
