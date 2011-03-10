#include "Menus.h"


using namespace CEGUI;

Menus::Menus(ListenerMouse * mouseControl, ListenerKeyboard * keyControl, PlayerControls * pControl, Application * app)
{
    this->app= app;

    this->mouseControl=mouseControl;
    this->keyControl=keyControl;
    this->pControl=pControl;

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
    creer_menus_start();
}

Menus::~Menus()
{
	mouseControl->signalMousePressed.remove(&Menus::mousePressed, this);
	mouseControl->signalMouseReleased.remove(&Menus::mouseReleased, this);
	mouseControl->signalMouseMoved.remove(&Menus::mouseMoved, this);

    keyControl->signalKeyPressed.remove(&Menus::keyPressed, this);
    keyControl->signalKeyReleased.remove(&Menus::keyReleased, this);

    pControl->signalKeyPressed.remove(&Menus::actionFromPlayer, this);

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
                //suspendre_jeux(); marcheuh paaaas
                afficher_menus();
                this->menu_open = true;

            }
            else
            {
                cacher_menus();
                redemarrer_jeux();
                this->menu_open = false;
            }
			break;
			
		default:
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
    quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.3,0)));
    quit->setPosition( UVector2( UDim( 0.05, 0.0f ), UDim( 0.32, 0.0f) ) );
    //menuBackground->addChildWindow(quit);
    quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Menus::clicExit, this));

    //the restart button
    CEGUI::Window * restart = wmgr.createWindow("SleekSpace/Button", "SpaceShip/restart");
    restart->setText("Redemarrer");
    restart->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.3,0)));
    restart->setPosition( UVector2( UDim( 0.25, 0.0f ), UDim( 0.32, 0.0f) ) );
    //menuBackground->addChildWindow(restart);
    restart->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Menus::clicRestart, this));



    //the About button
    CEGUI::Window * about = wmgr.createWindow("SleekSpace/Button", "SpaceShip/AboutButton");
    about->setText("A propos");
    about->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.3,0)));
    about->setPosition( UVector2( UDim( 0.45, 0.0f ), UDim( 0.32, 0.0f) ) );
    about->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Menus::clicAbout, this));

    //the scenario button
    CEGUI::Window *scenario = wmgr.createWindow("SleekSpace/Button", "SpaceShip/ScenarioButton");
    scenario->setText("Scenario");
    scenario->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.3,0)));
    scenario->setPosition( UVector2( UDim( 0.65, 0.0f ), UDim( 0.32, 0.0f) ) );
    scenario->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Menus::clicScenario, this));



    CEGUI::Window * tblWin[4];
    tblWin[0]=quit;
    tblWin[1]=restart;
    tblWin[2]=about;
    tblWin[3]=scenario;

    this->mainWdw=create_std_window("Combat de vaiseaux", 0.1, 0.05, 0.8, 0.2,4, tblWin);

    this->mainWdw->hide();
}


void Menus::creer_menus_start(void)
{
    CEGUI::Window * startWdw;
    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();

    //the one player button
    CEGUI::Window * onePlayer = wmgr.createWindow("SleekSpace/Button", "SpaceShip/OnePtButton");
    onePlayer->setText("1 joueur");
    onePlayer->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.25,0)));
    onePlayer->setPosition( UVector2( UDim( 0.05, 0.0f ), UDim( 0.32, 0.0f) ) );
    //menuBackground->addChildWindow(onePlayer);
    onePlayer->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Menus::PlayOnePlayer, this));

    //the two player button
    CEGUI::Window * twoPlayer = wmgr.createWindow("SleekSpace/Button", "SpaceShip/TwoPtButton");
    twoPlayer->setText("2 joueur");
    twoPlayer->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.25,0)));
    twoPlayer->setPosition( UVector2( UDim( 0.8, 0.0f ), UDim( 0.32, 0.0f) ) );
    //menuBackground->addChildWindow(twoPlayer);
    twoPlayer->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Menus::PlayTwoPlayer, this));


    CEGUI::Window * tblWin[2];
    tblWin[0]=onePlayer;
    tblWin[1]=twoPlayer;

    startWdw=create_std_window("Choisir mode de jeux", 0.1, 0.05, 0.8, 0.8,2, tblWin);

    afficher_souris();
    CEGUI::System::getSingleton().setGUISheet(startWdw);
    startWdw->show();
}

bool Menus::PlayOnePlayer(const CEGUI::EventArgs & evt){
    destroyWindow(evt);
    this->app->initScene(false);
    cacher_souris();
    return true;
}
bool Menus::PlayTwoPlayer(const CEGUI::EventArgs & evt){
    destroyWindow(evt);
    cacher_souris();
    this->app->initScene(true);
    return true;
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
    CEGUI::System::getSingleton().setGUISheet(this->mainWdw);

    mainWdw->show();
};
bool Menus::clicExit(const CEGUI::EventArgs & evt)
{
    this->app->killApplication();
    return true;
}

bool Menus::clicRestart(const CEGUI::EventArgs & evt)
{
    //permet de refermer proprement la fenetre
      
    this->app->restartScene();
    actionFromPlayer(PlayerControls::OPEN_MENU);
    return true;
}


bool Menus::destroyWindow(const CEGUI::EventArgs & evt)
{
    if(mainWdw==(static_cast<const WindowEventArgs&>(evt).window->getParent()->getParent()))
    {
        actionFromPlayer(PlayerControls::OPEN_MENU);
        signalPaused.dispatch(false);
    }
    else
    {
        CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
        wmgr.destroyWindow((static_cast<const WindowEventArgs&>(evt)).window->getParent()->getParent());
    }
    return true;
}


bool Menus::clicAbout(const CEGUI::EventArgs & evt)
{

    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    //création du texte
    std::string file;
	file.assign(Utils::getFullPathRessources("about.txt"));
    CEGUI::Window * textAbout= wmgr.createWindow("TaharezLook/StaticText", "AboutText");
    Ogre::String txt = Utils::read_file(file.c_str());
    textAbout->setText(txt);
    textAbout->setProperty( "VertScrollbar", "True" );
    CEGUI::Window * nouvWdw= create_std_window("A propos", 0.1, 0.5, 0.8, 0.3, 1, &textAbout);

    this->mainWdw->addChildWindow(nouvWdw);

    return true;
}

bool Menus::clicScenario(const CEGUI::EventArgs & evt)
{

    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    //création du texte
    std::string file;
	file.assign(Utils::getFullPathRessources("scenario.txt"));
    CEGUI::Window * textScen= wmgr.createWindow("TaharezLook/StaticText", "TextScen");
    Ogre::String txt = Utils::read_file(file.c_str());
    textScen->setText(txt);
    textScen->setProperty( "VertScrollbar", "True" );
    //textAbout->setMinSize(UVector2(UDim(2,0), UDim(2,0)));
    CEGUI::Window * nouvWdw= create_std_window("Scenario", 0.1, 0.5, 0.8, 0.3, 1, &textScen);
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
