/*!
*  \file GroupAsteroid.h
*  \brief Ce fichier contient la déclaration de la classe GestAsteroid. C'est la classe qui gère l'ensemble des asteroids
*/
#ifndef __GROUP_ASTEROID_H__
#define __GROUP_ASTEROID_H__

#include <Ogre.h>
#include <math.h>
#include "Asteroid.h"
#include "GestSceneManager.h"
#include "ListenerCollision.h"
#include "ShipPlayer.h"
#include "GestSound.h"

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
		/*!
		 * \brief Liste des asteroid du groupe
		 */
        std::vector<Asteroid *> lstGroupAsteroid;
		/*!
		 * \brief Angle de rotation de l'asteroid par rapport au centre
		 */
		Ogre::Radian angleRotation;
		/*!
		 * \brief Centre de la rotation
		 */
		Ogre::Vector3 centreRotation;
		/*!
		 * \brief Vitesse de rotation de l'asteroid
		 */
		Ogre::Real rotationSpeed;
		/*!
		 * \brief Noeud du groupe
		 */
		Ogre::SceneNode* node;		

    public:
		/*!
		 * \brief Construction
		 */
        GroupAsteroid();
		/*!
		 * \brief Destructeur
		 */
        ~GroupAsteroid();
		/*!
		 * \brief Ajoute un asteroid au groupe
		 * \param asteroid Pointeur sur l'asteroid
		 * \param listenerCollision Controlleur de collision
		*/     
		void addAsteroid(Asteroid * asteroid, ListenerCollision * listenerCollision);
		/*!
         * \brief Rotation autours de l'axe direction de l'objet, permet donc de tourner
         * \param angle Angle en radian
        */
		void rotateRelative(const Ogre::Radian angle);
		/*!
		 * \brief Met à jour la position de tous les asteroids du groupe
		*/
        void updateGroupAsteroids(void);
		/*!
		 * \brief Supprime tous les asteroids du groupe
		*/
        void deleteAllGroupAsteroids(void);
		/*!
		 * \brief Retourne vrai si il y a collision entre l'asteroid passé en parametre et un des asteroids du group
		 * \param asteroid L'asteroid a testé
		 * \return vrai ou faux selon si il y a collision ou non
		*/
		bool isCollided(Asteroid * asteroid);
        
        
        //Getter/setter
        
		/*!
		 * \brief [Getter] Récupère la liste des asteroids du groupe
		 * \return Liste des asteroids du groupe
		*/
        std::vector<Asteroid *> getAllGroupAsteroids();
		/*!
		 * \brief [Setter] Angle de rotation du groupe d'asteroids
		 * \param angleRotation quaternion contenant l'angle
		 */
		void setAngleRotation(Ogre::Radian angleRotation);
		/*!
		 * \brief [Getter] Angle de rotation du groupe d'asteroids
		 */
		Ogre::Radian getAngleRotation(void);
		/*!
		 * \brief [Setter] Centre de rotation du groupe d'asteroids
		 * \param coord Coordonnées du centre de rotation
		 */
		void setCentreRotation(Ogre::Vector3 &coord);
		/*!
		 * \brief [Getter] Centre de rotation du groupe d'asteroids
		 */
		Ogre::Vector3 getCentreRotation(void);
		/*!
		 * \brief [Setter] Vitesse de rotation du groupe d'asteroids
		 * \param rotationSpeed vitesse de rotataion
		 */
		void setRotationSpeed(Ogre::Real rotationSpeed);
		/*!
		 *  \brief [Getter] Vitesse de rotation du groupe d'asteroids
		 */
		Ogre::Real getRotationSpeed(void);
		/*!
		 * \brief [Setter] Définit le noeud du groupe d'astéroides
		 * \param node Le noeud du groupe d'astéroides
		*/
		void setNodeGroupAsteroid(Ogre::SceneNode * node);
		/*!
		 * \brief [Getter] Retourne le noeud du groupe d'astéroides
		 * \return Le noeud du groupe d'astéroides
		*/
        Ogre::SceneNode * getNodeGroupAsteroid(void);
};
#endif // __GROUP_ASTEROID_H__
