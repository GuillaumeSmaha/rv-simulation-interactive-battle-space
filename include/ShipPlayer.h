/*!
*  \file  ShipPlayer.h
*  \brief Ce fichier contient la déclaration de la classe ShipPlayer. C'est la classe qui gère les vaisseaux du joueur
*/
#ifndef __SHIP_PLAYER_H__
#define __SHIP_PLAYER_H__

#include "ShipAbstract.h"
#include "PlayerControls.h"
#include "ObjectRoot.h"

/*!
* \class ShipPlayer
* \brief Classe gérant les vaiseaux du joueur
*   Comporte un attribut Ogre::entity qui correspond à un unique mesh déplacable
*   Comporte également une fonction getNode qui permet de récupèrer le SceneNode de l'objet et donc de le positionner dans le graphe de scene (c'est via celui que l'on récupere la position orientation de l'objet.
*/
class ShipPlayer : public ShipAbstract, public ObjectRoot
{
	public:
		/*!
		 * \brief Construction
		*/
		ShipPlayer(PlayerControls * pControl);
		/*!
		 * \brief Destructeur
		*/
		~ShipPlayer(void);
		
        /*!
         * \brief permet de réagir aux évènement sur le clavier et la souris en utilisant PlayerControls
         */
        void keyPressed(PlayerControls::Controls key);
};

#endif // __SHIP_PLAYER_H__
