#include "Menus.h"

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
    creer_btn_exit();
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
    afficher_btn_exit();
}

void Menus::cacher_menus()
{
    cacher_souris();
    cacher_btn_exit();
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


void Menus::creer_btn_exit(void)
{
    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    mainWdw = wmgr.createWindow("DefaultWindow", "SpaceShip/Sheet");
    CEGUI::Window * quit = wmgr.createWindow("SleekSpace/Button", "SpaceShip/QuitButton");
    quit->setText("Quit");
    quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05,0)));
    mainWdw->addChildWindow(quit);
    CEGUI::System::getSingleton().setGUISheet(mainWdw);
    quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Menus::clicExit, this));
    mainWdw->hide();
}

void Menus::cacher_btn_exit(void)
{
    mainWdw->hide();
}

void Menus::afficher_btn_exit(void)
{
    mainWdw->show();
}

bool Menus::clicExit(const CEGUI::EventArgs & evt){
    this->app->killApplication();
    return true;
}


