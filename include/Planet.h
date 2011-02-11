#ifndef __PLANET_H__
#define __PLANET_H__

#include <Ogre.h>
#include "MeshLoader.h"
#include "Utils.h"

class Planet
{
	private:
		Ogre::Entity * entity;
		Ogre::int16 type;
		//Ogre::Vector3 orbit_axis;
		//Ogre::Real orbit_radius;
		//Ogre::Real speed;
		
	public:
		Planet(void);
		Planet(Ogre::int16 type);
		~Planet(void);
		
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
		
};

#endif // __PLANET_H__
