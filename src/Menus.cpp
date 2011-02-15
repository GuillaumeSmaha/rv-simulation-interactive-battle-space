#include "Menus.h"

Menus::Menus()
{

    menusRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
    CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
    

    CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
}


void Menus::afficher_souris(void)
{
    CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");
    CEGUI::MouseCursor::getSingleton().setImage(CEGUI::System::getSingleton().getDefaultMouseCursor());
}

void Menus::affiche_btn_exit(void)
{
    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    CEGUI::Window * sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");
    CEGUI::Window * quit = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/QuitButton");
    std::cout<<"quit name: "<<quit->getName()<<std::endl;
    quit->setText("Quit");
    quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05,0)));

    sheet->addChildWindow(quit);
    CEGUI::System::getSingleton().setGUISheet(sheet);
}

Menus::~Menus(){
    
}
