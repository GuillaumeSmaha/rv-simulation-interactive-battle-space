/*!
 *  \file  ListenerMouse.h
 *  \brief Ce fichier contient la déclaration de la classe ListenerKeyboard. C'est la classe gérant les événements de la souris.
 */
#ifndef __LISTENER_MOUSE_H__
#define __LISTENER_MOUSE_H__

#include <OISInputManager.h>
#include <OISMouse.h>
#include "CameraFixeAbstract.h"
/*!
 * \class ListenerMouse
 * \brief Classe permettant de gérer les événements de la souris.
 */
class ListenerMouse : public OIS::MouseListener {
	private:
		/*!
		 *  \brief Gestionnaire d'événements
		 */
        OIS::InputManager * inputManager;
		/*!
		 *  \brief Capteur d'événements de la souris
		 */
        OIS::Mouse * mouse;
        CameraFixeAbstract * gestCamera;
	public:
		/*!
		 * \brief Constructeur
		 */
		ListenerMouse(OIS::InputManager * inputManager, CameraFixeAbstract * gestCamera);
		/*!
		 * \brief Destructeur
		 */
		~ListenerMouse();

		/*!
		 * \brief Constructeur
		 * \return Le pointeur sur le capteur d'événements de la souris
		 */
		OIS::Mouse * getMouse()
		{
			return this->mouse;
		}
		void capture(void);
		CameraFixeAbstract *  getCamera(void);
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

#endif //__LISTENER_MOUSE_H__
