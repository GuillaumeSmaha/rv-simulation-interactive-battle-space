/*!
*  \file GestSound.h
*  \brief Ce fichier contient la déclaration de la classe GestSound. C'est la classe qui gère le son
*/
#ifndef __GESTSOUND_H__
#define __GESTSOUND_H__

#include <OgreAL.h>
//~ #include <boost/thread/thread.hpp>
//~ #include <boost/thread.hpp>
//~ #include <boost/bind.hpp>
#include "config.h"
#include "ObjectRoot.h"

/*!
* \class GestSound
* \brief Classe gérant le son 3D
*/
class GestSound : public ObjectRoot
{
	public:	
		/// Définit les différents types de son
		enum SoundType
		{
			/// Son Null
			SOUND_NULL = 0,
			/// Son tir
			SOUND_SHOOT = 1
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


#endif // __GESTSOUND_H__
