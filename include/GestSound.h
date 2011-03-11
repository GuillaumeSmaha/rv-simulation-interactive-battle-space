/*!
*  \file GestSound.h
*  \brief Ce fichier contient la déclaration de la classe GestSound. C'est la classe qui gère le son
*/
#ifndef __GEST_SOUND_H__
#define __GEST_SOUND_H__

#include <OgreAL.h>
#include "config.h"
#include "ClassRoot.h"

/*!
* \class GestSound
* \brief Classe gérant le son 3D
*/
class GestSound : public ClassRoot
{
	public:	
		/// Définit les différents types de son
		enum SoundType
		{
			/// Son Null
			SOUND_NULL = 0,
			/// Son tir
			SOUND_SHOOT = 1,
			/// Son "Retournez vous battre"
			SOUND_TRAITRE = 2,
			/// Son explosion
			SOUND_EXPLOSION = 3,
			/// Son dégats reçu
			SOUND_DEGATS = 4,
			/// Son frolement
			SOUND_FROLE = 5,
			SOUND_FROLEG = 6,
			SOUND_FROLED = 7,
			/// Son intro
			SOUND_INTRO = 8,
			/// Son moteur
			SOUND_MOTEUR = 9,
			/// Son statistique
			SOUND_STATS = 10,
			/// Son Musique de fond
			SOUND_MUSIC = 11
		};
	
	private:
		/*!
		 *  \brief Gestionnaire de son
		 */
		OgreAL::SoundManager * soundManager;

    public:
		/*!
		 * \brief Destructeur
		*/
        ~GestSound();
        /*!
         * \brief Detruit le singleton
         */
        void play(GestSound::SoundType soundType);
        
		/*!
		 *  \brief Retourne une instance du singleton
		 */
		static GestSound * getSingleton(void);
        /*!
         * \brief Detruit le singleton
         */
        static void destroy();
	
    private:
		/*!
		 *  \brief Instance de GestSound pour le singleton
		 */
		static GestSound * _instance ;

		/*!
		 * \brief Construction
		*/
        GestSound();
};


#endif // __GEST_SOUND_H__
