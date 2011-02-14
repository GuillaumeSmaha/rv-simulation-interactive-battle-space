/*!
*  \file  ShipIA.h
*  \brief Ce fichier contient la déclaration de la classe ShipIA. C'est la classe qui gère les vaisseaux automatiques
*/
#ifndef __SHIP_IA_H__
#define __SHIP_IA_H__

#include "ShipAbstract.h"

/*!
* \class ShipIA
* \brief Classe gérant les vaiseaux automatique
*/
class ShipIA : public ShipAbstract
{
	private:
	
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