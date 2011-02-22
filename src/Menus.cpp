#include "Menus.h"

using namespace CEGUI;

Menus::Menus(ListenerMouse * mouseControl, ListenerKeyboard * keyControl, PlayerControls * pControl, Application * app)
{
    this->app= app;

    //démarre le menusRenderer
    menusRenderer = &CEGUI::OgreRenderer::bootstrapSystem();

    //prépare les différents groupes de ressources
    CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

    //charge un scheme
    CEGUI::SchemeManager::getSingleton().create("SleekSpace.scheme");
    CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");

    //enregistre les signaux sur la souris
	mouseControl->signalMousePressed.add(&Menus::mousePressed, this);
	mouseControl->signalMouseReleased.add(&Menus::mouseReleased, this);
	mouseControl->signalMouseMoved.add(&Menus::mouseMoved, this);

    //enregistre les signaux sur le clavier
    keyControl->signalKeyPressed.add(&Menus::keyPressed, this);
    keyControl->signalKeyReleased.add(&Menus::keyReleased, this);

    //enregistre les signaux sur PlayerControls (même si réagit uniquement à l'appui sur la touche permettant d'ouvrir le menus
    pControl->signalKeyPressed.add(&Menus::actionFromPlayer, this);
    this->menu_open=false;   

    creer_souris();
    creer_main_window();
}

Menus::~Menus()
{

}

void Menus::keyPressed(const OIS::KeyEvent &evt)
{
    CEGUI::System &sys = CEGUI::System::getSingleton();
    sys.injectKeyDown(evt.key);
    sys.injectChar(evt.text);
}


void Menus::actionFromPlayer(PlayerControls::Controls key)
{
	switch(key)
	{
		case PlayerControls::OPEN_MENU:
            if(!this->menu_open)
            {
                std::cout<<"ouvrir"<<std::endl;
                afficher_menus();
                this->menu_open=true;
            }
            else
            {
                std::cout<<"fermer"<<std::endl;
                cacher_menus();
                this->menu_open=false;
            }
			break;
	}
}

void Menus::afficher_menus()
{
    afficher_souris();
    afficher_main_window();
}

void Menus::cacher_menus()
{
    cacher_souris();
    cacher_main_window();
}

void Menus::keyReleased(const OIS::KeyEvent &evt)
{
    CEGUI::System::getSingleton().injectKeyUp(evt.key);
}

void Menus::mousePressed(OIS::MouseButtonID evt)
{
    CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(evt));
}
void Menus::mouseReleased(OIS::MouseButtonID evt)
{
    CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(evt));
}

void Menus::mouseMoved(Ogre::Vector3 vect)
{
    CEGUI::System &sys = CEGUI::System::getSingleton();
    sys.injectMouseMove(vect[0], vect[1]);
    // Scroll wheel.
    if (vect[2])
        sys.injectMouseWheelChange(vect[2] / 120.0f);
}

CEGUI::MouseButton Menus::convertButton(OIS::MouseButtonID evt)
{
    switch (evt)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;

    case OIS::MB_Right:
        return CEGUI::RightButton;

    case OIS::MB_Middle:
        return CEGUI::MiddleButton;

    default:
        return CEGUI::LeftButton;
    }
}

void Menus::creer_souris(void)
{
    CEGUI::System::getSingleton().setDefaultMouseCursor("SleekSpace", "MouseArrow");
    CEGUI::MouseCursor::getSingleton().setImage(CEGUI::System::getSingleton().getDefaultMouseCursor());
    CEGUI::MouseCursor::getSingleton().hide();
}

void Menus::afficher_souris(void)
{
    CEGUI::MouseCursor::getSingleton().show();
}

void Menus::cacher_souris(void)
{
    CEGUI::MouseCursor::getSingleton().hide();
}


