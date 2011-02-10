/*!
 *  \file  ListenerFrame.h
 *  \brief Ce fichier contient la déclaration de la classe ListenerFrame. C'est la classe gérant les événements de la mise à jour du rendu.
 */
#ifndef __LISTENER_FRAME_H__
#define __LISTENER_FRAME_H__

#include <OgreFrameListener.h>
#include <ListenerKeyboard.h>
#include <ListenerMouse.h>
#include <Application.h>
class ListenerKeyboard;
class ListenerMouse;
class Application;
/*!
 * \class ListenerFrame
 * \brief Classe permettant de gérer les événements de la mise à jour du rendu.
 */
class ListenerFrame : public Ogre::FrameListener {
    private:
        ListenerKeyboard * keyboard;
        ListenerMouse * mouse;
        Application * app;
	public:
		/*!
		 * \brief Constructeur
		 */
		ListenerFrame(ListenerKeyboard * keyboard, ListenerMouse * mouse, Application * app);
		/*!
		 *  \brief Génère la frame de rendu
		 */
        bool frameRenderingQueued(const Ogre::FrameEvent& evt);
};

#endif //__LISTENER_FRAME_H__


