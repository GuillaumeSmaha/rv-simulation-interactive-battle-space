#include "Message.h"

int Message::nbMessage= 0;


void Message::afficher_message(std::string titre,Ogre::String txt)
{
    affiche=true;
    std::ostringstream internalName;
    internalName<< "tmpText" << Utils::toString(nbMessage);
    nbMessage++;


    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    CEGUI::Window * textWnd= wmgr.createWindow("TaharezLook/StaticText", internalName.str());
    textWnd->setText(txt);
    textWnd->setProperty( "VertScrollbar", "True" );

    this->mainWdw=create_std_window(titre, 0.2, 0.9 ,0.6, 0.06, 1 ,&textWnd);

    CEGUI::System::getSingleton().setGUISheet(this->mainWdw);
    this->mainWdw->show();
}



bool Message::destroyWindow()
{
    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    wmgr.destroyWindow(mainWdw);

    return true;

}
bool Message::destroyWindow(const CEGUI::EventArgs & evt)
{
    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    wmgr.destroyWindow(mainWdw);

    return true;

}

void Message::timer(void *)
{
    if(affiche){
        elapsedtime++;
    }
    if(elapsedtime==100){
        destroyWindow();
        affiche=false;
        elapsedtime=0;
    }
}
