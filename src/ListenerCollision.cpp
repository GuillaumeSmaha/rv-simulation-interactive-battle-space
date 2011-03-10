#include "ListenerCollision.h"

ListenerCollision::ListenerCollision(ListenerFrame * listenerFrame)
{	
    //Start Bullet
    mWorld = new OgreBulletDynamics::DynamicsWorld(GestSceneManager::getSceneManager(), Ogre::AxisAlignedBox(Ogre::Vector3 (-1, -1, -1), Ogre::Vector3 (1,  1,  1)), Ogre::Vector3(0,0,0));
    //add Debug info display tool
    debugDrawer = new OgreBulletCollisions::DebugDrawer();
    debugDrawer->setDrawWireframe(false);   // we want to see the Bullet containers
    mWorld->setDebugDrawer(debugDrawer);
    mWorld->setShowDebugShapes(false);      // enable it if you want to see the Bullet containers
    Ogre::SceneNode *node_debugDrawer = GestSceneManager::getSceneManager()->getRootSceneNode()->createChildSceneNode("debugDrawer", Ogre::Vector3::ZERO);
    node_debugDrawer->attachObject(static_cast <Ogre::SimpleRenderable *> (debugDrawer));
    mWorld->getBulletDynamicsWorld()->clearForces();

    listenerFrame->signalFrameStarted.add(&ListenerCollision::updateCollision, this);
    listenerFrame->signalFrameEnded.add(&ListenerCollision::updateCollision, this);

}

ListenerCollision::~ListenerCollision()
{
    delete mWorld->getDebugDrawer();
    mWorld->setDebugDrawer(0);
    delete mWorld;
}

