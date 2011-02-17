#ifndef __GESTGROUPASTEROIDS_H__
#define __GESTGROUPASTEROIDS_H__

#include <Ogre.h>
#include "GroupAsteroid.h"
#include "ObjectRoot.h"
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
class GestGroupAsteroids : public ObjectRoot
{
    private:
        std::vector<GroupAsteroid *> lstGroupAsteroids;
        GestGroupAsteroids();
        static GestGroupAsteroids * _instance;
    public:
        static GestGroupAsteroids * getSingleton(void);
        ~GestGroupAsteroids();
        /*!
         * \brief Detruit le singleton
         */
        static void destroy();
        void addGroupAsteroids(GroupAsteroid * groupAsteroids);
        std::vector<GroupAsteroid> getAllGroupsAsteroids();
        /*permet de mettre à jour la position de tous les groupes d'asteroids
        */
        void updateGroupsAsteroids()
        {
            updateGroupsAsteroids(NULL);
        }
        /*permet de mettre à jour la position de tous les groupes d'asteroids
        */
        void updateGroupsAsteroids(void*);

        void deleteAllGroupsAsteroids();
};
#endif // __GESTGROUPASTEROIDS_H__
