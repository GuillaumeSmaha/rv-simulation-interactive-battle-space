#include <Ogre.h>
#include "Planet.h"

/*!
*  \file GestPlanet.h
*  \brief Ce fichier contient la déclaration de la classe GestPlanet. C'est la classe qui gère l'ensemble des planètes.
*/

/*!
* \class GestPlanet
* \brief Classe gérant l'ensemble des planètes via un std::vecteur.
* En particulier, on renvoit vers elle les traitements communs à tous les planètes (mise à jour de la position après une frame si on a besoin après). 
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
