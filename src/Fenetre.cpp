#include "Fenetre.h"

using namespace CEGUI;

CEGUI::Window * Fenetre::create_std_window(CEGUI::utf8 * name, float posX, float posY ,float largeur, float hauteur, int nbEl ,CEGUI::Window ** contenu)
{
    //création de la nouvelle fenetre
    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    CEGUI::Window * Wdw= wmgr.createWindow("DefaultWindow", "SpaceShip/"+(CEGUI::String)name+"main");

    //Titlebar
    CEGUI::Window * titlebar = wmgr.createWindow("TaharezLook/Titlebar", "SpaceShip/titlebar"+(CEGUI::String)name);
    titlebar->setText(name);
    titlebar->setSize(CEGUI::UVector2(CEGUI::UDim(largeur, 0), CEGUI::UDim(0.05,0)));
    titlebar->setPosition(CEGUI::UVector2(CEGUI::UDim(posX, 0), CEGUI::UDim(posY,0)));
    Wdw->addChildWindow(titlebar);

    //création du background
    CEGUI::Window * menuBackground = wmgr.createWindow("TaharezLook/StaticImage", "Background"+(CEGUI::String)name);
    menuBackground->setSize(CEGUI::UVector2(CEGUI::UDim(largeur, 0), CEGUI::UDim(hauteur,0)));
    menuBackground->setPosition(CEGUI::UVector2(CEGUI::UDim(posX,0.0),CEGUI::UDim((posY+0.05),0.0)));

    CEGUI::Window * tmp_contenu;
    int i=0;
    while(i < nbEl)
    {
        tmp_contenu = contenu[i];
        menuBackground->addChildWindow(tmp_contenu);
        i++;
    }

    //on ajoute un close bouton à chaque fenetre
    CEGUI::Window * quit = wmgr.createWindow("SleekSpace/Button", "SpaceShip/close"+(CEGUI::String)name);
    quit->setText("Fermer");
    quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.14,0)));
    quit->setPosition( UVector2( UDim( 0.8, 0.0f ), UDim( 0.85, 0.0f) ) );
    //menuBackground->addChildWindow(quit);
    quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&Fenetre::destroyWindow, this));
    menuBackground->addChildWindow(quit);
    Wdw->addChildWindow(menuBackground);
    return Wdw;


}

