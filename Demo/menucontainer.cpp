#include "menucontainer.h"
#include "menubutton.h"
#include "menulevelbutton.h"
#include "level.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QRectF>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

#include <QDebug>

MenuContainer::MenuContainer(QGraphicsView *m_view)
{
    setupScene();

    addGameLogo();

    QList<Level*> listLevels = Level::loadLevels();
    addLevelButtons(listLevels);

    addQuitOptionsButtons();

    addMenuOptions();

    setupView(m_view);

    initializationAnimation();
}

MenuContainer::~MenuContainer()
{
    //TODO: ...
}

QGraphicsScene *MenuContainer::getScene() const
{
    return scene;
}

void MenuContainer::moveViewToMenuOptions()
{
    animation->setStartValue(QRect(0,0,SCENE_SIZE_X/2,SCENE_SIZE_Y));
    animation->setEndValue(QRect(SCENE_SIZE_X/2,0,SCENE_SIZE_X/2,SCENE_SIZE_Y));
    //animation->setEasingCurve(QEasingCurve::InBack);
    animation->start();
}

void MenuContainer::moveViewToMenuPrincipal()
{
    animation->setStartValue(QRect(SCENE_SIZE_X/2,0,SCENE_SIZE_X/2,SCENE_SIZE_Y));
    animation->setEndValue(QRect(0,0,SCENE_SIZE_X/2,SCENE_SIZE_Y));
    //animation->setEasingCurve(QEasingCurve::InBack);
    animation->start();
}

void MenuContainer::addGameLogo()
{
    QGraphicsPixmapItem *itemLogo = this->scene->addPixmap(QPixmap("://ressources/img/logo.png"));
    itemLogo->moveBy(50,0);
}

void MenuContainer::addLevelButtons(QList<Level *> listLevels)
{
    labelChooseLevel = new QGraphicsTextItem(tr("Choix du niveau: "));
    labelChooseLevel->setFont(QFont("Comic Sans MS", 16));
    labelChooseLevel->moveBy(50,200);

    scene->addItem(labelChooseLevel);

    for (int i = 0; i < listLevels.size(); i++)
    {
        QRectF *rectangleLevel = new QRectF(MENU_LEVEL_BUTTON_COOR_X+i%LEVEL_BY_LINE*MENU_LEVEL_BUTTON_MARGE_X,MENU_LEVEL_BUTTON_COOR_Y+i/LEVEL_BY_LINE*MENU_LEVEL_BUTTON_MARGE_Y,MENU_LEVEL_BUTTON_WIDTH,MENU_LEVEL_BUTTON_HEIGHT);
        Level *lvl = listLevels.at(i);
        MenuLevelButton *btn = new MenuLevelButton(rectangleLevel, lvl);

        connect(btn, SIGNAL(startLevel(Level*)), this, SIGNAL(startLevel(Level*)));
        scene->addItem(btn);
    }
}

void MenuContainer::addQuitOptionsButtons()
{
    btnQuitter = new MenuButton(new QRectF(70,480,MENU_BUTTON_WIDTH,MENU_BUTTON_HEIGHT),"Quitter");
    btnOption = new MenuButton(new QRectF(370,480,MENU_BUTTON_WIDTH,MENU_BUTTON_HEIGHT),"Options");

    connect(btnQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(btnOption, SIGNAL(clicked()), this, SLOT(moveViewToMenuOptions()));

    scene->addItem(btnQuitter);
    scene->addItem(btnOption);
}

void MenuContainer::addMenuOptions()
{
    labelOptionTitle = new QGraphicsTextItem(tr("Menu des options"));
    labelOptionTitle->setFont(QFont("Comic Sans MS", 24));
    labelOptionTitle->moveBy(960,50);


    btnAnnuler = new MenuButton(new QRectF((SCENE_SIZE_X/2)+410,480,MENU_BUTTON_WIDTH,MENU_BUTTON_HEIGHT), tr("Annuler"));
    //TODO: btnValider, btnReset,...

    connect(btnAnnuler, SIGNAL(clicked()), this, SLOT(moveViewToMenuPrincipal()));

    scene->addItem(labelOptionTitle);
    scene->addItem(btnAnnuler);
}

void MenuContainer::setupView(QGraphicsView *m_view)
{
    this->view = m_view;
    view->setScene(scene);

    view->setSceneRect(0,0,SCENE_SIZE_X/2,SCENE_SIZE_Y+5); // fixe la scène, évite de la déplacer avec les touches du clavier
    view->centerOn(SCENE_SIZE_X/4,SCENE_SIZE_Y/2);
}

void MenuContainer::initializationAnimation()
{
    animation = new QPropertyAnimation(view,"sceneRect");
    animation->setDuration(500);
}

void MenuContainer::setupScene()
{
    scene = new QGraphicsScene();
}
