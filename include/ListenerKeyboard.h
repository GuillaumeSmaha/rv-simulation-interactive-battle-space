/*!
 *  \file  ListenerKeyboard.h
 *  \brief Ce fichier contient la déclaration de la classe ListenerKeyboard. C'est la classe gérant les événements du clavier.
 */
#ifndef __LISTENER_KEYBOARD_H__
#define __LISTENER_KEYBOARD_H__

#include <OISInputManager.h>
#include <OISKeyboard.h>
#include "ObjectRoot.h"
#include "CameraFixeAbstract.h"
#include "Signal.h"

/*!
 * \class ListenerKeyboard
 * \brief Classe permettant de gérer les événements du clavier.
 */
class ListenerKeyboard : public OIS::KeyListener, public ObjectRoot {
	private:
        /*!
		 *  \brief Gestionnaire d'événements I/O
		 */
        OIS::InputManager * inputManager;
		/*!
		 *  \brief Capteur d'événements du clavier
		 */
        OIS::Keyboard * keyboard;

	public:
        /*!
         * \brief Dispatche un signal lorsqu'une touche du clavier est préssée Signal(const OIS::KeyEvent &evt)
         */
        Signal<const OIS::KeyEvent&> signalKeyPressed;
        /*!
         * \brief Dispatche un signal lorsqu'une touche du clavier est relâchée Signal(const OIS::KeyEvent &evt)
         */
        Signal<const OIS::KeyEvent&> signalKeyReleased;
		/*!
		 * \brief Constructeur
		 */
		ListenerKeyboard(OIS::InputManager * inputManager);
		/*!
		 * \brief Destructeur
		 */
		~ListenerKeyboard();

		/*!
		 * \brief [Getter] Recupère la valeur de keyboard
		 * \return Le pointeur sur le capteur d'événements du clavier
		 */
		OIS::Keyboard * getKeyboard()
		{
			return this->keyboard;
		}

		/*!
		 * \brief Recupère les événements
		 */
		void capture(void);

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
};

#endif //__LISTENER_KEYBOARD_H__
