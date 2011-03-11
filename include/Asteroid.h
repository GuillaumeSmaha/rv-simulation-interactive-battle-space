/*!
*  \file  Asteroid.h
*  \brief Ce fichier contient la déclaration de la classe Asteroid. C'est la classe qui gère les asteroids individuellements
*/
#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include <Ogre.h>
#include "MeshLoader.h"
#include "ObjectRoot.h"
#include "Utils.h"


/*!
* \class Asteroid
* \brief Classe gérant les asteroid individuellements
*   Comporte un attribut Ogre::entity qui correspond à un unique mesh déplacable
*   Comporte également une fonction getNode qui permet de récupèrer le SceneNode de l'objet et donc de le positionner dans le graphe de scene (c'est via celui que l'on récupere la position orientation de l'objet).
*/

class Asteroid : public ObjectRoot
{
	private:
		/*!
		 * \brief Entité du mesh de l'asteroid
		*/
		Ogre::Entity * entity;
		/*!
		 * \brief Entité du mesh de l'asteroid
		*/
		Ogre::Entity * entitySmall;
		/*!
		 * \brief Vitesse de l'asteroid
		 */
		Ogre::Real speed;
		/*!
		 * \brief vitesse de rotation de l'asteroid
		 */
		Ogre::Real rotationSpeed;


	public:
		/*!
		 * \brief Construction
		*/
		Asteroid(void);
		/*!
		 * \brief Destructeur
		*/
		~Asteroid(void);
		/*!
		 * \brief Getter de l'orientation de l'asteroid (utilisation d'un quaternion plutot que les 4 angles)
		 */
        Ogre::Quaternion getOrientation(void);
		/*!
		 * \brief Setter de l'orientation de l'asteroid (utilisation d'un quaternion plutot que les 4 angles)
		 * \param q quaternion contenant l'angle
		 */
		void setOrientation(Ogre::Quaternion);
		/*!
		 * \brief Setter de l'orientation de l'asteroid (utilisation de 4 real)
		 * \param x Orientation de l'objet sur l'axe x
		 * \param y Orientation de l'objet sur l'axe y
		 * \param z Orientation de l'objet sur l'axe z
		 * \param a Orientation
		*/
        void setOrientation(Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Real a);
		/*!
		 * \brief Setter de la vitesse de l'asteroid
		 * \param speed vitesse de l'asteroid
		 */
		void setSpeed (Ogre::Real);
		/*!
		 * \brief Setter de la vitesse de rotation l'asteroid
		 * \param rotationSpeed vitesse de rotation
		 */
		void setRotationSpeed (Ogre::Real);
		/*!
		 *  \brief Getter de la vitesse de l'asteroid
		 */
        Ogre::Real getSpeed(void);
		/*!
		 * \brief Getter de la vitesse de rotation l'asteroid
		 */
		Ogre::Real getRotationSpeed(void);
		/*!
		 * \brief Getter de la position de l'asteroid
		 */
        Ogre::Vector3 getPosition(void);
		/*!
		 * \brief Setter de la position de l'asteroid
		 * \param x coordonnée en x
		 * \param y coordonnée en y
		 * \param z coordonnée en z
		*/
		void setPosition(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z);
		/*!
		 * \brief Déplacement l'objet dans le référentiel du monde
		 * \param x Déplacement de l'objet en x
		 * \param y Déplacement de l'objet en y
		 * \param z Déplacement de l'objet en z
		*/
		void move(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z);
		/*!
		 * \brief Déplacement l'objet dans le référentiel du monde
		 * \param vec Déplacement de l'objet selon le vecteur v
		*/
		void move(const Ogre::Vector3 &vec);
		/*!
		 * \brief Déplacement l'objet dans le référentiel de l'objet
		 * \param x Déplacement de l'objet en x
		 * \param y Déplacement de l'objet en y
		 * \param z Déplacement de l'objet en z
		*/
		void moveRelative(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z);
		/*!
		 * \brief Déplacement l'objet dans le référentiel de l'objet
		 * \param vec Déplacement de l'objet selon le vecteur v
		*/
		void moveRelative(const Ogre::Vector3 &vec);
		/*!
         * \brief Rotation autours de l'axe direction de l'objet, permet donc de tourner
         * \param angle un angle en radian
        */
		void rotateRelative(const Ogre::Radian angle);
        /*!
		 *  \brief Update la position en fonction de la position actuelle, de la vitesse et de l'acceleration
		 */
		void updatePosition(void);
        /*!
		 *  \brief Retourne le nom de l'entité
		 */
		Ogre::String getName(void)
		{
			return this->entity->getName();
		}
        /*!
		 *  \brief Retourne le noeud parent de l'entité
		 */
		Ogre::SceneNode * getNode(void)
		{
			return this->entity->getParentSceneNode();
		}
        /*!
		 *  \brief Retourne le noeud de l'entité
		 */
		Ogre::Entity * getEntity(void)
		{
			return this->entity;
		}
};

#endif // __ASTEROID_H__
