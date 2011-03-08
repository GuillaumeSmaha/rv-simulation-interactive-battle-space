/*!
 *  \file  ListenerWindow.h
 *  \brief Ce fichier contient la déclaration de la classe ListenerWindow. C'est la classe gérant les événements de la fenêtre.
 */
#ifndef __LISTENER_WINDOW_H__
#define __LISTENER_WINDOW_H__

#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>
#include "Utils.h"
#include "Signal.h"
#include "OISMouse.h"
#include "ListenerMouse.h"


/*!
 * \class ListenerWindow
 * \brief Classe permettant de gérer les événements de la fenêtre.
 */
class ListenerWindow :  public ClassRoot, public Ogre::WindowEventListener
{
	private:
        /*!
		 *  \brief Dispatche un signal lorsque la souris bouge Signal(Ogre::Vector3(X, Y, Z)))
		 */
        Ogre::RenderWindow * renderWindow;
         /*!
		 * \brief Pointeur sur le controleur de la souris
		 */
        ListenerMouse * mouseControl;
		

	public:
		/*!
		 * \brief Dispatche un signal lorsque la fenêtre est fermée Signal(void)
		 */
		Signal<void*> signalWindowClosed;
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
		Ogre::RenderWindow * getRenderWindow()
		{
			return this->renderWindow;
		}
		/*!
		 * \brief [Setter] Définit le pointeur
		 * \return window Le pointeur sur le capteur d'événements de la souris
		 */
		void setMouseControl(ListenerMouse * mouseControl)
		{
			this->mouseControl = mouseControl;
		}
		/*!
		 * \brief [Setter] Définit le pointeur
		 * \return window Le pointeur sur le capteur d'événements de la fenêtre
		 */
		void setRenderWindow(Ogre::RenderWindow * renderWindow)
		{
			this->renderWindow = renderWindow;
		}

		/*!
		 *  \brief Action à effectuer pour l'événement "redimensionnement de la fenêtre"
		 * 	\param rw Fenêtre de rendu
		 */
        void windowResized(Ogre::RenderWindow * rw);
		/*!
		 *  \brief Action à effectuer pour l'événement "fermeture de la fenêtre"
		 * 	\param rw Fenêtre de rendu
		 */
        void windowClosed(Ogre::RenderWindow * rw);
};

#endif //__LISTENER_WINDOW_H__
