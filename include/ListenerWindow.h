/*!
 *  \file  ListenerWindow.h
 *  \brief Ce fichier contient la déclaration de la classe ListenerWindow. C'est la classe gérant les événements de la fenêtre.
 */
#ifndef __LISTENER_WINDOW_H__
#define __LISTENER_WINDOW_H__

#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>
#include "Utils.h"

/*!
 * \class ListenerWindow
 * \brief Classe permettant de gérer les événements de la fenêtre.
 */
class ListenerWindow : public Ogre::WindowEventListener {
	private:
		/*!
		 *  \brief Root
		 */
        Ogre::Root * root;


	public:
        /*!
		 *  \brief Fenêtre de Rendu
		 */
        Ogre::RenderWindow * window;
		/*!
		 * \brief Constructeur
		 */
		ListenerWindow(Ogre::Root * root, Ogre::String nameWindow);
		/*!
		 * \brief Destructeur
		 */
		~ListenerWindow();

		/*!
		 * \brief [Getter] Recupère le pointeur
		 * \return Le pointeur sur le capteur d'événements de la fenêtre
		 */
		Ogre::RenderWindow * getWindow()
		{
			return this->window;
		}
		/*!
		 * \brief [Setter] Recupère le pointeur
		 * \return window Le pointeur sur le capteur d'événements de la fenêtre
		 */
		void setWindow(Ogre::RenderWindow *window)
		{
			this->window = window;
		}

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
