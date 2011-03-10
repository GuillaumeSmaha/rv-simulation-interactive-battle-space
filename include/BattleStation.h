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
        Ogre::Vector3 destination;
        Ogre::Real speed;
        Ogre::Quaternion mOrientSrc;               // Initial orientation
          Ogre::Quaternion mOrientDest;              // Destination orientation
          Ogre::Real mRotProgress;                   // How far we've interpolated
          Ogre::Real mRotFactor;                     // Interpolation step
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
