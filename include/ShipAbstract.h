/*!
*  \file  ShipAbstract.h
*  \brief Ce fichier contient la déclaration de la classe Ship. C'est la classe qui gère les vaiseaux individuellements
*/
#ifndef __SHIP_ABSTRACT_H__
#define __SHIP_ABSTRACT_H__

#include <Ogre.h>
#include "CameraFixeTarget.h"
#include "MeshLoader.h"
#include "Utils.h"
#include "Signal.h"
#include "ObjectRoot.h"
/*!
* \class ShipAbstract
* \brief Classe gérant les vaiseaux individuellements
*   Comporte un attribut Ogre::entity qui correspond à un unique mesh déplacable
*   Comporte également une fonction getNode qui permet de récupèrer le SceneNode de l'objet et donc de le positionner dans le graphe de scene (c'est via celui que l'on récupere la position orientation de l'objet.
*/

class ShipAbstract : public ObjectRoot
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
		 * \brief Vitesse de rotation du vaisseau
		*/
		Ogre::Radian rollSpeed;
		/*!
		 * \brief Vitesse de rotation du vaisseau
		*/
		Ogre::Radian pitchSpeed;
		/*!
		 * \brief Accélération du vaisseau
		*/
		Ogre::Real acceleration;
		/*!
         * \brief Accelération de la rotation du vaiseau
        */
        Ogre::Radian rollAcceleration;
       	/*!
         * \brief Accelération de l'inclinaison du vaiseau
        */
        Ogre::Radian pitchAcceleration;

	public:
        /*!
		 * \brief Dispatche un signal lorsque le vaisseau est détruit Signal(ShipAbstract*)
		 */
		 Signal<ShipAbstract*> signalDestruction;
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
		virtual void updatePosition(void);
		/*!
		 * \brief Applique une texture blessé au vaisseau
		*/
		void touched(void);
		/*!
		 * \brief Définit les particules des réacteurs
		*/
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

        /*!
         * \brief Rotation autours de l'axe direction de l'objet, permet donc de tourner
         * \param w un angle en radian
        */
		void rotateRelative(const Ogre::Radian w);

        /*!
         * \brief Permet d'incliner le vaiseau vers le haut (angle positif) ou vers le bas (angle négatif)
         * /param w l'angle d'inclinaison
        */
        void goUp(const Ogre::Radian w);


        /*!
         * \brief Permet d'augmenter diminuer l'accélération en fonction de ce qu'elle était avant
         * \param coefAcceleration Coefficient d'accélération
        */
        void accelerate(const Ogre::Real coefAcceleration);

        /*!
         * \brief Permet d'augmenter diminuer l'accélération de la rotation en fonction de ce qu'elle était avant
         * \param coefAcceleration Coefficient d'accélération
        */
        void pitchAccelerate(const Ogre::Radian coefAcceleration);

        /*!
         * \brief Permet d'augmenter diminuer l'accélération de l'inclinaison en fonction de ce qu'elle était avant
         * \param coefAcceleration Coefficient d'accélération
        */
        void rollAccelerate(const Ogre::Radian coefAcceleration);


        //Getter/Setter

		/*!
		 * \brief [Getter] Récupère la vie du vaisseau
		 * \return Vie du vaisseau
		*/
		int getShipLife()
		{
			return this->shipLife;
		}
		/*!
		 * \brief [Setter] Définit la vie du vaisseau
		 * \param shipLife Vie du vaisseau
		*/
		void setShipLife(int shipLife)
		{
			this->shipLife = shipLife;
		}

		/*!
		 * \brief [Getter] Récupère la vie maximale du vaisseau
		 * \return Vie maximale du vaisseau
		*/
		int getShipLifeMax()
		{
			return this->shipLifeMax;
		}
		/*!
		 * \brief [Setter] Définit la vie maximale du vaisseau
		 * \param shipLifeMax Vie maximale du vaisseau
		*/
		void setShipLifeMax(int shipLifeMax)
		{
			this->shipLifeMax = shipLifeMax;
		}

		/*!
		 * \brief [Getter] Récupère la vitesse du vaisseau
		 * \return Vitesse du vaisseau
		*/
        Ogre::Real getSpeed(void)
		{
			return this->speed;
		}
		/*!
		 * \brief [Setter] Définit la vitesse du vaisseau
		 * \param speed Vitesse du vaisseau
		*/
		void setSpeed(const Ogre::Real speed)
		{
			this->speed = speed;
		}

		/*!
		 * \brief [Getter] Récupère de rotation la vitesse du vaisseau
		 * \return Vitesse de rotation du vaisseau
		*/
        Ogre::Radian getRollSpeed(void)
		{
			return this->rollSpeed;
		}
		/*!
		 * \brief [Setter] Définit la vitesse de rotation du vaisseau
		 * \param rollSpeed Vitesse de rotation du vaisseau
		*/
		void setRollSpeed(const Ogre::Radian rollSpeed)
		{
			this->rollSpeed = rollSpeed;
		}

		/*!
		 * \brief [Getter] Récupère de rotation la vitesse du vaisseau
		 * \return Vitesse de rotation du vaisseau
		*/
        Ogre::Radian getPitchSpeed(void)
		{
			return this->pitchSpeed;
		}
		/*!
		 * \brief [Setter] Définit la vitesse de rotation du vaisseau
		 * \param pitchSpeed Vitesse de rotation du vaisseau
		*/
		void setPitchSpeed(const Ogre::Radian pitchSpeed)
		{
			this->pitchSpeed = pitchSpeed;
		}

		/*!
		 * \brief [Getter] Récupère l'accélération du vaisseau
		 * \return Accélération du vaisseau
		*/
		Ogre::Real getAcceleration(void)
		{
			return this->acceleration;
		}
		/*!
		 * \brief [Setter] Définit l'accélération du vaisseau
		 * \param acceleration Accélération du vaisseau
		*/
		void setAcceleration(const Ogre::Real acceleration)
		{
			this->acceleration = acceleration;
		}

		/*!
		 * \brief [Getter] Récupère l'accélération de rotation du vaisseau
		 * \return Accélération de rotation du vaisseau
		*/
		Ogre::Radian getRollAcceleration(void)
		{
			return this->rollAcceleration;
		}
		/*!
		 * \brief [Setter] Définit l'accélération de rotation du vaisseau
		 * \param rollAcceleration Accélération de rotation du vaisseau
		*/
		void setRollAcceleration(const Ogre::Radian rollAcceleration)
		{
			this->rollAcceleration = rollAcceleration;
		}

		/*!
		 * \brief [Getter] Récupère l'accélération de rotation du vaisseau
		 * \return Accélération de rotation du vaisseau
		*/
		Ogre::Radian getPitchAcceleration(void)
		{
			return this->pitchAcceleration;
		}
		/*!
		 * \brief [Setter] Définit l'accélération de rotation du vaisseau
		 * \param pitchAcceleration Accélération de rotation du vaisseau
		*/
		void setPitchAcceleration(const Ogre::Radian pitchAcceleration)
		{
			this->pitchAcceleration = pitchAcceleration;
		}

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
