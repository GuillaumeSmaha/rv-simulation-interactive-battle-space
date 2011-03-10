/*!
*  \file  BattleStation.h
*  \brief Ce fichier contient la déclaration de la classe BattleStation. C'est la classe qui gère la station
*/
#ifndef __BATTLE_STATION_H__
#define __BATTLE_STATION_H__

#include "ShipAbstract.h"
#include "Utils.h"
/*!
* \class BattleStation
* \brief Classe gérant la station spatiale
*/
class BattleStation : public ShipAbstract
{
	private:
        /*!
		 * \brief Point de destination (utilisé pour calculé la distance entre la station et sa destination)
		*/
        Ogre::Vector3 destination;
        /*!
		 * \brief Vitesse de la station
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
		 * \brief Station en rotation ?
		*/
        bool mRotating;
	public:
		/*!
		 * \brief Construction
		*/
		BattleStation(void);
		/*!
		 * \brief Destructeur
		*/
		~BattleStation(void);

		/*!
		 *  \brief Update la position en fonction de la position actuelle, de la vitesse et de l'acceleration
		 */
		void updatePosition(void);
};

#endif // __BATTLE_STATION_H__
