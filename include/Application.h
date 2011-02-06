/*!
 *  \file  Application.h
 *  \brief Ce fichier contient la déclaration de la classe Application. C'est la classe qui permet d'initialiser le logiciel en partie en gérant les aspecs graphiques et évènement
 */
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <Ogre.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include "Camera.h"
#include "CameraFixe.h"
#include "cameraType.h"

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
		/*!
		 *  \brief Ogre Root
		 */
        Ogre::Root * root;
		/*!
		 *  \brief Scène Manager
		 */
        Ogre::SceneManager *sceneMgr;
		/*!
		 *  \brief Fenêtre de Rendu
		 */
        Ogre::RenderWindow *window;
		/*!
		 *  \brief Chemin du fichier resources.cfg
		 */
        Ogre::String resourcesCfg;
		/*!
		 *  \brief Chemin du fichier plugins.cfg
		 */
        Ogre::String pluginsCfg;
        
		/*!
		 *  \brief Capteur d'événements
		 */
        OIS::InputManager * inputManager;
		/*!
		 *  \brief Capteur d'événements de la souris
		 */
        OIS::Mouse * mouse;
		/*!
		 *  \brief Capteur d'événements de la clavier
		 */
        OIS::Keyboard * keyboard;
    
		/*!
		 *  \brief Type de la caméra utilisé
		 */
        EnumTypeCamera type_Camera;
		/*!
		 *  \brief Pointeur sur la caméra utilisée
		 */
        Camera * gestCamera;
		/*!
		 *  \brief Indique si l'application doit-être arrếtée
		 */
        bool shutDown;


    public:
		/*!
		 *  \brief Constructeur
		 */
	    Application(void);
		/*!
		 *  \brief Destructeur
		 */
	    virtual ~Application(void);
		/*!
		 *  \brief Démarre l'application
		 */
	    bool start(void);	
        
	private:
		/*!
		 *  \brief Charge les ressources listées dans resources.cfg
		 */
        void loadRessources(void);
		/*!
		 *  \brief Initialise l'écoute de l'entrée clavier et souris
		 */
        void initListeners(void);
		/*!
		 *  \brief Initialise le graphe de scène
		 */
        void initSceneGraph(void);
		/*!
		 *  \brief Initialise la scène
		 */
        void initScene(void);
		/*!
		 *  \brief Génère la frame de rendu
		 */
        bool frameRenderingQueued(const Ogre::FrameEvent& evt);
        
        // Ogre::WindowEventListener
		/*!
		 *  \brief Action à effectuer pour l'événement "redimensionnement de la fenêtre"
		 * 	\param rw Fenêtre de rendu
		 */
        void windowResized(Ogre::RenderWindow* rw);
		/*!
		 *  \brief Action à effectuer pour l'événement "fermeture de la fenêtre"
		 * 	\param rw Fenêtre de rendu
		 */
        void windowClosed(Ogre::RenderWindow* rw);
        
        // OIS::KeyListener
		/*!
		 *  \brief Action à effectuer pour l'événement "touche pressée"
		 * 	\param evt Evenement du clavier
		 */
        bool keyPressed( const OIS::KeyEvent &evt );
		/*!
		 *  \brief Action à effectuer pour l'événement "touche relachée"
		 * 	\param evt Evenement du clavier
		 */
        bool keyReleased( const OIS::KeyEvent &evt );
        
        // OIS::MouseListener
		/*!
		 *  \brief Action à effectuer pour l'événement "souis en mouvement"
		 * 	\param evt Evenement de la souris
		 */
        bool mouseMoved( const OIS::MouseEvent &evt );
		/*!
		 *  \brief Action à effectuer pour l'événement "touche de la souris cliquée"
		 * 	\param evt Evenement de la souris
		 * 	\param id Identifiant du bouton de la souris
		 */
        bool mousePressed( const OIS::MouseEvent &evt, OIS::MouseButtonID id );
		/*!
		 *  \brief Action à effectuer pour l'événement "touche de la souris relachée"
		 * 	\param evt Evenement de la souris
		 * 	\param id Identifiant du bouton de la souris
		 */
        bool mouseReleased( const OIS::MouseEvent &evt, OIS::MouseButtonID id );
	
};

#endif // __APPLICATION_H__
