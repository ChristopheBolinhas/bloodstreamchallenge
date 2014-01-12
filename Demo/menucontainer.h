/**
  TODO:
  - Chargement du niveau au clic --> Renvoie une instance de Level --> Connecter signal -> signal (MenuContainer) et signal -> slot (GUI)
  - Griser les niveaux inaccessibles
  - Bouton Options (Clic sur option --> bascule la vue sur les options et vice versa (animation)) --> Fait !
  - Bouton Quitter --> Fait
  - Menu Options
    * Interaction avec la classe Option (sauvegarde, chargement, reset !)
    * Basculement vers le menu principal (animation) --> Fait
    * Implémentation de l'interface
        * Création de boutons radios pour les langues (MenuRadioButton)
        * Création d'un slider pour le volume (MenuSlider)
        * Création d'une case à cocher pour rendre le jeu muet (MenuCheckBox)
    * Se pencher sur la gestion des langues

    Une seule scène instanciée par MenuContainer et utilisé, DANS LE FUTUR, par MenuPrincipal et MenuOption
    La navigation se fait en déplacant la scène sur un menu ou l'autre.
  **/

#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include "menulevelbutton.h"
#include "menubutton.h"
class QGraphicsView;
class QGraphicsScene;
class QPixmap;
class Level;
class QPropertyAnimation;
class MenuRadioButton;
class MenuSliderCircle;
class MenuCheckBox;
class Option;
#include <QList>
#include <QObject>
#include <QPoint>
#include <QRect>


class MenuContainer : public QObject
{
    Q_OBJECT
public:
    MenuContainer(QGraphicsView *m_view, Option *_option);
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


    //QGraphicsTextItem *labelOptionTitle;
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

signals:
    void startLevel(Level *lvl);
public slots:
    void moveViewToMenuOptions();
    void moveViewToMenuPrincipal();
    void cancelOption();
    void resetOption();
    void saveOption();
    void setChecked(MenuRadioButton*radioButton);

};

#endif // MENUPRINCIPAL_H
