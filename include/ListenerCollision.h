/*!
 *  \file  ListenerCollision.h
 *  \brief Ce fichier contient la déclaration de la classe ListenerCollision. C'est la classe gérant les collisions. On utilise la librairie OgreBullet
 */
#ifndef __LISTENER_COLLISION_H__
#define __LISTENER_COLLISION_H__
#include <Ogre.h>
//Tingshuo Debut
#include "OgreBulletDynamicsRigidBody.h"
#include "Shapes/OgreBulletCollisionsSphereShape.h"

#include "ObjectRoot.h"
#include "ListenerFrame.h"
class ListenerCollision : public ObjectRoot
{
private :
    OgreBulletDynamics::DynamicsWorld *mWorld;	// OgreBullet World
    OgreBulletCollisions::DebugDrawer *debugDrawer;

public :
    
    ListenerCollision(Ogre::SceneManager * sceneMgr, ListenerFrame * listenerFrame);
    ~ListenerCollision();

    void updateCollision(const Ogre::FrameEvent &evt);

    OgreBulletDynamics::DynamicsWorld * getWorld()
    {
        return mWorld;
    }

};

#endif //__LISTENER_COLLISION_H__

