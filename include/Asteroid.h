#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include <Ogre.h>
#include "MeshLoader.h"
#include "Utils.h"

/*!
*  \file  Asteroid.h
*  \brief Ce fichier contient la déclaration de la classe Asteroid. C'est la classe qui gère les asteroids individuellements
*/

/*!
* \class Asteroid
* \brief Classe gérant les asteroid individuellements
*   Comporte un attribut Ogre::entity qui correspond à un unique mesh déplacable
*   Comporte également une fonction getNode qui permet de récupèrer le SceneNode de l'objet et donc de le positionner dans le graphe de scene (c'est via celui que l'on récupere la position orientation de l'objet).
*/

class Asteroid
{
	private:
		Ogre::Entity * entity;
		Ogre::Real speed; //vitesse de l'asteroid
		Ogre::Real rotationSpeed; //vitesse de rotation de l'asteroid
		
	public:
		Asteroid(void);
		~Asteroid(void);
		

		//setter et getter de l'orientation du vaisseau
		/*!
		 *  \brief utilisation d'un quaternion plutot que les 4 angles
		 */
        Ogre::Quaternion getOrientation(void);
		void setOrientation(Ogre::Quaternion);
        void setOrientation(Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Real a);
		
		//setter et getter de la vitesse et la vitesse de rotation de l'asteroid
		void setSpeed (Ogre::Real);
		void setRotationSpeed (Ogre::Real);
        Ogre::Real getSpeed(void);
		Ogre::Real getRotationSpeed(void);

        Ogre::Vector3 getPosition(void);
		void setPosition(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z);
		
		void move(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z);
		void move(const Ogre::Vector3 &vec);
		
		void moveRelative(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z);
		void moveRelative(const Ogre::Vector3 &vec);
        
		//update la position en fonction de la position actuelle, de la vitesse et de l'acceleration
		void updatePosition(void);
		
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

#endif // __ASTEROID_H__
