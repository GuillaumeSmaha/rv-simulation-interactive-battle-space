#include "ListenerCollision.h"

ListenerCollision::ListenerCollision(ListenerFrame * listenerFrame)
{	
    //Start Bullet
    mWorld = new OgreBulletDynamics::DynamicsWorld(GestSceneManager::getSceneManager(), Ogre::AxisAlignedBox(Ogre::Vector3 (-1, -1, -1), Ogre::Vector3 (1,  1,  1)), Ogre::Vector3(0,0,0));
    //add Debug info display tool
    debugDrawer = new OgreBulletCollisions::DebugDrawer();
    debugDrawer->setDrawWireframe(true);   // we want to see the Bullet containers
    mWorld->setDebugDrawer(debugDrawer);
    mWorld->setShowDebugShapes(true);      // enable it if you want to see the Bullet containers
    Ogre::SceneNode *node_debugDrawer = GestSceneManager::getSceneManager()->getRootSceneNode()->createChildSceneNode("debugDrawer", Ogre::Vector3::ZERO);
    node_debugDrawer->attachObject(static_cast <Ogre::SimpleRenderable *> (debugDrawer));
    //mWorld->getBulletDynamicsWorld()->clearForces();

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
    
    int i = 0;
    for(itShip = listShips.begin() ; itShip < listShips.end() ; itShip++)
	{
		std::cout << "." << std::ends;
		if((*itShip)->getTypeObject() == ObjectRoot::SHIP_PLAYER)
		{
			Ogre::Ray rayTo((*itShip)->getPosition(), (*itShip)->getOrientation()*Ogre::Vector3(0.0, 0.0, 1.0));
			
			OgreBulletCollisions::CollisionClosestRayResultCallback * mCollisionClosestRayResultCallback;
			mCollisionClosestRayResultCallback = new OgreBulletCollisions::CollisionClosestRayResultCallback(rayTo, mWorld, 90.0);

			mWorld->launchRay(*mCollisionClosestRayResultCallback);
			if (mCollisionClosestRayResultCallback->doesCollide ())
			{
				OgreBulletDynamics::RigidBody * body = static_cast <OgreBulletDynamics::RigidBody *>(mCollisionClosestRayResultCallback->getCollidedObject());
				
				intersectionPoint = mCollisionClosestRayResultCallback->getCollisionPoint();
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
				
				std::cout << "Hit :" << body->getName() << std::endl;
				break;
			}
			
			delete mCollisionClosestRayResultCallback;
			i++;
		}
    }

}
