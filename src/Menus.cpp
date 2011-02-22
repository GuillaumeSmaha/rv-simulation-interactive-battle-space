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
    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    wmgr.destroyAllWindows();
    this->menusRenderer->destroyAllGeometryBuffers ();
    this->menusRenderer->destroyAllTextureTargets ();
    this->menusRenderer->destroyAllTextures ();
    CEGUI::OgreRenderer::destroySystem ();
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
                suspendre_jeux();
                afficher_menus();
                this->menu_open=true;

            }
            else
            {
                std::cout<<"fermer"<<std::endl;
                cacher_menus();
                redemarrer_jeux();
                this->menu_open=false;
            }
			break;
	}
}

void Menus::afficher_menus()
{
    afficher_souris();
    afficher_main_window();
    signalPaused.dispatch(true);
}

void Menus::cacher_menus()
{
    cacher_souris();
    cacher_main_window();
    signalPaused.dispatch(false);
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

    //the Quit button
    CEGUI::Window * quit = wmgr.createWindow("SleekSpace/Button", "SpaceShip/QuitButton");
    quit->setText("Quit");
    quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.3,0)));
    quit->setPosition( UVector2( UDim( 0.2, 0.0f ), UDim( 0.32, 0.0f) ) );
    //menuBackground->addChildWindow(quit);
    quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Menus::clicExit, this));

    //the About button
    CEGUI::Window * about = wmgr.createWindow("SleekSpace/Button", "SpaceShip/AboutButton");
    about->setText("A propos");
    about->setSize(CEGUI::UVector2(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.3,0)));
    about->setPosition( UVector2( UDim( 0.45, 0.0f ), UDim( 0.32, 0.0f) ) );
    //menuBackground->addChildWindow(about);
    about->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Menus::clicAbout, this));

    CEGUI::Window * tblWin[2];
    tblWin[0]=quit;
    tblWin[1]=about;

    this->mainWdw=create_std_window("Combat de vaiseaux", 0.1, 0.05, 0.8, 0.1,2, tblWin);

    CEGUI::System::getSingleton().setGUISheet(this->mainWdw);
    this->mainWdw->hide();
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
};
bool Menus::clicExit(const CEGUI::EventArgs & evt){
    this->app->killApplication();
    return true;
}

CEGUI::Window * Menus::create_std_window(std::string name, float posX, float posY ,float largeur, float hauteur, int nbEl ,CEGUI::Window ** contenu)
{
    //création de la nouvelle fenetre
    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    CEGUI::Window * Wdw= wmgr.createWindow("DefaultWindow", "SpaceShip/"+name+"main");

    //Titlebar
    CEGUI::Window * titlebar= wmgr.createWindow("TaharezLook/Titlebar", "SpaceShip/titlebar"+name);
    titlebar->setText(name);
    titlebar->setSize(CEGUI::UVector2(CEGUI::UDim(largeur, 0), CEGUI::UDim(0.05,0)));
    titlebar->setPosition(CEGUI::UVector2(CEGUI::UDim(posX, 0), CEGUI::UDim(posY,0)));
    Wdw->addChildWindow(titlebar);

    //création du background
    CEGUI::Window * menuBackground = wmgr.createWindow("TaharezLook/StaticImage", "Background"+name);
    menuBackground->setSize(CEGUI::UVector2(CEGUI::UDim(largeur, 0), CEGUI::UDim(hauteur,0)));
    menuBackground->setPosition(CEGUI::UVector2(CEGUI::UDim(posX,0.0),CEGUI::UDim((posY+0.05),0.0)));

    CEGUI::Window * tmp_contenu;
    int i=0;
    while(i<nbEl)
    {
        tmp_contenu=contenu[i];
        menuBackground->addChildWindow(tmp_contenu);
        i++;
    }

    //on ajoute un close bouton à chaque fenetre
    CEGUI::Window * quit = wmgr.createWindow("SleekSpace/Button", "SpaceShip/close"+name);
    quit->setText("Fermer");
    quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.2,0)));
    quit->setPosition( UVector2( UDim( 0.8, 0.0f ), UDim( 0.7, 0.0f) ) );
    //menuBackground->addChildWindow(quit);
    quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Menus::destroyWindow, this));
    menuBackground->addChildWindow(quit);
    Wdw->addChildWindow(menuBackground);
    return Wdw;


}
bool Menus::destroyWindow(const CEGUI::EventArgs & evt)
{
    if(mainWdw==(static_cast<const WindowEventArgs&>(evt).window->getParent()->getParent()))
    {
        actionFromPlayer(PlayerControls::OPEN_MENU);
    }
    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    wmgr.destroyWindow((static_cast<const WindowEventArgs&>(evt)).window->getParent()->getParent());
    signalPaused.dispatch(false);
    return true;
}


bool Menus::clicAbout(const CEGUI::EventArgs & evt)
{

    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
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
    textAbout->setProperty( "VertScrollbar", "True" );
    //textAbout->setMinSize(UVector2(UDim(2,0), UDim(2,0)));
    CEGUI::Window * nouvWdw= create_std_window("A propos", 0.1, 0.5, 0.8, 0.2, 1, &textAbout);


    this->mainWdw->addChildWindow(nouvWdw);


    return true;
}


void Menus::suspendre_jeux()
{
    this->app->suspendre_jeux();
}

void Menus::redemarrer_jeux()
{
    this->app->redemarrer_jeux();
}
