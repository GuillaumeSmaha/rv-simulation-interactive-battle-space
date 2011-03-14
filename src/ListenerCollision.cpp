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
		if(!(*itShip)->getIsDead() && (*itShip)->getTypeObject() != ObjectRoot::SHIP_BATTLE_STATION)
		{
			Ogre::Ray rayToFront((*itShip)->getPosition(), (*itShip)->getOrientation()*Ogre::Vector3(0.0, 0.0, 1.0));
			Ogre::Ray rayToLeft((*itShip)->getPosition()+ (*itShip)->getOrientation()*Ogre::Vector3(0.0, 50.0, 0.0), (*itShip)->getOrientation()*Ogre::Vector3(0.0, 1.0, 0.0));
			Ogre::Ray rayToRight((*itShip)->getPosition()+ (*itShip)->getOrientation()*Ogre::Vector3(0.0, -50.0, 0.0), (*itShip)->getOrientation()*Ogre::Vector3(0.0, -1.0, 0.0));
			Ogre::Ray rayToUp((*itShip)->getPosition()+ (*itShip)->getOrientation()*Ogre::Vector3(50.0, 0.0, 0.0), (*itShip)->getOrientation()*Ogre::Vector3(1.0, 0.0, 0.0));
			Ogre::Ray rayToDown((*itShip)->getPosition()+ (*itShip)->getOrientation()*Ogre::Vector3(-50.0, 0.0, 0.0), (*itShip)->getOrientation()*Ogre::Vector3(-1.0, 0.0, 0.0));
			
			OgreBulletCollisions::CollisionClosestRayResultCallback * mCollisionClosestRayResultCallbackFront;
			OgreBulletCollisions::CollisionClosestRayResultCallback * mCollisionClosestRayResultCallbackLeft;
			OgreBulletCollisions::CollisionClosestRayResultCallback * mCollisionClosestRayResultCallbackRight;
			OgreBulletCollisions::CollisionClosestRayResultCallback * mCollisionClosestRayResultCallbackUp;
			OgreBulletCollisions::CollisionClosestRayResultCallback * mCollisionClosestRayResultCallbackDown;
			
			mCollisionClosestRayResultCallbackFront = new OgreBulletCollisions::CollisionClosestRayResultCallback(rayToFront, mWorld, 50*2);
			mCollisionClosestRayResultCallbackLeft = new OgreBulletCollisions::CollisionClosestRayResultCallback(rayToLeft, mWorld, 50);
			mCollisionClosestRayResultCallbackRight = new OgreBulletCollisions::CollisionClosestRayResultCallback(rayToRight, mWorld, 50);
			mCollisionClosestRayResultCallbackUp = new OgreBulletCollisions::CollisionClosestRayResultCallback(rayToUp, mWorld, 50);
			mCollisionClosestRayResultCallbackDown = new OgreBulletCollisions::CollisionClosestRayResultCallback(rayToDown, mWorld, 50);

			mWorld->launchRay(*mCollisionClosestRayResultCallbackFront);
			mWorld->launchRay(*mCollisionClosestRayResultCallbackLeft);
			mWorld->launchRay(*mCollisionClosestRayResultCallbackRight);
			mWorld->launchRay(*mCollisionClosestRayResultCallbackUp);
			mWorld->launchRay(*mCollisionClosestRayResultCallbackDown);
			if (mCollisionClosestRayResultCallbackFront->doesCollide() 
                || mCollisionClosestRayResultCallbackLeft->doesCollide()
                || mCollisionClosestRayResultCallbackRight->doesCollide()
                || mCollisionClosestRayResultCallbackUp->doesCollide()
                || mCollisionClosestRayResultCallbackDown->doesCollide()
                )
			{
				OgreBulletDynamics::RigidBody * body;
				
				if(mCollisionClosestRayResultCallbackFront->doesCollide ())
				{
					body = static_cast <OgreBulletDynamics::RigidBody *>(mCollisionClosestRayResultCallbackFront->getCollidedObject());
					std::cout << "[Front] " << std::ends;
				}
                else if(mCollisionClosestRayResultCallbackLeft->doesCollide())
                {
					body = static_cast <OgreBulletDynamics::RigidBody *>(mCollisionClosestRayResultCallbackLeft->getCollidedObject());
					std::cout << "[Left] " << std::ends;
				}
                else if(mCollisionClosestRayResultCallbackRight->doesCollide())
                {
					body = static_cast <OgreBulletDynamics::RigidBody *>(mCollisionClosestRayResultCallbackRight->getCollidedObject());
					std::cout << "[Right] " << std::ends;
				}
                else if(mCollisionClosestRayResultCallbackUp->doesCollide())
                {
					body = static_cast <OgreBulletDynamics::RigidBody *>(mCollisionClosestRayResultCallbackUp->getCollidedObject());
					std::cout << "[Up] " << std::ends;
				}
                else if(mCollisionClosestRayResultCallbackDown->doesCollide())
                {
					body = static_cast <OgreBulletDynamics::RigidBody *>(mCollisionClosestRayResultCallbackDown->getCollidedObject());
					std::cout << "[Down] " << std::ends;
				}
                
				ObjectRoot * object = ObjectRoot::getObjectWithRigidBody(body);
											

				switch((*itShip)->getTypeObject())
				{
					case ObjectRoot::SHIP_PLAYER :
						std::cout << "ShipPlayer " << std::ends;
						break;
						
					case ObjectRoot::SHIP_IA :
						std::cout << "ShipIA " << std::ends;
						break;
						
					case ObjectRoot::SHIP_BATTLE_STATION :
						std::cout << "ShipBattleStation " << std::ends;
						break;
						
					default:
						break;
				}
								
				switch(object->getTypeObject())
				{
					case ObjectRoot::SHIP_PLAYER :
						std::cout << "Collision Hit ShipPlayer :" << object->getName() << std::endl;
						break;
						
					case ObjectRoot::SHIP_IA :
						std::cout << "Collision Hit ShipIA :" << object->getName() << std::endl;
						break;
						
					case ObjectRoot::SHIP_BATTLE_STATION :
						std::cout << "Collision Hit ShipBattleStation :" << object->getName() << std::endl;
						break;
				
					case ObjectRoot::PLANET :
						std::cout << "Collision Hit Planet :" << object->getName() << std::endl;
						break;
						
					case ObjectRoot::ASTEROID :
						std::cout << "Collision Hit Asteroid :" << object->getName() << std::endl;
						break;
						
					case ObjectRoot::MISSILE :
						std::cout << "Collision Hit Missile :" << object->getName() << std::endl;
						break;
						
					case ObjectRoot::LASER :
						std::cout << "Collision Hit Laser :" << object->getName() << std::endl;
						break;
							
						default:
							break;
				}
				
				switch(object->getTypeObject())
				{						
					case ObjectRoot::SHIP_BATTLE_STATION :
					case ObjectRoot::SHIP_PLAYER :
					{
						ShipAbstract * ship = static_cast<ShipAbstract *>(object);
						ship->isTouch(25);
						break;
					}
					
					case ObjectRoot::SHIP_IA :
					{
						ShipAbstract * ship = static_cast<ShipAbstract *>(object);
						ship->exploded();
						
						break;
					}
					
					/*case ObjectRoot::ASTEROID :
					{
						Asteroid * asteroid = static_cast<Asteroid *>(object);
						asteroid->exploded();
						GestGroupAsteroid::getSingleton()->remShip(asteroid);
						break;
					}*/
						
					default:
						break;
				}
				
				//intersectionPoint = mCollisionClosestRayResultCallback->getCollisionPoint();
				if((*itShip)->getTypeObject() == ObjectRoot::SHIP_PLAYER
					&& ( (object->getTypeObject() == ObjectRoot::SHIP_PLAYER) || (object->getTypeObject() == ObjectRoot::SHIP_IA) ) )
					(*itShip)->isTouch(25);
				else
					(*itShip)->exploded();
				
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
		mCollisionClosestRayResultCallback = new OgreBulletCollisions::CollisionClosestRayResultCallback(rayTo, mWorld, GestLaser::speedLaserBase);

		mWorld->launchRay(*mCollisionClosestRayResultCallback);
		if (mCollisionClosestRayResultCallback->doesCollide ())
		{
			OgreBulletDynamics::RigidBody * body = static_cast <OgreBulletDynamics::RigidBody *>(mCollisionClosestRayResultCallback->getCollidedObject());
			//On regarde si on a toucher un vaiseau
            
			ObjectRoot * object = ObjectRoot::getObjectWithRigidBody(body);
				
			switch(object->getTypeObject())
			{
				case ObjectRoot::SHIP_PLAYER :
					std::cout << "LASER Hit ShipPlayer :" << object->getName() << std::endl;
					break;
					
				case ObjectRoot::SHIP_IA :
					std::cout << "LASER Hit ShipIA :" << object->getName() << std::endl;
					break;
					
				case ObjectRoot::SHIP_BATTLE_STATION :
					std::cout << "LASER Hit ShipBattleStation :" << object->getName() << std::endl;
					break;
				
				case ObjectRoot::PLANET :
					break;
					
				case ObjectRoot::ASTEROID :
					std::cout << "LASER Hit Asteroid :" << object->getName() << std::endl;
					break;
					
				case ObjectRoot::MISSILE :
					std::cout << "LASER Hit Missile :" << object->getName() << std::endl;
					break;
					
				case ObjectRoot::LASER :
					std::cout << "LASER Hit Laser :" << object->getName() << std::endl;
					break;
			}
			
			switch(object->getTypeObject())
			{
				case ObjectRoot::SHIP_PLAYER :
				case ObjectRoot::SHIP_IA :
				case ObjectRoot::SHIP_BATTLE_STATION :
				{
					ShipAbstract * ship = static_cast<ShipAbstract *>(object);
                    ship->isTouch(10);                    
					break;
				}
					
				default:
					break;
			}
            
			//~ intersectionPoint = mCollisionClosestRayResultCallback->getCollisionPoint();
			(*itLaser)->exploded();		
			GestLaser::getSingleton()->remove(*itLaser);				
		}
		
		delete mCollisionClosestRayResultCallback;
    }
}
