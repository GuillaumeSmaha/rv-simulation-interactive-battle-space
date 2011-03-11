/*!
*  \file  ShipIA.h
*  \brief Ce fichier contient la déclaration de la classe ShipIA. C'est la classe qui gère les vaisseaux automatiques
*/
#ifndef __SHIP_IA_H__
#define __SHIP_IA_H__

#include "ShipAbstract.h"
#include "Utils.h"
/*!
* \class ShipIA
* \brief Classe gérant les vaiseaux automatique
*/
class ShipIA : public ShipAbstract
{
	private:
        int shootDelay;
        /*!
		 * \brief Point de destination (utilisé pour calculé la distance entre le vaisseau et sa destination)
		*/
        Ogre::Vector3 destination;
        /*!
		 * \brief Vitesse du vaisseau
		*/
        Ogre::Real speed;
        /*!
		 * \brief Nombre de frames pour la rotation
		*/
        Ogre::Real mRotFrames;
        /*!
		 * \brief Orientation courante (avant le début de la rotation)
		*/
        Ogre::Quaternion mOrientSrc;
        /*!
		 * \brief Orientation future (après la rotation)
		*/
        Ogre::Quaternion mOrientDest;
        /*!
		 * \brief Avancement de la rotation
		*/
        Ogre::Real mRotProgress;
        /*!
		 * \brief "Pas" pour la rotation
		*/
        Ogre::Real mRotFactor;
        /*!
		 * \brief Vaisseau en rotation ?
		*/
        bool mRotating;
        /*!
         * \brief ID de la cible
         */
         unsigned int target;
	public:
		/*!
		 * \brief Construction
		*/
		ShipIA(void);
		/*!
		 * \brief Destructeur
		*/
		~ShipIA(void);

		/*!
		 *  \brief Update la position en fonction de la position actuelle, de la vitesse et de l'acceleration
		 */
		void updatePosition(void);
};

#endif // __SHIP_IA_H__
