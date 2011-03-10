/*!
*  \file Laser.h
*  \brief Ce fichier contient la déclaration de la classe Laser. C'est la classe qui gère les lasers
*/
#ifndef __LASER_H__
#define __LASER_H__

#include <Ogre.h>
#include "config.h"
#include "nodeName.h"
#include "Utils.h"
#include "ClassRoot.h"
#include "Signal.h"
#include "GestSceneManager.h"
#include "MeshLoader.h"
#include "GestLaser.h"
#include "ObjectRoot.h"

class GestLaser;

/*!
* \class Laser
* \brief Classe gérant les lasers
*/
class Laser : public ObjectRoot
{	
	private:
         /*!
         * \brief Position initial du laser
         */
		Ogre::Vector3 position;
         /*!
         * \brief Orientation du laser
         */
		Ogre::Quaternion orientation;
         /*!
         * \brief Le timer de vie du laser
         */
        Ogre::Timer * timerLife;
         /*!
         * \brief Objet à dessiner
         */
        Ogre::ParticleSystem * particule;

    public:
		/*!
		 * \brief Constructeur
         * \param position Position initiale du laser
         * \param orientation Orientation du laser
         * \param color La couleur du laser émis
		*/
        Laser(const Ogre::Vector3 &position, const Ogre::Quaternion &orientation, const Ogre::ColourValue &color);
		/*!
		 * \brief Destructeur
		*/
        ~Laser();
        
        /*!
         * \brief Detruit le singleton
         */
        void updatePosition(void);
		
		/*!
		 * \brief Indique si le laser est en vie ou non
		 * \return Vrai s'il est actif
		*/
		bool isAlive();
        
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
		
		
		//Getter/Setter
		
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
		 * \param x Orientation de l'objet sur l'axe x
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
			return this->particule->getParentSceneNode()->getName();
		}
		/*!
		 * \brief [Getter] Récupère un pointeur sur le noeud content le mesh
		 * \return Nom du noeud
		*/
		Ogre::SceneNode * getNode(void)
		{
			return this->particule->getParentSceneNode();
		}
		/*!
		 * \brief [Getter] Récupère un pointeur sur l'entity
		 * \return Nom du noeud
		*/
		Ogre::Entity * getEntity(void)
		{
			//~ return this->particule;
			return NULL;
		}
		/*!
		 * \brief [Getter] Récupère un pointeur sur le particule
		 * \return Nom du noeud
		*/
		Ogre::MovableObject * getMovableObject(void)
		{
			return this->particule;
		}
		/*!
		 * \brief Applique une texture blessé au laser
		*/
		void exploded(void);
};


#endif // __LASER_H__
