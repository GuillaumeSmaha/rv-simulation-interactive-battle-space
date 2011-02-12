#ifndef __SHIP_H__
#define __SHIP_H__

#include <Ogre.h>
#include "MeshLoader.h"
#include "Utils.h"

/*!
*  \file  Ship.h
*  \brief Ce fichier contient la déclaration de la classe Ship. C'est la classe qui gère les vaiseaux individuellements
*/

/*!
* \class Ship
* \brief Classe gérant les vaiseaux individuellements
*   Comporte un attribut Ogre::entity qui correspond à un unique mesh déplacable
*   Comporte également une fonction getNode qui permet de récupèrer le SceneNode de l'objet et donc de le positionner dans le graphe de scene (c'est via celui que l'on récupere la position orientation de l'objet.
*/

class Ship
{
	private:
		Ogre::Entity * entity;
		int shipLife;
		Ogre::Real speed;
		Ogre::Real acceleration;
		
	public:
		Ship(void);
		~Ship(void);
		
		void setShipLife(int);
		int getShipLife();

        Ogre::Vector3 getPosition();

		void setOrientation(Ogre::Quaternion);
        void setOrientation(Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Real a);
		
        Ogre::Quaternion getOrientation();

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
