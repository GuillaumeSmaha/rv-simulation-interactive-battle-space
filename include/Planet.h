/*!
*  \file  Planet.h
*  \brief Ce fichier contient la d�claration de la classe Planet.
*/
#ifndef __PLANET_H__
#define __PLANET_H__

#include <Ogre.h>
#include "MeshLoader.h"
#include "Utils.h"

/*!
* \class Planet
* \brief Classe g�rant les plan�tes
*/
class Planet
{
	private:
		Ogre::Entity * entity;
		//Type de plan�te qui correspond les mod�les de mesh
		Ogre::int16 type;
		
		//L'axe de rotation
		//Ogre::Vector3 orbit_axis;
		
		//Ogre::Real orbit_radius;
		
		//La vitesse de rotation(2 types de vitesse de rotation, entrain de penser)
		//Ogre::Real speed;
		
	public:
		Planet(void);
		Planet(Ogre::int16 type);
		~Planet(void);
		
		//Configurer la position de plan�te par rapport au noeud de groupe de plan�tes
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
