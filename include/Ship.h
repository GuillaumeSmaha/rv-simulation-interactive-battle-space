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
		
	public:
		Ship(void);
		~Ship(void);
		
		void setShipLife(int);
		int getShipLife();

		void setPosition(Ogre::Real x, Ogre::Real y, Ogre::Real z);
		
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
