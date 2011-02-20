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
* \brief Classe gérant l'ensemble des groupes d'asteroids via un std::vecteur.
* En particulier, on renvoit vers elle les traitements communs à tous les groupes asteroids (mise à jour de la position après une frame par exemple).
*
*
*/
class GestGroupAsteroids : public ObjectRoot
{
    private:
		/*!
		* \brief Liste des groupes d'asteroids
		*/
        std::vector<GroupAsteroid *> lstGroupAsteroids;
        GestGroupAsteroids();
        static GestGroupAsteroids * _instance;
    public:
		/*!
		 * \brief Construction
		*/
        static GestGroupAsteroids * getSingleton(void);
		/*!
		 * \brief Destructeur
		*/
        ~GestGroupAsteroids(); 
        /*!
         * \brief Detruit le singleton
         */
        static void destroy();
		/*!
		 * \brief Ajoute un groupe d'asteroids au gestionnaire
		 * \param groupAsteroids Pointeur sur le groupe d'asteroids
		*/    
		void addGroupAsteroids(GroupAsteroid * groupAsteroids);
		/*!
		 * \brief Récupère la liste des groupes d'asteroids du gestionnaire
		 * \return Liste des groupes d'asteroids du gestionnaire
		*/
        std::vector<GroupAsteroid> getAllGroupsAsteroids();
		/*!
		 * \brief Met à jour la position de tous les groupe d'asteroids du gestionnaire
		*/
        void updateGroupsAsteroids()
        {
            updateGroupsAsteroids(NULL);
        }
        /*permet de mettre à jour la position de tous les groupes d'asteroids
        */
        void updateGroupsAsteroids(void*);
		/*!
		 * \brief Supprime tous les groupes d'asteroids du gestionnaire
		*/
        void deleteAllGroupsAsteroids();
		/*!
		 * \brief Crée un groupe d'asteroids
		 * \param nb Nombre d'asteroids de ce groupe (multiple de 4!!!)
		 * \param angleRotation angle de rotation autour de l'axe
		 * \param rayon distances des asteroids autour de l'axe
		 * \param centreRotation coordonnées du centre de la rotation
		 * \param rotationSpeed vitesse de la rotation
		*/
		void createGroup(int nb, Ogre::Radian angleRotation, Ogre::Real rayon, Ogre::Vector3 centreRotation, Ogre::Real rotationSpeed);
};
#endif // __GESTGROUPASTEROIDS_H__
