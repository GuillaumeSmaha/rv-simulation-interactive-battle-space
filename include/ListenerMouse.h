/*!
 *  \file  ListenerMouse.h
 *  \brief Ce fichier contient la déclaration de la classe ListenerKeyboard. C'est la classe gérant les événements de la souris.
 */
#ifndef __LISTENER_MOUSE_H__
#define __LISTENER_MOUSE_H__

#include <OISMouse.h>

/*!
 * \class ListenerMouse
 * \brief Classe permettant de gérer les événements de la souris.
 */
class ListenerMouse : public OIS::MouseListener {
	public:
		/*!
		 * \brief Constructeur
		 */
		ListenerMouse();
		
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
