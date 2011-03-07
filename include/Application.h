/*!
*  \file  Application.h
*  \brief Ce fichier contient la déclaration de la classe Application. C'est la classe qui permet d'initialiser le logiciel en partie en gérant les aspecs graphiques et évènement
*/
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <Ogre.h>
#include <OISInputManager.h>
#include "nodeName.h"
#include "ObjectRoot.h"
#include "Utils.h"
#include "Signal.h"
#include "ListenerKeyboard.h"
#include "ListenerMouse.h"
#include "ListenerWindow.h"
#include "ListenerFrame.h"
#include "ListenerTime.h"
#include "ListenerCollision.h"
#include "MeshLoader.h"
#include "GestSceneManager.h"
#include "GestSound.h"
#include "GestShip.h"
#include "GestLaser.h"
#include "GestPlanet.h"
#include "GestGroupAsteroids.h"
#include "ViewportLoader.h"
#include "Menus.h"
#include "PlayerControls.h"
#include "ShipAbstract.h"
#include "ShipIA.h"
#include "ShipPlayer.h"
#include "Planet.h"
#include "Asteroid.h"
#include "GroupAsteroid.h"

class ListenerWindow;
class ListenerMouse;
class ListenerKeyboard;
class ListenerFrame;

class Menus;

//Tingshuo Debut
enum QueryFlags
{
	ANY_QUERY_MASK = 1<<0,
	SHIP_QUERY_MASK = 0x1,
	PLANET_QUERY_MASK = 0x3
};
//Tingshuo Fin

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
		* \brief Listener pour les événements time
		*/
		ListenerTime * listenerTime;
         /*!
		* \brief Listener sur les collisions
		*/
		ListenerCollision * listenerCollision;
        /*!
        * Gere le menus du jeux
        */
        Menus * menus;

        /*!
        * Gere les controles claviers / souris utisable par le joueur
        */
        PlayerControls * player;
        /*!
        * Gere les controles claviers / souris utisable par le joueur
        */
        PlayerControls * player2;
        /*!
        * \brief Gere l'ensemble des planetes
        */
		GestPlanet * gestPlanet;

	public: //TODO : faire des fonctions pour ca

    	/*!
		*  \brief Seuil jusqu'au prochain affichage des stats
		*/
		Ogre::Real timeUntilNextToggle;
    	/*!
		*  \brief Définit si on affiche les stats
		*/
		bool isStatsOn;
    	/*!
		*  \brief Définit si on arrête le jeu
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
		~Application(void);

		/*!
		*  \brief Démarre l'application
		*/
		bool start(void);

        /*!
		* \brief Mise à jour générale
		*/
		void update(void *);
		/*!
		*  \brief Ferme l'application
		*/
		void killApplication();
		/*!
		*  \brief Tue le gestionnaire d'événements
		*/
		void killInputManager(void*);
		
		/*!
		* \brief Mise à jour des stats (FPS, etc...)
		*/
		void updateStats(void *);
		/*!
		* \brief Affiche l'overlay des stats
		*/
		void showDebugOverlay(bool);

    	/*!
		*  \brief Permet de suspendre le jeu
		*/
        void suspendre_jeux();
    	/*!
		*  \brief Permet de redemarrer le jeu
		*/
        void redemarrer_jeux();
    	/*!
		*  \brief Permet de redemarrer sur une scene initiale sans tout recharger
		*/
		void restartScene(void);
		
		
		//Getter/Setter
		
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
         * \brief Reçoit les évènements clavier de PlayerControls (utilisé notamment pour fermer la fenêtre avec échap)
         */
        void onKeyPressed(PlayerControls::Controls key);

};

#endif // __APPLICATION_H__
