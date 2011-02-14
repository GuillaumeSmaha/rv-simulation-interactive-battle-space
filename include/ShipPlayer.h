/*!
*  \file  ShipPlayer.h
*  \brief Ce fichier contient la déclaration de la classe ShipPlayer. C'est la classe qui gère les vaisseaux du joueur
*/
#ifndef __SHIP_PLAYER_H__
#define __SHIP_PLAYER_H__

#include "ShipAbstract.h"

/*!
* \class ShipPlayer
* \brief Classe gérant les vaiseaux du joueur
*   Comporte un attribut Ogre::entity qui correspond à un unique mesh déplacable
*   Comporte également une fonction getNode qui permet de récupèrer le SceneNode de l'objet et donc de le positionner dans le graphe de scene (c'est via celui que l'on récupere la position orientation de l'objet.
*/
class ShipPlayer : public ShipAbstract
{
	public:
		/*!
		 * \brief Construction
		*/
		ShipPlayer(void);
		/*!
		 * \brief Destructeur
		*/
		~ShipPlayer(void);
		
		/*!
		 *  \brief Update la position en fonction de la position actuelle, de la vitesse et de l'acceleration
		 */
		void updatePosition(void);
};

#endif // __SHIP_PLAYER_H__
