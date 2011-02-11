/**
 *  \file  Utils.h
 *  \brief Utilities file
 */
#ifndef __UTILS_H__
#define __UTILS_H__

#include <Ogre.h>
#include <math.h>
#include <time.h>
#include <OgreQuaternion.h>
#include <sstream>
#include <iostream>

/**
 * \class Utils
 * \brief A tools class
 */
class Utils
{
	private:
		/**
		 * Initialize the rand function
		 */
		static int initialize(void);

		/**
		 * Value of a unique counter
		 */
		static int _count;

		/**
		 * Chemin du fichier de log
		 */
		static Ogre::String _logFile;
	public:
		/**
		* Returns an int between min and max (inclusive)
		* \param min lower bound
		* \param max upper bound
		* \return An int between min and max (inclusive)
		*/
		static int randRangeInt(int min, int max);
		/**
		 * Returns an unique int
		 * \return unique int
		 */
		static int unique(void);

		/*!
		* \brief Affiche un message de log sur la console
		* \param text Texte à afficher
		*/
		static void log(Ogre::String text);
		/*!
		* \brief Affiche un message de log sur la console (type générique)
		* \param text Texte à afficher
		*/
		/*$
		template <typename T>
        Ogre::String log( const T & Value )
        {
            return Utils::toString<T>(Value);
        }*/

		/*!
		* \brief Affiche un message de log sur la console
		* \param text Texte à afficher
		*/
		static void log(int text)
		{
		    Utils::log(Utils::toString(text));
		}
		/*!
		* \brief Affiche un message de log sur la console
		* \param text Texte à afficher
		*/
		static void log(int * text)
		{
		    Utils::log(Utils::toString(text));
		}
		/*!
		* \brief Affiche un message de log sur la console
		* \param text Texte à afficher
		*/
		static void log(void * text)
		{
		    Utils::log(Utils::toString(text));
		}
        static void log(float text)
		{
		    Utils::log(Utils::toString(text));
		}

		/*!
		* \brief Initialise le fichier de sortie de log
		* \param file Chemin du fichier
		*/
		static void logFileInit(Ogre::String file);
		/*!
		* \brief Enregistre un message de log dans le fichier de sortie
		* \param text Texte à afficher
		*/
		static void logFile(Ogre::String text);

		/*!
		* \brief Transforme une valeur en une chaine de caractère.
		* \param Value valeur à chainer
		*/
		template <typename T>
       static Ogre::String toString( const T & Value )
        {
            // utiliser un flux de sortie pour créer la chaîne
            std::ostringstream oss;
            // écrire la valeur dans le flux
            oss << Value;
            // renvoyer une string
            return oss.str();
        }
        static Ogre::String toString( float Value)
        {

            // utiliser un flux de sortie pour créer la chaîne
            std::ostringstream oss;
            // écrire la valeur dans le flux
            oss << Value;
            // renvoyer une string
            return oss.str();
        }

		/*!
		* \brief Transforme un entier en une chaine de caractère.
		* \param Value valeur à chainer
		*/
		static Ogre::String toString( int Value);
        /*!
		* \brief Transforme un pointeur d'entier en une chaine de caractère.
		* \param Value valeur à chainer
		*/
		static Ogre::String toString( int * Value)
		{
            return Utils::toString(*Value);
		}
        /*!
		* \brief Transforme un pointeur quelconque en une chaine de caractère (son addresse).
		* \param Value valeur à chainer
		*/
		static Ogre::String toString( void * Value);
};


#endif // __UTILS_H__
