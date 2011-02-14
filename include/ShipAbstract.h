/*!
*  \file  ShipAbstract.h
*  \brief Ce fichier contient la déclaration de la classe Ship. C'est la classe qui gère les vaiseaux individuellements
*/
#ifndef __SHIP_ABSTRACT_H__
#define __SHIP_ABSTRACT_H__

#include <Ogre.h>
#include "MeshLoader.h"
#include "Utils.h"

/*!
* \class ShipAbstract
* \brief Classe gérant les vaiseaux individuellements
*   Comporte un attribut Ogre::entity qui correspond à un unique mesh déplacable
*   Comporte également une fonction getNode qui permet de récupèrer le SceneNode de l'objet et donc de le positionner dans le graphe de scene (c'est via celui que l'on récupere la position orientation de l'objet.
*/

class ShipAbstract
{
	private:
		/*!
		 * \brief Entité du mesh du vaisseau
		*/
		Ogre::Entity * entity;
		/*!
		 * \brief Santé du vaisseau
		*/
		int shipLife;
		/*!
		 * \brief Santé maximim du vaisseau
		*/
		int shipLifeMax;
		/*!
		 * \brief Vitesse du vaisseau
		*/
		Ogre::Real speed;
		/*!
		 * \brief Accélération du vaisseau
		*/
		Ogre::Real acceleration;
		
	public:
		/*!
		 * \brief Construction
		*/
		ShipAbstract(void);
		/*!
		 * \brief Destructeur
		*/
		virtual ~ShipAbstract(void);

        
		/*!
		 * \brief Update la position en fonction de la position actuelle, de la vitesse et de l'acceleration
		 * Méthode virtuelle pure
		*/
		virtual void updatePosition(void) = 0;
		
		void touched(void);
		
		void defineParticules(void);
		
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
		
		
		int getShipLife();
		void setShipLife(int shipLife);
		
		int getShipLifeMax();
		void setShipLifeMax(int shipLifeMax);
		
        Ogre::Real getSpeed(void);
		void setSpeed(const Ogre::Real speed);
		
		Ogre::Real getAcceleration(void);
		void setAcceleration(const Ogre::Real acceleration);

		/*!
		 * \brief [Getter] Récupère l'orientation de l'objet
		 * \return Orientation de l'objet
		*/
        Ogre::Quaternion getOrientation(void);
		/*!
		 * \brief [Setter] Définit l'orientation de l'objet
		 * \param q Orientation de l'objet
		*/
		void setOrientation(const Ogre::Quaternion &q);
		/*!
		 * \brief [Setter] Définit l'orientation de l'objet
		 * \param X Orientation de l'objet sur l'axe x
		 * \param y Orientation de l'objet sur l'axe y
		 * \param z Orientation de l'objet sur l'axe z
		 * \param a Orientation
		*/
        void setOrientation(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z, const Ogre::Real a);
        
		/*!
		 * \brief [Getter] Récupère la position de l'objet
		 * \return Position de l'objet
		*/
        Ogre::Vector3 getPosition(void);
		/*!
		 * \brief [Setter] Définit la position de l'objet
		 * \param v Position de l'objet
		*/
        void setPosition(const Ogre::Vector3 &v);
		/*!
		 * \brief [Setter] Définit la position de l'objet
		 * \param x Position de l'objet en x
		 * \param y Position de l'objet en y
		 * \param z Position de l'objet en z
		*/
		void setPosition(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z);
		
		/*!
		 * \brief [Getter] Récupère le nom du noeud
		 * \return Nom du noeud
		*/
		Ogre::String getName(void)
		{
			return entity->getName();
		}
		/*!
		 * \brief [Getter] Récupère un pointeur sur le noeud content le mesh
		 * \return Nom du noeud
		*/
		Ogre::SceneNode * getNode(void)
		{
			return this->entity->getParentSceneNode();
		}
		/*!
		 * \brief [Getter] Récupère un pointeur sur le mesh
		 * \return Nom du noeud
		*/
		Ogre::Entity * getEntity(void)
		{
			return this->entity;
		}
};

#endif // __SHIP_ABSTRACT_H__
