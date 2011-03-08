/*!
*  \file GestShip.h
*  \brief Ce fichier contient la déclaration de la classe GestShip. C'est la classe qui gère l'ensemble des vaiseaux
*/
#ifndef __GEST_SHIP_H__
#define __GEST_SHIP_H__

#include <Ogre.h>
#include "ShipAbstract.h"
#include "ClassRoot.h"
#include "Utils.h"

//class ShipAbstract;

/*!
* \class GestShip
* \brief Classe gérant l'ensemble des vaiseaux via un std::vecteur.
* En particulier, on renvoit vers elle les traitements communs à tous les vaiseaux (mise à jour de la position après une frame par exemple.
*/
class GestShip : public ClassRoot
{
    private:
		/*!
		 * \brief Liste des vaisseaux
		*/
        std::vector<ShipAbstract *> lstShip;

		/*!
		 *  \brief Instance de GestShip pour le singleton
		 */
		static GestShip * _instance ;

		/*!
		 * \brief Construction
		*/
        GestShip();

    public:
		/*!
		 *  \brief Retourne une instance du singleton
		 */
		static GestShip * getSingleton(void);
        /*!
         * \brief Detruit le singleton
         */
        static void destroy();


		/*!
		 * \brief Destructeur
		*/
        ~GestShip();

		/*!
		 * \brief Ajoute un vaisseau au gestionnaire
		 * \param ship Pointeur sur le vaisseau
		*/
        void addShip(ShipAbstract * ship);
        /*!
		 * \brief Supprime un vaisseau du gestionnaire
		 * \param ship Pointeur sur le vaisseau
		*/
        void remShip(ShipAbstract * ship);
		/*!
		 * \brief Récupère la liste des vaisseaux
		 * \return Liste des vaisseaux
		*/
        std::vector<ShipAbstract *> getAllShips()
		{
			return lstShip;
		}
		/*!
		 * \brief Met à jour la position de tous les vaisseaux
		*/
        void updateShips()
        {
            updateShips(NULL);
        }
        /*!
		 * \brief Met à jour la position de tous les vaisseaux
		*/
        void updateShips(void*);
		/*!
		 * \brief Supprime tous les vaisseaux du gestionnaire
		*/
        void deleteAllShips();

		/*!
		 * \brief Pour tous les vaiseaux, les replace à leur position initiale
		*/
        void resetPosAllShips(void);
};


#endif // __GEST_SHIP_H__
