#include "menucontainer.h"
#include "menubutton.h"
#include "menulevelbutton.h"
#include "level.h"
#include "menucheckbox.h"
#include "menuradiobutton.h"
#include "menuslidercircle.h"
#include "gamesoundplayer.h"
#include "option.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QRectF>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QFontDatabase>
#include <QMessageBox>

#include <QDebug>

MenuContainer::MenuContainer(QGraphicsView *_view, Option *_option)
{
    this->option = _option;


    //player->play();
	
    setupScene();

    addGameLogo();

    QList<Level*> listLevels = Level::loadLevels();
    addLevelButtons(listLevels);

    //listLevels.at(0)->setName("popopo");
    Level *lvl = listLevels.at(0);
    lvl->setScore(1230);
    Level::saveLevels(listLevels);
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
    this->scene->update();
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

	QMessageBox::information(NULL,tr("Modification de la langue"),tr("Si vous avez changer la langue, veuillez relancer le jeu."),QMessageBox::Ok);
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

void MenuContainer::startLevelFromButton(Level *lvl)
{
    emit startLevelToGUI(lvl);
}
void MenuContainer::addGameLogo()
{
    this->scene->addPixmap(QPixmap(":/menu/ressources/img/menu/background.png"));
}

void MenuContainer::addLevelButtons(QList<Level *> listLevels)
{
    labelChooseLevel = new QGraphicsTextItem(tr("Choix du niveau: "));
    labelChooseLevel->setFont(QFont("LetterOMatic!", 14));
    labelChooseLevel->moveBy(50,220);

    scene->addItem(labelChooseLevel);

    for (int i = 0; i < listLevels.size(); i++)
    {
        QPointF positionLevel = QPointF(MENU_LEVEL_BUTTON_COOR_X+i%LEVEL_BY_LINE*MENU_LEVEL_BUTTON_MARGE_X,MENU_LEVEL_BUTTON_COOR_Y+i/LEVEL_BY_LINE*MENU_LEVEL_BUTTON_MARGE_Y);
        Level *lvl = listLevels.at(i);
        MenuLevelButton *btn = new MenuLevelButton(positionLevel, lvl);

        connect(btn, SIGNAL(startLevel(Level*)), this, SLOT(startLevelFromButton(Level*)));
        scene->addItem(btn);
    }
}

void MenuContainer::addQuitOptionsButtons()
{
    btnQuitter = new MenuButton(QPointF(125,MENU_BUTTON_Y),tr("Quitter"));
    btnOption = new MenuButton(QPointF(510,MENU_BUTTON_Y),tr("Options"));

    connect(btnQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(btnOption, SIGNAL(clicked()), this, SLOT(moveViewToMenuOptions()));

    scene->addItem(btnQuitter);
    scene->addItem(btnOption);
}

void MenuContainer::addMenuOptions()
{
    btnValider = new MenuButton(QPointF((SCENE_SIZE_X/2)+40,MENU_BUTTON_Y), tr("Valider"));
    btnAnnuler = new MenuButton(QPointF((SCENE_SIZE_X/2)+340,MENU_BUTTON_Y), tr("Annuler"));
    btnReset = new MenuButton(QPointF((SCENE_SIZE_X/2)+640,MENU_BUTTON_Y), tr("Reinitialiser"));

    labelOptionLangue = new QGraphicsTextItem(tr("Langue:"));
    labelOptionLangue->setFont(QFont("LetterOMatic!", 12));
    labelOptionLangue->moveBy(MENU_OPTION_TOP_LEFT_X+MENU_OPTION_MARGIN_LEFT,90);

    // Langues
    mrbtnLangueFrancais = new MenuRadioButton(QRect(MENU_OPTION_TOP_LEFT_X+MENU_OPTION_MARGIN_LEFT+20,120,32,32),true);

    labelOptionLangueFrancais = new QGraphicsTextItem(tr("Francais"));
    labelOptionLangueFrancais->setFont(QFont("LetterOMatic!", 12));
    labelOptionLangueFrancais->moveBy(MENU_OPTION_TOP_LEFT_X+MENU_OPTION_MARGIN_LEFT+60,120);

    mrbtnLangueAnglais = new MenuRadioButton(QRect(MENU_OPTION_TOP_LEFT_X+MENU_OPTION_MARGIN_LEFT+20,160,32,32),false);

    labelOptionLangueAnglais = new QGraphicsTextItem(tr("Anglais"));
    labelOptionLangueAnglais->setFont(QFont("LetterOMatic!", 12));
    labelOptionLangueAnglais->moveBy(MENU_OPTION_TOP_LEFT_X+MENU_OPTION_MARGIN_LEFT+60,160);

    // Volume
    mscVolume = new MenuSliderCircle(QPoint(MENU_OPTION_TOP_LEFT_X+MENU_OPTION_MARGIN_LEFT+20,240),32,0,100,2,this->scene);
    mscVolume->setValue(option->getVolume());

    labelOptionVolume = new QGraphicsTextItem(tr("Volume"));
    labelOptionVolume->setFont(QFont("LetterOMatic!", 12));
    labelOptionVolume->moveBy(MENU_OPTION_TOP_LEFT_X+MENU_OPTION_MARGIN_LEFT,200);

    mcbxMute = new MenuCheckBox(QRect(MENU_OPTION_TOP_LEFT_X+MENU_OPTION_MARGIN_LEFT+80,280,32,32),option->isMute());

    labelOptionMute = new QGraphicsTextItem(tr("Muet: "));
    labelOptionMute->setFont(QFont("LetterOMatic!", 12));
    labelOptionMute->moveBy(MENU_OPTION_TOP_LEFT_X+MENU_OPTION_MARGIN_LEFT,280);

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
    scene->addItem(labelOptionLangueFrancais);
    scene->addItem(labelOptionLangueAnglais);
    scene->addItem(labelOptionLangue);
    scene->addItem(labelOptionVolume);
    scene->addItem(labelOptionMute);
    scene->addItem(btnReset);
    scene->addItem(btnValider);
    scene->addItem(btnAnnuler);

    resetOption(); // met les valeurs par defaut à la fin de la construction du menu option
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
    qDebug() << "Font importée ?: " << QFontDatabase::addApplicationFont(":/font/ressources/font/ltromatic.ttf");
}
