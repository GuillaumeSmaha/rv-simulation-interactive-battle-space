/*!
 **  \file  Application.h
 **  \brief Ce fichier contient la déclaration de la classe Application. C'est la classe qui permet d'initialiser le logiciel en partie en gérant les aspecs graphiques et évènement
 **/
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <Ogre.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include "Camera.h"
#include "symbole.h"

/*!
 * \class Application
 * \brief Class principale qui permet de démarrer le programme, d'afficher la fenêtre et de réagir aux évènements (ceux-ci sont ensuite dirigé vers les classes adaptés)
 *   
 *   En particulier elle hérite de:
 *   Ogre::FrameListener : Permet de recevoir les notifications avant et aprés chaque frame rendu à l'écran
 *
 *   Ogre::WindowEventListener : Permet d'obtenir les informations de déplacement/redimmensionnement de la fenetre ainsi que sa demande de fermeture
 *   
 *   OIS::KeyListener : Information sur les évènements claviers
 *   
 *   OIS::MouseListener
 */
class Application : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener {
	private:
        Ogre::Root *root;
        Ogre::SceneManager *sceneMgr;
        Ogre::RenderWindow *window;
        Ogre::String resourcesCfg;
        Ogre::String pluginsCfg;
        
        OIS::InputManager *inputManager;
        OIS::Mouse *mouse;
        OIS::Keyboard *keyboard;
    
        int type_Camera;
        Camera* gestCamera;
        bool shutDown;
        
        void loadRessources(void);
        void initListeners(void);
        void initScene(void);
        bool frameRenderingQueued(const Ogre::FrameEvent& evt);
        
        // Ogre::WindowEventListener
        void windowResized(Ogre::RenderWindow* rw);
        void windowClosed(Ogre::RenderWindow* rw);
        
        // OIS::KeyListener
        bool keyPressed( const OIS::KeyEvent &evt );
        bool keyReleased( const OIS::KeyEvent &evt );
        
        // OIS::MouseListener
        bool mouseMoved( const OIS::MouseEvent &evt );
        bool mousePressed( const OIS::MouseEvent &evt, OIS::MouseButtonID id );
        bool mouseReleased( const OIS::MouseEvent &evt, OIS::MouseButtonID id );


    public:
	    Application(void);
	    virtual ~Application(void);
	    bool start(void);	
	
};

#endif // __DEMO_H__
