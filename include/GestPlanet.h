/*!
*  \file GestPlanet.h
*  \brief Ce fichier contient la déclaration de la classe GestPlanet. C'est la classe qui gère l'ensemble des planètes.
*/
#ifndef __GEST_PLANET_H__
#define __GEST_PLANET_H__

#include <Ogre.h>
#include "Planet.h"
#include "ObjectRoot.h"


/*!
* \class GestPlanet
* \brief Classe gérant l'ensemble des planètes via un std::vecteur.
* En particulier, on renvoit vers elle les traitements communs à tous les planètes (mise à jour de la position après une frame si on a besoin après). 
*/

class GestPlanet : public ObjectRoot
{
    private:
		/*!
		 * \brief Liste des planètes
		 */
        std::vector<Planet *> lstPlanet;

		/*!
		 *  \brief Instance de GestPlanet pour le singleton
		 */
		static GestPlanet * _instance ;

		/*!
		 * \brief Construction
		*/
        GestPlanet();

    public:
		/*!
		 *  \brief Retourne une instance du singleton
		 */
		static GestPlanet * getSingleton(void);

		/*!
         * \brief Detruit le singleton
         */
        static void destroy();

		/*!
		 * \brief Destructeur
		 */
        ~GestPlanet();

		/*!
		 * \brief Ajoute une planète au gestionnaire
		 * \param planet Planète à ajouter
		 */
        void addPlanet(Planet * planet);

		/*!
		 * \brief Récupère la liste des planètes
		 * \return La liste des planètes
		 */
        std::vector<Planet> getAllPlanet();

		/*!
		 * \brief Effectue la mise à jour des planètes
		 */
        void updatePlanet(void *);

		/*!
		 * \brief Supprime les planètes du gestionnaire
		 */
        void deleteAllPlanet();
};

#endif // __GEST_PLANET_H__