void Menus::creer_main_window(void)
{

    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    this->mainWdw = wmgr.createWindow("DefaultWindow", "SpaceShip/Sheet");


    //First the Titlebar
    CEGUI::Window * titlebar= wmgr.createWindow("TaharezLook/Titlebar", "titlebar");
    titlebar->setText("combat de l'espace");
    titlebar->setSize(CEGUI::UVector2(CEGUI::UDim(0.8, 0), CEGUI::UDim(0.05,0)));
    titlebar->setPosition(CEGUI::UVector2(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.25,0)));
    this->mainWdw->addChildWindow(titlebar);

    //The background
    CEGUI::Window * menuBackground = wmgr.createWindow("TaharezLook/StaticImage", "Background");
    menuBackground->setSize(CEGUI::UVector2(CEGUI::UDim(0.8, 0), CEGUI::UDim(0.10,0)));
    menuBackground->setPosition(CEGUI::UVector2(CEGUI::UDim(0.1,0.0),CEGUI::UDim(0.3,0.0)));
    this->mainWdw->addChildWindow(menuBackground);

    //the Quit button
    CEGUI::Window * quit = wmgr.createWindow("SleekSpace/Button", "SpaceShip/AboutButton");
    quit->setText("Quit");
    quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.3,0)));
    quit->setPosition( UVector2( UDim( 0.2, 0.0f ), UDim( 0.32, 0.0f) ) );
    menuBackground->addChildWindow(quit);
    quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Menus::clicExit, this));

    //the About button
    CEGUI::Window * about = wmgr.createWindow("SleekSpace/Button", "SpaceShip/QuitButton");
    about->setText("A propos");
    about->setSize(CEGUI::UVector2(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.3,0)));
    about->setPosition( UVector2( UDim( 0.45, 0.0f ), UDim( 0.32, 0.0f) ) );
    menuBackground->addChildWindow(about);
    about->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Menus::clicAbout, this));

    CEGUI::System::getSingleton().setGUISheet(this->mainWdw);
    mainWdw->hide();
}

//void Menus::creer_background(void)
//{

//}


void Menus::cacher_main_window(void)
{
    mainWdw->hide();
}

void Menus::afficher_main_window(void)
{
    mainWdw->show();
}

bool Menus::clicExit(const CEGUI::EventArgs & evt){
    this->app->killApplication();
    return true;
}

bool Menus::clicAbout(const CEGUI::EventArgs & evt){
    //création de la nouvelle fenetre
    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    CEGUI::Window * aboutWdw= wmgr.createWindow("DefaultWindow", "SpaceShip/AboutSheet");

    //Titlebar
    CEGUI::Window * titlebar= wmgr.createWindow("TaharezLook/Titlebar", "titlebarAbout");
    titlebar->setText("A propos");
    titlebar->setSize(CEGUI::UVector2(CEGUI::UDim(0.8, 0), CEGUI::UDim(0.05,0)));
    titlebar->setPosition(CEGUI::UVector2(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.5,0)));
    aboutWdw->addChildWindow(titlebar);

    //création du background
    CEGUI::Window * menuBackground = wmgr.createWindow("TaharezLook/StaticImage", "AboutBackground");
    menuBackground->setSize(CEGUI::UVector2(CEGUI::UDim(0.8, 0), CEGUI::UDim(0.10,0)));
    menuBackground->setPosition(CEGUI::UVector2(CEGUI::UDim(0.1,0.0),CEGUI::UDim(0.55,0.0)));
    aboutWdw->addChildWindow(menuBackground);
    
    CEGUI::Window * aboutScrollPane= wmgr.createWindow("TaharezLook/ScrollablePane", "AboutScroll");
    aboutScrollPane->setSize(CEGUI::UVector2(CEGUI::UDim(1.0,0), CEGUI::UDim(1.0,0)));
    menuBackground->addChildWindow(aboutScrollPane);
    

    //création du texte
    CEGUI::Window * textAbout= wmgr.createWindow("TaharezLook/StaticText", "AboutText");
    textAbout->setText("Jeux créé par :\n \
       [colour='FFFF0000'] Guillaume Smaha [colour='FFFFFFFF'],\n \
       [colour='FFFF0000'] Pierre Vittet [colour='FFFFFFFF'],\n \
       [colour='FFFF0000'] Jérémy Dubois [colour='FFFFFFFF'],\n \
       [colour='FFFF0000'] Dimitry Bourreau [colour='FFFFFFFF'],\n \
       [colour='FFFF0000'] Nicolas Fontenit [colour='FFFFFFFF'],\n \
       [colour='FFFF0000'] Pascal Burdin [colour='FFFFFFFF'],\n \
       [colour='FFFF0000'] Ting Shuo WANG [colour='FFFFFFFF'],\n \
        ");
     

//textAbout->setText("This is just some text that shows how nicely [colour='FFFF0000']CEGUI \
can format strings.[colour='FF00FF00'] and this is just colour [colour='FF0000FF'] formatting!");
    aboutScrollPane->addChildWindow(textAbout);

    this->mainWdw->addChildWindow(aboutWdw);

    
    return true;
}
