#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include "menulevelbutton.h"
#include "menubutton.h"
#include <QList>
#include <QObject>
#include <QPoint>
#include <QRect>
class QGraphicsView;
class QGraphicsScene;
class QPixmap;
class Level;
class QPropertyAnimation;
class MenuRadioButton;
class MenuSliderCircle;
class MenuCheckBox;
class Option;
class GameSoundPlayer;

class MenuContainer : public QObject
{
    Q_OBJECT
public:
    MenuContainer(QGraphicsView *m_view, Option *_option, QList<Level *> *listLevel);
    virtual ~MenuContainer();

    QGraphicsScene *getScene() const;

    void addGameLogo();
    void addLevelButtons(QList<Level*> listLevels);
    void addQuitOptionsButtons();
    void addMenuOptions();
    void setupView(QGraphicsView *m_view);
    void initializationAnimation();
    void setupScene();
    void initilizationConstants();
private:
    QGraphicsView *view;
    QGraphicsScene *scene;
    Option *option;
    QList<Level*> *listLevel;

    //Menu principal
    QPixmap *gameLogo;
    QGraphicsTextItem *labelChooseLevel;
    QList<MenuLevelButton> *listButtonLevel;
    MenuButton *btnOption;
    MenuButton *btnQuitter;

    //Menu option
    MenuButton *btnValider;
    MenuButton *btnAnnuler;
    MenuButton *btnReset;

    QList<MenuRadioButton*> listMenuRadioButton;
    MenuRadioButton *mrbtnLangueFrancais;
    MenuRadioButton *mrbtnLangueAnglais;

    MenuSliderCircle *mscVolume;
    MenuCheckBox *mcbxMute;

    QGraphicsTextItem *labelOptionLangue;
    QGraphicsTextItem *labelOptionLangueFrancais;
    QGraphicsTextItem *labelOptionLangueAnglais;
    QGraphicsTextItem *labelOptionVolume;
    QGraphicsTextItem *labelOptionMute;

    static const int CENTER_MENU_PRINCIPAL_X = 0;
    static const int CENTER_MENU_PRINCIPAL_Y = 270;
    static const int CENTER_MENU_OPTION_X = 1920;
    static const int CENTER_MENU_OPTION_Y = 270;
    static const int SCENE_SIZE_X = 1920;
    static const int SCENE_SIZE_Y = 560;

    static const int LEVEL_BY_LINE = 10;
    static const int MENU_LEVEL_BUTTON_COOR_X = 70;
    static const int MENU_LEVEL_BUTTON_COOR_Y = 250;
    static const int MENU_LEVEL_BUTTON_MARGE_X = 100;
    static const int MENU_LEVEL_BUTTON_MARGE_Y = 125;
    static const int MENU_LEVEL_BUTTON_WIDTH = 64;
    static const int MENU_LEVEL_BUTTON_HEIGHT = 64;

    static const int MENU_BUTTON_Y = 420;

    static const int MENU_OPTION_TOP_LEFT_X = 960;
    static const int MENU_OPTION_TOP_LEFT_Y = 0;

    static const int MENU_OPTION_MARGIN_LEFT = 200;

    QPropertyAnimation *animation;

    //Sons
    GameSoundPlayer *player;
signals:
    void startLevelToGUI(Level *lvl);
public slots:
    void moveViewToMenuOptions();
    void moveViewToMenuPrincipal();
    void cancelOption();
    void resetOption();
    void saveOption();
    void setChecked(MenuRadioButton*radioButton);

};

#endif // MENUPRINCIPAL_H
