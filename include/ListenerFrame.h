/*!
 *  \file  ListenerFrame.h
 *  \brief Ce fichier contient la déclaration de la classe ListenerFrame. C'est la classe gérant les événements de la mise à jour du rendu.
 */
#ifndef __LISTENER_FRAME_H__
#define __LISTENER_FRAME_H__

#include <iostream>
#include <Ogre.h>
#include <OgreFrameListener.h>
#include <OgreBulletDynamicsRigidBody.h>
#include <Shapes/OgreBulletCollisionsSphereShape.h>
#include "Signal.h"
#include "ObjectRoot.h"
#include "GestSceneManager.h"

/*!
 * \class ListenerFrame
 * \brief Classe permettant de gérer les événements de la mise à jour du rendu.
 */
class ListenerFrame : public ObjectRoot, public Ogre::FrameListener  {
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
         * \brief Dispatche le signal à chaque début d'image. 
         */
        Signal<const Ogre::FrameEvent&> signalFrameStarted;
        /*!
         * \brief Dispatche le signal à chaque fin d'image. 
         */
        Signal<const Ogre::FrameEvent&> signalFrameEnded;
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

		bool frameStarted(const Ogre::FrameEvent& evt);//Tingshuo
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
//		//Tingshuo Debut
//		OgreBulletDynamics::RigidBody* addSphere(const Ogre::Entity *entity, Ogre::SceneNode *node, const Ogre::Vector3 &pos, const Ogre::Quaternion &q, const Ogre::Real radius, 
//			const Ogre::Real bodyRestitution, const Ogre::Real bodyFriction, const Ogre::Real bodyMass);
//		//Tingshuo Fin
};

#endif //__LISTENER_FRAME_H__


