#ifndef __SHIP_H__
#define __SHIP_H__

#include <Ogre.h>
#include "MeshLoader.h"
#include "Utils.h"


class Ship
{
	private:
		Ogre::Entity * entity;
		int shipLife;
		Ogre::Real wAngleShip;
		Ogre::Real xAngleShip;
		Ogre::Real yAngleShip;
		Ogre::Real zAngleShip;
		Ogre::Real speed;
		Ogre::Real acceleration;
		
	public:
		Ship(void);
		~Ship(void);
		
		void setShipLife(int);
		int getShipLife();

		void setXShip (Ogre::Real);
		void setYShip (Ogre::Real);
		void setZShip (Ogre::Real);
        Ogre::Vector3 getPosition();

		void setWAngleShip(Ogre::Real);
		void setXAngleShip(Ogre::Real);
		void setYAngleShip(Ogre::Real);
		void setZAngleShip(Ogre::Real);
		Ogre::Real getWAngleShip();
		Ogre::Real getXAngleShip();
		Ogre::Real getYAngleShip();
		Ogre::Real getZAngleShip();

		void setOrient(Ogre::Quaternion);
		Ogre::Quaternion getOrient();

		void setPosition(Ogre::Real x, Ogre::Real y, Ogre::Real z);
		
		void setSpeed (Ogre::Real);
		void setAcceleration (Ogre::Real);
		void updatePosition();
        Ogre::Real getSpeed();
		Ogre::Real getAcceleration();
        
		Ogre::String getName(void)
		{
			return entity->getName();
		}
		
		Ogre::SceneNode * getNode(void)
		{
			return this->entity->getParentSceneNode();
		}
		
		Ogre::Entity * getEntity(void)
		{
			this->getNode();
		}
		
		void touched(void);
};

#endif // __SHIP_H__
