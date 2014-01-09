#include "menucontainer.h"
#include "menubutton.h"
#include "menulevelbutton.h"
#include "level.h"
#include "menucheckbox.h"
#include "menuradiobutton.h"
#include "menuslidercircle.h"
#include "option.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QRectF>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QDebug>

MenuContainer::MenuContainer(QGraphicsView *_view, Option *_option)
{
    this->option = _option;

    setupScene();

    addGameLogo();

    QList<Level*> listLevels = Level::loadLevels();
    addLevelButtons(listLevels);

    addQuitOptionsButtons();

    addMenuOptions();

    setupView(_view);

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

void MenuContainer::cancelOption()
{
    this->resetOption();
    this->moveViewToMenuPrincipal();
}

void MenuContainer::resetOption()
{
    // on recharge les dernières options sauvegardées
    this->option->loadOption();

    int defaultVolume = this->option->getVolume();
    bool defaultMute = this->option->isMute();

    this->mscVolume->setValue(defaultVolume);
    this->mcbxMute->setChecked(defaultMute);

    switch(this->option->getLanguage())
    {
    case Option::french:
        this->setChecked(mrbtnLangueFrancais);
        break;
    case Option::english:
        this->setChecked(mrbtnLangueAnglais);
        break;
    }
}

void MenuContainer::saveOption()
{
    this->option->setVolume(mscVolume->getValue());
    this->option->setMute(mcbxMute->getChecked());


    if(mrbtnLangueAnglais->getChecked())
        this->option->setLanguage(Option::english);
    else if(mrbtnLangueFrancais->getChecked())
        this->option->setLanguage(Option::french);

    this->option->saveOption();

    moveViewToMenuPrincipal();
}

void MenuContainer::setChecked(MenuRadioButton *mrbtn)
{
    foreach (MenuRadioButton *item, listMenuRadioButton) {
        item->setChecked(false);
        item->update();
    }
    mrbtn->setChecked(true);
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

    btnValider = new MenuButton(new QRectF((SCENE_SIZE_X/2)+80,480,MENU_BUTTON_WIDTH,MENU_BUTTON_HEIGHT), tr("Valider"));
    btnAnnuler = new MenuButton(new QRectF((SCENE_SIZE_X/2)+380,480,MENU_BUTTON_WIDTH,MENU_BUTTON_HEIGHT), tr("Annuler"));
    btnReset = new MenuButton(new QRectF((SCENE_SIZE_X/2)+680,480,MENU_BUTTON_WIDTH,MENU_BUTTON_HEIGHT), tr("Réinitialiser"));

    labelOptionLangue = new QGraphicsTextItem(tr("Langue:"));
    labelOptionLangue->setFont(QFont("Comic Sans MS", 14));
    labelOptionLangue->moveBy(980,90);

    // Langues
    mrbtnLangueFrancais = new MenuRadioButton(QRect(1000,120,32,32),true);

    labelOptionLangueFrancais = new QGraphicsTextItem(tr("Français"));
    labelOptionLangueFrancais->setFont(QFont("Comic Sans MS", 14));
    labelOptionLangueFrancais->moveBy(1040,120);

    mrbtnLangueAnglais = new MenuRadioButton(QRect(1000,160,32,32),false);

    labelOptionLangueAnglais = new QGraphicsTextItem(tr("Anglais"));
    labelOptionLangueAnglais->setFont(QFont("Comic Sans MS", 14));
    labelOptionLangueAnglais->moveBy(1040,160);

    // Volume
    mscVolume = new MenuSliderCircle(QPoint(1000,240),32,0,100,2);
    mscVolume->setValue(option->getVolume());

    labelOptionVolume = new QGraphicsTextItem(tr("Volume"));
    labelOptionVolume->setFont(QFont("Comic Sans MS", 14));
    labelOptionVolume->moveBy(980,200);

    mcbxMute = new MenuCheckBox(QRect(1040,280,32,32),option->isMute());

    labelOptionMute = new QGraphicsTextItem(tr("Muet: "));
    labelOptionMute->setFont(QFont("Comic Sans MS", 14));
    labelOptionMute->moveBy(980,280);

    connect(btnAnnuler, SIGNAL(clicked()), this, SLOT(cancelOption()));
    connect(btnValider, SIGNAL(clicked()), this, SLOT(saveOption()));
    connect(btnReset, SIGNAL(clicked()), this, SLOT(resetOption()));

    connect(mrbtnLangueFrancais,SIGNAL(checkStateChanged(MenuRadioButton*)), this, SLOT(setChecked(MenuRadioButton*)));
    connect(mrbtnLangueAnglais,SIGNAL(checkStateChanged(MenuRadioButton*)), this, SLOT(setChecked(MenuRadioButton*)));

    listMenuRadioButton = QList<MenuRadioButton*>();
    listMenuRadioButton.append(mrbtnLangueFrancais);
    listMenuRadioButton.append(mrbtnLangueAnglais);

    for(int i=0; i < listMenuRadioButton.size(); i++)
    {
        scene->addItem(listMenuRadioButton.at(i));
    }
    scene->addItem(mscVolume);
    scene->addItem(mrbtnLangueFrancais);
    scene->addItem(mrbtnLangueAnglais);
    scene->addItem(mcbxMute);
    scene->addItem(labelOptionTitle);
    scene->addItem(labelOptionLangueFrancais);
    scene->addItem(labelOptionLangueAnglais);
    scene->addItem(labelOptionLangue);
    scene->addItem(labelOptionVolume);
    scene->addItem(labelOptionMute);
    scene->addItem(btnReset);
    scene->addItem(btnValider);
    scene->addItem(btnAnnuler);

    resetOption(); // met les valeurs par defaut a la fin de la construction du menu option
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
