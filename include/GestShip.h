#include <Ogre.h>
#include "Ship.h"

/*!
*  \file GestShip.h
*  \brief Ce fichier contient la déclaration de la classe GestShip. C'est la classe qui gère l'ensemble des vaiseaux
*/

/*!
* \class GestShip
* \brief Classe gérant l'ensemble des vaiseaux via un std::vecteur.
* En particulier, on renvoit vers elle les traitements communs à tous les vaiseaux (mise à jour de la position après une frame par exemple.
*   
*   
*/
class GestShip
{
    private:
        std::vector<Ship *> lstShip;

    public:
        GestShip();
        ~GestShip();
        void addShip(Ship * ship);
        std::vector<Ship> getAllShips();
        /*permet de mettre à jour la position de tous les vaiseaux
        */
        void updateShips();

        void deleteAllShips();
};
