/*!
 *  \file  ListenerFrame.h
 *  \brief Ce fichier contient la déclaration de la classe ListenerFrame. C'est la classe gérant les événements de la mise à jour du rendu.
 */
#ifndef __LISTENER_FRAME_H__
#define __LISTENER_FRAME_H__

#include <OgreFrameListener.h>
#include "Signal.h"
#include "ObjectRoot.h"
#include <Ogre.h>
/*!
 * \class ListenerFrame
 * \brief Classe permettant de gérer les événements de la mise à jour du rendu.
 */
class ListenerFrame : public Ogre::FrameListener, public ObjectRoot {
    private :
        /*!
         * \brief Indique si l'application est fermée
         */
         bool closed;
	public:
        /*!
         * \brief Dispatche le signal à chaque image. N'a aucun argument.
         */
        Signal<void*> signalFrameRendering;
        /*!
         * \brief Dispatche le signal à chaque fin d'image. N'a aucun argument.
         */
        Signal<void*> signalFrameEnded;
		/*!
		 * \brief Constructeur
		 */
		ListenerFrame(Ogre::Root * root);
		/*!
		 * \brief Destructeur
		 */
		~ListenerFrame();
		/*!
		 *  \brief Génère la frame de rendu
		 */
        bool frameRenderingQueued(const Ogre::FrameEvent& evt);

		/*!
		*  \brief Comportement après génération de la frame
		*/
		bool frameEnded(const Ogre::FrameEvent& evt);
		/*!
        * \brief Appelée lorsque l'application est fermée
        */
        void shutdown()
        {
            this->shutdown(NULL);
        }
		/*!
        * \brief Appelée lorsque l'application est fermée
        */
        void shutdown(void*);
};

#endif //__LISTENER_FRAME_H__


