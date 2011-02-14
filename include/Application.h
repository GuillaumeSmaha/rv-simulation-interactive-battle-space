/*!
*  \file  Application.h
*  \brief Ce fichier contient la déclaration de la classe Application. C'est la classe qui permet d'initialiser le logiciel en partie en gérant les aspecs graphiques et évènement
*/
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <Ogre.h>
#include <OISInputManager.h>
#include "ObjectRoot.h"
#include "PlayerControls.h"
#include "ListenerKeyboard.h"
#include "ListenerMouse.h"
#include "ListenerWindow.h"
#include "ListenerFrame.h"
#include "nodeName.h"
#include "CameraFixeAbstract.h"
#include "CameraFixe.h"
#include "CameraFixeTarget.h"
#include "ShipAbstract.h"
#include "ShipIA.h"
#include "ShipPlayer.h"
#include "GestShip.h"
#include "Utils.h"
#include "MeshLoader.h"
#include "Signal.h"
#include "Planet.h"


class ListenerWindow;
class ListenerMouse;
class ListenerKeyboard;
class ListenerFrame;


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
class Application : public ObjectRoot
{
	private:
		/*!
		*  \brief Ogre Root
		*/
		Ogre::Root * root;
		/*!
		*  \brief Scène Manager
		*/
		Ogre::SceneManager * sceneMgr;
		/*!
		*  \brief Chemin du fichier resources.cfg
		*/
		Ogre::String resourcesCfg;
		/*!
		*  \brief Chemin du fichier plugins.cfg
		*/
		Ogre::String pluginsCfg;

		/*!
		* \brief GUI pour afficher les stats
		*/
		Ogre::Overlay * debugOverlay;
		/*!
		* \brief Texte utile pour le debug
		*/
		Ogre::String debugText;

		/*!
		*  \brief Type de la caméra utilisé
		*/
		CameraFixeAbstract::CameraType type_Camera;
		/*!
		*  \brief Pointeur sur la caméra utilisée
		*/
		CameraFixeAbstract * gestCamera;


		/*!
		*  \brief Capteur d'événements
		*/
		OIS::InputManager * inputManager;
		/*!
		* \brief Listener pour les événements fenetre
		*/
		ListenerWindow * listenerWindow;
		/*!
		* \brief Listener pour les événements souris
		*/
		ListenerMouse * listenerMouse;
		/*!
		* \brief Listener pour les événements clavier
		*/
		ListenerKeyboard * listenerKeyboard;
		/*!
		* \brief Listener pour les événements rendu
		*/
		ListenerFrame * listenerFrame;

        /*!
        * \brief gere l'ensemble des vaiseaux
        */
        GestShip * gestShip;


	public: //TODO : faire des fonctions pour ca

		/* Pour la gestion des stats */
		Ogre::Real timeUntilNextToggle;
		bool isStatsOn;
		bool shutDown;


		float _translateX;
		float _translateZ;



	public:
		/*!
		*  \brief Constructeur
		*/
		Application(void);
		/*!
		*  \brief Destructeur
		*/
		~Application(void);

		/*!
		*  \brief Démarre l'application
		*/
		bool start(void);


		/*!
		* \brief Mise à jour des stats (FPS, etc...)
		*/
		void updateStats(void*);
		/*!
		* \brief Affiche l'overlay des stats
		*/
		void showDebugOverlay(bool);
		/*!
		*  \brief Ferme l'application
		*/
		void killApplication();
		/*!
		*  \brief Tue le gestionnaire d'événements
		*/
		void killInputManager();



// Getter/Setter

		/*!
		*  \brief [Getter] Camera
		*/
		CameraFixeAbstract * getGestCamera()
		{
			return this->gestCamera;
		}
        /*!
        * \brief [Getter] gestion des vaiseaux
        */
        GestShip * getGestShip()
        {
            return this->gestShip;
        }
		/*!
		*  \brief [Getter] Capteur d'événements
		*/
		OIS::InputManager * getInputManager()
		{
			return this->inputManager;
		}
		/*!
		*  \brief [Getter] Capteur d'événements fenêtre
		*/
		ListenerWindow * getListenerWindow()
		{
			return this->listenerWindow;
		}
		/*!
		*  \brief [Getter] Capteur d'événements souris
		*/
		ListenerMouse * getListenerMouse()
		{
			return this->listenerMouse;
		}
		/*!
		*  \brief [Getter] Capteur d'événements clavier
		*/
		ListenerKeyboard * getListenerKeyboard()
		{
			return this->listenerKeyboard;
		}
		/*!
		*  \brief [Getter] Capteur d'événements rendu
		*/
		ListenerFrame * getListenerFrame()
		{
			return this->listenerFrame;
		}
		/*!
		*  \brief [Getter] SI on doit fermer l'application
		*/
		bool getShutDown()
		{
			return this->shutDown;
		}
		/*!
		*  \brief [Setter] Ferme l'application
		*/
		void setShutDown(bool shutdown)
		{
			this->shutDown = shutdown;
		}


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
         * \brief Temporaire mais utilise le signal de PlayerControls pour bouger la caméra
         */
        void tempKeyboardControl(PlayerControls::Controls key);
         /*!
         * \brief Temporaire mais utilise le signal de PlayerControls pour bouger la caméra
         */
        void tempKeyboardControlReleased(PlayerControls::Controls key);
        /*!
         * \brief Temporaire mais utilise le signal de PlayerControls pour bouger la caméra
         */
        void tempMouseMoved(Ogre::Vector3 vect);
};

#endif // __APPLICATION_H__
