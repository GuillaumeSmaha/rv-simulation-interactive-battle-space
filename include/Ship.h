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
		int shipLife; // santé du vaisseau
		Ogre::Real speed; //vitesse du vaisseau
		Ogre::Real acceleration; //acceleration du vaisseau
		
	public:
		Ship(void);
		~Ship(void);
		
		//setter et getter de la vie du vaisseau
		void setShipLife(int);
		int getShipLife();

		//setter et getter de l'orientation du vaisseau
		/*!
		 *  \brief utilisation d'un quaternion plutot que les 4 angles
		 */
        Ogre::Quaternion getOrientation(void);
		void setOrientation(Ogre::Quaternion);
        void setOrientation(Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Real a);
		
		//setter et getter de la vitesse et l'acceleration du vaisseau
		void setSpeed (Ogre::Real);
		void setAcceleration (Ogre::Real);
        Ogre::Real getSpeed(void);
		Ogre::Real getAcceleration(void);

        Ogre::Vector3 getPosition(void);
		void setPosition(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z);
		
		void move(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z);
		void move(const Ogre::Vector3 &vec);
		
		void moveRelative(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z);
		void moveRelative(const Ogre::Vector3 &vec);
        
		//update la position en fonction de la position actuelle, de la vitesse et de l'acceleration
		void updatePosition(void);
		
		void touched(void);
		
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
			return this->entity;
		}
};

#endif // __SHIP_H__
