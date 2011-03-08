/*!
*  \file GestLaser.h
*  \brief Ce fichier contient la déclaration de la classe GestLaser. C'est la classe qui gère les lasers
*/
#ifndef __GEST_LASER_H__
#define __GEST_LASER_H__

#include <Ogre.h>
#include "config.h"
#include "ClassRoot.h"
#include "Utils.h"
#include "Laser.h"


class Laser;

/*!
* \class GestLaser
* \brief Classe gérant les lasers
*/
class GestLaser : public ClassRoot
{
	public:	
		/*!
		 *  \brief Vitesse du laser
		 */
		static Ogre::Real speedLaserBase;
		/*!
		 *  \brief Temps de vie du laser en milliseconde
		 */
		static Ogre::Real timeLife;
	
	private:
		/*!
		 *  \brief Gestionnaire de son
		 */
		std::vector<Laser *> listLasers;

    public:
		/*!
		 * \brief Destructeur
		*/
        ~GestLaser();
        /*!
         * \brief Ajoute un laser
         * \param position Position initiale du laser
         * \param orientation Orientation du laser
         * \param color La couleur du laser émis
         * \return Le laser crée
         */
        Laser * create(const Ogre::Vector3 &position, const Ogre::Quaternion &orientation, const Ogre::ColourValue &color);        
		/*!
		 * \brief Ajoute un laser au gestionnaire
		 * \param laser Pointeur sur le laser
		*/
        void add(Laser * laser);
        /*!
		 * \brief Supprime un laser du gestionnaire
		 * \param laser Pointeur sur le laser
		*/
        void remove(Laser * laser);
        
		/*!
		 * \brief Récupère la liste des vaisseaux
		 * \return Liste des vaisseaux
		*/
        std::vector<Laser *> getAll()
		{
			return listLasers;
		}
		
		/*!
		 * \brief Met à jour la position de tous les lasers
		*/
        void updateLasers()
        {
            updateLasers(NULL);
        }
        /*!
		 * \brief Met à jour la position de tous les lasers
		*/
        void updateLasers(void *);
        
		/*!
		 * \brief Supprime tous les lasers du gestionnaire
		*/
        void deleteAll();
        
		/*!
		 *  \brief Retourne une instance du singleton
		 */
		static GestLaser * getSingleton(void);
        /*!
         * \brief Detruit le singleton
         */
        static void destroy();
	
    private:
		/*!
		 *  \brief Instance de GestLaser pour le singleton
		 */
		static GestLaser * _instance ;

		/*!
		 * \brief Construction
		*/
        GestLaser();
};


#endif // __GEST_LASER_H__
