#ifndef __GROUPASTEROID_H__
#define __GROUPASTEROID_H__

#include <Ogre.h>
#include "Asteroid.h"

/*!
*  \file GroupAsteroid.h
*  \brief Ce fichier contient la déclaration de la classe GestAsteroid. C'est la classe qui gère l'ensemble des asteroids
*/

/*!
* \class GroupAsteroid
* \brief Classe gérant l'ensemble des asteroids d'un groupe via un std::vecteur.
* En particulier, on renvoit vers elle les traitements communs à tous les asteroids (mise à jour de la position après une frame par exemple).
*   
*   
*/
class GroupAsteroid
{
    private:
        std::vector<Asteroid *> lstGroupAsteroid;
		Ogre::Quaternion angleRotation; //angle de rotation de l'asteroid par rapport au centre
		Ogre::Vector3 centreRotation; //centre de la rotation
		Ogre::Real rotationSpeed; //vitesse de rotation de l'asteroid

    public:
        GroupAsteroid();
        ~GroupAsteroid();

		//getter et setter de l'angle de rotation, le centre de rotation et la vitesse de rotation
		void setAngleRotation(Ogre::Quaternion);
		Ogre::Quaternion getAngleRotation(void);
		void setCentreRotation(Ogre::Vector3);
		Ogre::Vector3 getCentreRotation(void);
		void setRotationSpeed(Ogre::Real);
		Ogre::Real getRotationSpeed(void);
        
		void addAsteroid(Asteroid * asteroid);
        std::vector<Asteroid> getAllGroupAsteroids();
        /*permet de mettre à jour la position de tous les asteroids du groupe
        */
        void updateGroupAsteroids();

        void deleteAllGroupAsteroids();
};
#endif // __GROUPASTEROID_H__
