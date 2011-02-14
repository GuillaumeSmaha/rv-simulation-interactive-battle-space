#include <Ogre.h>
#include "Asteroid.h"

/*!
*  \file GroupAsteroid.h
*  \brief Ce fichier contient la déclaration de la classe GestAsteroid. C'est la classe qui gère l'ensemble des asteroids
*/

/*!
* \class GroupAsteroid
* \brief Classe gérant l'ensemble des asteroids d'un groupe via un std::vecteur.
* En particulier, on renvoit vers elle les traitements communs à tous les asteroids (mise à jour de la position après une frame par exemple).
*   
*   
*/
class GroupAsteroid
{
    private:
        std::vector<Asteroid *> lstGroupAsteroid;

    public:
        GroupAsteroid();
        ~GroupAsteroid();
        void addAsteroid(Asteroid * asteroid);
        std::vector<Asteroid> getAllGroupAsteroids();
        /*permet de mettre à jour la position de tous les asteroids du groupe
        */
        void updateGroupAsteroids();

        void deleteAllGroupAsteroids();
};
