#include <Ogre.h>
#include "Planet.h"

/*!
*  \file GestPlanet.h
*  \brief Ce fichier contient la d�claration de la classe GestPlanet. C'est la classe qui g�re l'ensemble des plan�tes.
*/

/*!
* \class GestPlanet
* \brief Classe g�rant l'ensemble des plan�tes via un std::vecteur.
* En particulier, on renvoit vers elle les traitements communs � tous les plan�tes (mise � jour de la position apr�s une frame si on a besoin apr�s). 
*/

class GestPlanet
{
    private:
        std::vector<Planet *> lstPlanet;

    public:
        GestPlanet();
        ~GestPlanet();
        void addPlanet(Planet * planet);
        std::vector<Planet> getAllPlanet();
        void updatePlanet();
        void deleteAllPlanet();
};
