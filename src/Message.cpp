#include "Message.h"

int Message::nbMessage= 0;

Message * Message::_instance = NULL;

Message* Message::getSingleton(void)
{
	if (_instance == NULL)
	{
        std::cout<<"Intance doit être initalisé explicitement une premiere fois"<<std::endl;
	}
	return _instance;
}

void Message::afficher_message(CEGUI::utf8 * titre,CEGUI::utf8 * txt)
{
    //si un message est déja afficher on le détruit avant d'en afficher un autre
    if(affiche==true)
    {
        destroyWindow();
    }
    affiche = true;
    std::ostringstream internalName;
    internalName << "tmpText" << Utils::toString(nbMessage);
    nbMessage++;


    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    CEGUI::Window * textWnd = wmgr.createWindow("TaharezLook/StaticText", internalName.str());
    textWnd->setText(txt);
    textWnd->setProperty( "VertScrollbar", "True" );

    this->mainWdw = create_std_window(  titre, 0.2, 0.9 ,0.6, 0.06, 1 ,&textWnd);

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
    if(affiche)
    {
        elapsedtime++;
    }
    
    if(elapsedtime == 100)
    {
        destroyWindow();
        affiche = false;
        elapsedtime = 0;
    }
}
