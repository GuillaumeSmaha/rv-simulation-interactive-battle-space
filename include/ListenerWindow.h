/*!
 *  \file  ListenerWindow.h
 *  \brief Ce fichier contient la déclaration de la classe ListenerWindow. C'est la classe gérant les événements du clavier.
 */
#ifndef __LISTENER_WINDOW_H__
#define __LISTENER_WINDOW_H__

#include <OgreWindowEventUtilities.h>

/*!
 * \class ListenerWindow
 * \brief Classe permettant de gérer les événements du clavier.
 */
class ListenerWindow : public Ogre::WindowEventListener {
	public:
		/*!
		 * \brief Constructeur
		 */
		ListenerWindow();
		
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
};

#endif //__LISTENER_WINDOW_H__
