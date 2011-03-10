
/*!
*  \file GestGroupAsteroids.h
*  \brief Ce fichier contient la déclaration de la classe GestGroupAsteroids. C'est la classe qui gère l'ensemble des groupes d'asteroids
*/
#ifndef __GEST_GROUP_ASTEROIDS_H__
#define __GEST_GROUP_ASTEROIDS_H__

#include <Ogre.h>
#include "GroupAsteroid.h"
#include "GestShip.h"
#include "ClassRoot.h"
#include "Utils.h"
#include "ListenerCollision.h"
/*!
* \class GestGroupAsteroids
* \brief Classe gérant l'ensemble des groupes d'asteroids via un std::vecteur.
* En particulier, on renvoit vers elle les traitements communs à tous les groupes asteroids (mise à jour de la position après une frame par exemple).
*/
class GestGroupAsteroids : public ClassRoot
{
    private:
		/*!
		* \brief Liste des groupes d'asteroids
		*/
        std::vector<GroupAsteroid *> lstGroupAsteroids;
        
		/*!
		* \brief Instance du singleton
		*/
        static GestGroupAsteroids * _instance;        
        
       private:
		/*!
		 * \brief Construction
		*/
        GestGroupAsteroids();
        
    public:
		/*!
		 * \brief Récupère le pointeur sur le singleton
		 * \return Instance du singleton
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
		/*!
         * \brief Permet de mettre à jour la position de tous les groupes d'asteroids
         * \param useless NULL
        */
        void updateGroupsAsteroids(void * useless);
		/*!
		 * \brief Supprime tous les groupes d'asteroids du gestionnaire
		*/
        void deleteAllGroupsAsteroids();
		/*!
		 * \brief Crée un groupe d'asteroids
		 * \param nb Nombre d'asteroids de ce groupe (multiple de 4!!!)
		 * \param degreLiberte Degre de liberte autour de l'axe de rotation (distance d'écart tolérée)
		 * \param scale Echelle des asteroids (un random de 10 est ajouté)
		 * \param angleRotation Angle de rotation autour de l'axe
		 * \param rayon Distances des asteroids autour de l'axe
		 * \param planet Noeud de la planète
		 * \param rotationSpeed Vitesse de la rotation
		 * \param listenerCollision Controlleur de collision
		*/
		void createGroup(int nb, int degreLiberte, int scale, Ogre::Radian angleRotation, Ogre::Real rayon, Ogre::SceneNode * planet, Ogre::Real rotationSpeed, ListenerCollision * listenerCollision);
};
#endif // __GEST_GROUP_ASTEROIDS_H__
