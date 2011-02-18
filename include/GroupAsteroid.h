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
		/*!
		 * \brief Liste des asteroid du groupe
		 */
        std::vector<Asteroid *> lstGroupAsteroid;
		/*!
		 * \brief Angle de rotation de l'asteroid par rapport au centre
		 */
		Ogre::Quaternion angleRotation;
		/*!
		 * \brief Centre de la rotation
		 */
		Ogre::Vector3 centreRotation;
		/*!
		 * \brief Vitesse de rotation de l'asteroid
		 */
		Ogre::Real rotationSpeed;

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
		 * \brief Setter de l'angle de rotation du groupe d'asteroids
		 * \param angleRotation quaternion contenant l'angle
		 */
		void setAngleRotation(Ogre::Quaternion);
		/*!
		 * \brief Getter de l'angle de rotation du groupe d'asteroids
		 */
		Ogre::Quaternion getAngleRotation(void);
		/*!
		 * \brief Setter du centre de rotation du groupe d'asteroids
		 * \param vec coordonnées du centre de rotation
		 */
		void setCentreRotation(Ogre::Vector3);
		/*!
		 * \brief Getter du centre de rotation du groupe d'asteroids
		 */
		Ogre::Vector3 getCentreRotation(void);
		/*!
		 * \brief Setter de la vitesse de rotation du groupe d'asteroids
		 * \param rotationSpeed vitesse de rotataion
		 */
		void setRotationSpeed(Ogre::Real);
		/*!
		 *  \brief Getter de la vitesse de rotation du groupe d'asteroids
		 */
		Ogre::Real getRotationSpeed(void);
		/*!
		 * \brief Ajoute un asteroid au groupe
		 * \param asteroid Pointeur sur l'asteroid
		*/     
		void addAsteroid(Asteroid * asteroid);
		/*!
		 * \brief Récupère la liste des asteroids du groupe
		 * \return Liste des asteroids du groupe
		*/
        std::vector<Asteroid> getAllGroupAsteroids();
		/*!
		 * \brief Met à jour la position de tous les asteroids du groupe
		*/
        void updateGroupAsteroids();
		/*!
		 * \brief Supprime tous les asteroids du groupe
		*/
        void deleteAllGroupAsteroids();
};
#endif // __GROUPASTEROID_H__
