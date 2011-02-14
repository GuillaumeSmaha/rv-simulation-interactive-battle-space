#include <Ogre.h>
#include "GroupAsteroid.h"

/*!
*  \file GestGroupAsteroids.h
*  \brief Ce fichier contient la déclaration de la classe GestGroupAsteroids. C'est la classe qui gère l'ensemble des groupes d'asteroids
*/

/*!
* \class GestGroupAsteroids
* \brief Classe gérant l'ensemble des groupes asteroids via un std::vecteur.
* En particulier, on renvoit vers elle les traitements communs à tous les groupes asteroids (mise à jour de la position après une frame par exemple).
*   
*   
*/
class GestGroupAsteroids
{
    private:
        std::vector<GroupAsteroid *> lstGroupAsteroids;

    public:
        GestGroupAsteroids();
        ~GestGroupAsteroids();
        void addGroupAsteroids(GroupAsteroid * groupAsteroids);
        std::vector<GroupAsteroid> getAllGroupsAsteroids();
        /*permet de mettre à jour la position de tous les groupes d'asteroids
        */
        void updateGroupsAsteroids();

        void deleteAllGroupsAsteroids();
};