void ListenerCollision::updateCollision(const Ogre::FrameEvent &evt)
{
	//mWorld->stepSimulation(evt.timeSinceLastFrame);   // update Bullet Physics animation
		
	//rayCast
	std::vector<ShipAbstract *> listShips = GestShip::getSingleton()->getAllShips();
    std::vector<ShipAbstract *>::iterator itShip = listShips.begin();
    Ogre::Vector3 intersectionPoint;
    
    for(itShip = listShips.begin() ; itShip < listShips.end() ; itShip++)
	{
		if((*itShip)->getTypeObject() == ObjectRoot::SHIP_PLAYER && !(*itShip)->getIsDead())
		{
			Ogre::Ray rayToFront((*itShip)->getPosition(), (*itShip)->getOrientation()*Ogre::Vector3(0.0, 0.0, 1.0));
			Ogre::Ray rayToLeft((*itShip)->getPosition()+ Ogre::Vector3(0,-50,0), (*itShip)->getOrientation()*Ogre::Vector3(0.0, 1.0, 0.0));
			Ogre::Ray rayToRight((*itShip)->getPosition()+ Ogre::Vector3(0,50,0), (*itShip)->getOrientation()*Ogre::Vector3(0.0, -1.0, 0.0));
			Ogre::Ray rayToUp((*itShip)->getPosition()+ Ogre::Vector3(-50,0,0), (*itShip)->getOrientation()*Ogre::Vector3(1.0, 0.0, 0.0));
			Ogre::Ray rayToDown((*itShip)->getPosition()+ Ogre::Vector3(50,0,0), (*itShip)->getOrientation()*Ogre::Vector3(-1.0, 0.0, 0.0));
			
			OgreBulletCollisions::CollisionClosestRayResultCallback * mCollisionClosestRayResultCallbackFront;
			OgreBulletCollisions::CollisionClosestRayResultCallback * mCollisionClosestRayResultCallbackLeft;
			OgreBulletCollisions::CollisionClosestRayResultCallback * mCollisionClosestRayResultCallbackRight;
			OgreBulletCollisions::CollisionClosestRayResultCallback * mCollisionClosestRayResultCallbackUp;
			OgreBulletCollisions::CollisionClosestRayResultCallback * mCollisionClosestRayResultCallbackDown;
			
			mCollisionClosestRayResultCallbackFront = new OgreBulletCollisions::CollisionClosestRayResultCallback(rayToFront, mWorld, 90.0);
			mCollisionClosestRayResultCallbackLeft = new OgreBulletCollisions::CollisionClosestRayResultCallback(rayToLeft, mWorld, 50.0);
			mCollisionClosestRayResultCallbackRight = new OgreBulletCollisions::CollisionClosestRayResultCallback(rayToRight, mWorld, 50.0);
			mCollisionClosestRayResultCallbackUp = new OgreBulletCollisions::CollisionClosestRayResultCallback(rayToUp, mWorld, 50.0);
			mCollisionClosestRayResultCallbackDown = new OgreBulletCollisions::CollisionClosestRayResultCallback(rayToDown, mWorld, 50.0);

			mWorld->launchRay(*mCollisionClosestRayResultCallbackFront);
			mWorld->launchRay(*mCollisionClosestRayResultCallbackLeft);
			mWorld->launchRay(*mCollisionClosestRayResultCallbackRight);
			mWorld->launchRay(*mCollisionClosestRayResultCallbackUp);
			mWorld->launchRay(*mCollisionClosestRayResultCallbackDown);
			if (mCollisionClosestRayResultCallbackFront->doesCollide () || 
                mCollisionClosestRayResultCallbackLeft->doesCollide() ||
                mCollisionClosestRayResultCallbackRight->doesCollide() ||
                mCollisionClosestRayResultCallbackUp->doesCollide() ||
                mCollisionClosestRayResultCallbackDown->doesCollide()
                )
			{
                
				//OgreBulletDynamics::RigidBody * body = static_cast <OgreBulletDynamics::RigidBody *>(mCollisionClosestRayResultCallbackLeft->getCollidedObject());
				
				//intersectionPoint = mCollisionClosestRayResultCallback->getCollisionPoint();
				(*itShip)->exploded();
				(*itShip)->setSpeed(0);
				(*itShip)->setAcceleration(0);
				(*itShip)->setTranslateSpeed(0);
				(*itShip)->setTranslateAcceleration(0);
				(*itShip)->setRollSpeed(Ogre::Radian(0));
				(*itShip)->setRollAcceleration(Ogre::Radian(0));
				(*itShip)->setPitchSpeed(Ogre::Radian(0));
				(*itShip)->setPitchAcceleration(Ogre::Radian(0));
				(*itShip)->setYawSpeed(Ogre::Radian(0));
				(*itShip)->setYawAcceleration(Ogre::Radian(0));
				
				std::cout << "Hit :"<< std::endl;// body->getName() << std::endl;
				break;
			}
			
			delete mCollisionClosestRayResultCallbackFront;
			delete mCollisionClosestRayResultCallbackLeft;
			delete mCollisionClosestRayResultCallbackRight;
			delete mCollisionClosestRayResultCallbackUp;
			delete mCollisionClosestRayResultCallbackDown;
		}
    }

	//***************************************************************************
	std::vector<Laser *> listLasers = GestLaser::getSingleton()->getAll();
    std::vector<Laser *>::iterator itLaser = listLasers.begin();
    
    for(itLaser = listLasers.begin() ; itLaser < listLasers.end() ; itLaser++)
	{
		Ogre::Ray rayTo((*itLaser)->getPosition(), (*itLaser)->getOrientation()*Ogre::Vector3(0.0, 0.0, 1.0));
		
		OgreBulletCollisions::CollisionClosestRayResultCallback * mCollisionClosestRayResultCallback;
		mCollisionClosestRayResultCallback = new OgreBulletCollisions::CollisionClosestRayResultCallback(rayTo, mWorld, 90.0);

		mWorld->launchRay(*mCollisionClosestRayResultCallback);
		if (mCollisionClosestRayResultCallback->doesCollide ())
		{
			OgreBulletDynamics::RigidBody * body = static_cast <OgreBulletDynamics::RigidBody *>(mCollisionClosestRayResultCallback->getCollidedObject());
			//On regarde si on a toucher un vaiseau
            for(itShip = listShips.begin() ; itShip < listShips.end() ; itShip++)
            {
                if((*itShip)->getRigidBody() == body)
                {
                    (*itShip)->isTouch(10);
                }
            }
            
			intersectionPoint = mCollisionClosestRayResultCallback->getCollisionPoint();
			(*itLaser)->exploded();
			std::cout << "LASER Hit :" << body->getName() << std::endl;
			break;
		}
		
		delete mCollisionClosestRayResultCallback;
    }
}
