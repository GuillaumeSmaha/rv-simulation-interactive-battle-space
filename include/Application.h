/*!
*  \file  Application.h
*  \brief Ce fichier contient la déclaration de la classe Application. C'est la classe qui permet d'initialiser le logiciel en partie en gérant les aspecs graphiques et évènement
*/
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <Ogre.h>
#include <OISInputManager.h>
#include "ListenerFrame.h"
#include "ListenerWindow.h"
#include "ListenerKeyboard.h"
#include "ListenerMouse.h"
#include "nodeName.h"
#include "CameraFixeAbstract.h"
#include "CameraFixe.h"
#include "CameraFirstPerson.h"
#include "CameraExterieureFixe.h"
#include "Ship.h"
#include "Utils.h"
#include "MeshLoader.h"


class ListenerKeyboard;
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
class Application : public Ogre::FrameListener, public Ogre::WindowEventListener {
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
	* \brief GUI pour afficher les stats
	*/
	Ogre::Overlay* debugOverlay;

	/*!
	* \brief Texte utile pour le debug
	*/
	Ogre::String debugText;

	/*!
	*  \brief Capteur d'événements
	*/
	OIS::InputManager * inputManager;

	/*!
	*  \brief Type de la caméra utilisé
	*/
	CameraFixeAbstract::CameraType type_Camera;
	/*!
	*  \brief Pointeur sur la caméra utilisée
	*/
	CameraFixeAbstract * gestCamera;

	/*!
	* \brief Listener pour les evts clavier
	*/
	ListenerKeyboard * listenerKeyboard;

	/* Pour la gestion des stats */
	Ogre::Real timeUntilNextToggle;
	bool isStatsOn;

public: //TODO : faire des fonctions pour ca
	bool shutDown;

	float _translateX;
	float _translateZ;

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
	* \brief Mise à jour des stats (FPS, etc...)
	*/
	void updateStats(void);

	/*!
	* \brief Affiche l'overlay des stats
	*/
	void showDebugOverlay(bool);

	/*!
	*  \brief Génère la frame de rendu
	*/
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	/*!
	*  \brief Comportement à effectuer à la fin de la génération 
	*  de chaque frame
	*/
	bool frameEnded(const Ogre::FrameEvent& evt);

	/*!
	*  \brief Action à effectuer pour l'événement "redimensionnement de la fenêtre"
	*      \param rw Fenêtre de rendu
	*/
	void windowResized(Ogre::RenderWindow* rw);
	
	/*!
	*  \brief Action à effectuer pour l'événement "fermeture de la fenêtre"
	*      \param rw Fenêtre de rendu
	*/
	void windowClosed(Ogre::RenderWindow* rw);
};

#endif // __APPLICATION_H__
