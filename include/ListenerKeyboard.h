/*!
 *  \file  ListenerKeyboard.h
 *  \brief Ce fichier contient la déclaration de la classe ListenerKeyboard. C'est la classe gérant les événements du clavier.
 */
#ifndef __LISTENER_KEYBOARD_H__
#define __LISTENER_KEYBOARD_H__

#include <OISKeyboard.h>

/*!
 * \class ListenerKeyboard
 * \brief Classe permettant de gérer les événements du clavier.
 */
class ListenerKeyboard : public OIS::KeyListener {
	public:
		/*!
		 * \brief Constructeur
		 */
		ListenerKeyboard();
		
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
