/*!
*  \file GestPlanet.h
*  \brief Ce fichier contient la d�claration de la classe GestPlanet. C'est la classe qui g�re l'ensemble des plan�tes.
*/
#ifndef __GEST_PLANET_H__
#define __GEST_PLANET_H__

#include <Ogre.h>
#include "Planet.h"
#include "ObjectRoot.h"


/*!
* \class GestPlanet
* \brief Classe g�rant l'ensemble des plan�tes via un std::vecteur.
* En particulier, on renvoit vers elle les traitements communs � tous les plan�tes (mise � jour de la position apr�s une frame si on a besoin apr�s). 
*/

class GestPlanet : public ObjectRoot
{
    private:
		/*!
		 * \brief Liste des plan�tes
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
		 * \brief Ajoute une plan�te au gestionnaire
		 * \param planet Plan�te � ajouter
		 */
        void addPlanet(Planet * planet);

		/*!
		 * \brief R�cup�re la liste des plan�tes
		 * \return La liste des plan�tes
		 */
        std::vector<Planet> getAllPlanet();

		/*!
		 * \brief Effectue la mise � jour des plan�tes
		 */
        void updatePlanet(void *);

		/*!
		 * \brief Supprime les plan�tes du gestionnaire
		 */
        void deleteAllPlanet();
};

#endif // __GEST_PLANET_H__
