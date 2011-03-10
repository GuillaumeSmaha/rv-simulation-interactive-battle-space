/*!
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
#include <fstream>

/// Valeur de PI : 3.141592653589793
#define PI Ogre::Math::PI

/*!
 * \class Utils
 * \brief A tools class
 */
class Utils
{
	private:
		/*!
		 * \brief Initialize the rand function
		 */
		static int initialize(void);

		/*!
		 * \brief Value of a unique counter
		 */
		static int _count;

		/*!
		 * \brief Chemin du fichier de log
		 */
		static Ogre::String _logFile;
	public:
		/*!
		* \brief Returns an int between min and max (inclusive)
		* \param min lower bound
		* \param max upper bound
		* \return An int between min and max (inclusive)
		*/
		static int randRangeInt(int min, int max);

		/*!
		 * \brief Returns an unique int
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
		* \param Value Valeur à afficher
		*/
		template <typename T>
        static Ogre::String log( const T & Value )
        {
            return Utils::toString<T>(Value);
        }

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
		/*!
		* \brief Affiche un message de log sur la console
		* \param text Texte à afficher
		*/
		static void log(const char* text)
		{
			log(Ogre::String(text));
		}
		/*!
		* \brief Affiche un nombre de log sur la console
		* \param text Nombre à afficher
		*/
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
		* \brief Enregistre un message de log dans le fichier de sortie
		* \param Value Valeur à afficher
		*/
        template <typename T>
        static void logFile( const T & Value )
        {
            Utils::logFile(Utils::toString<T>(Value));
        }
		/*!
		* \brief Transforme une valeur quelconque en une chaine de caractère.
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
		/*!
		* \brief Transforme un nombre en une chaine de caractère.
		* \param Value nombre à chainer
		*/
        static Ogre::String toString( float Value );
		/*!
		* \brief Transforme un entier en une chaine de caractère.
		* \param Value valeur à chainer
		*/
		static Ogre::String toString( int Value );
        /*!
		* \brief Transforme un pointeur d'entier en une chaine de caractère.
		* \param Value valeur à chainer
		*/
		static Ogre::String toString( int * Value );
		/*!
		* \brief Retourne la distance entre deux points
		* \param A: coordonnées de l'objet A
		* \param B: coordonnées de l'objet B
		*/
		static Ogre::Real distance (Ogre::Vector3 A, Ogre::Vector3 B);

        /*!
		* \brief Retourne le contenu d'un fichier sous la forme d'une chaine de caractères
		* \param path Le chemin du fichier à lire
		*/
        static Ogre::String read_file(const char * path)
        {
			return Utils::read_file((char *)path);
		}

        /*!
		* \brief Retourne le contenu d'un fichier sous la forme d'une chaine de caractères
		* \param path Le chemin du fichier à lire
		*/
        static Ogre::String read_file(char * path);

        /*!
		* \brief Retourne le chemin complet d'un fichier contenu dans les ressources d'un groupe défini
		* \param groupName Nom du groupe de la ressource
		* \param filename Nom du fichier
		*/
		static Ogre::String getFullPathRessources(Ogre::String groupName, Ogre::String filename);
        /*!
		* \brief Retourne le chemin complet d'un fichier contenu dans tous les groupes des ressources
		* \param filename Nom du fichier
		*/
		static Ogre::String getFullPathRessources(Ogre::String filename);
        /*!
		* \brief Retourne le chemin complet pour un fichier sonore en fonction du fichier "soundDir.here"
		* \param filename Nom du fichier
		*/
		static Ogre::String getFullPathSound(Ogre::String filename);
		/*!
		* \brief Retourne ou est l'asteroid
		* \param ship Position du vaisseau
		* \param shipFutur Future position du vaisseeau
		* \param asteroid Position de l'astéroide
		* \return angle [0.0,0.4[ gauche; [O.4,0.6] centre; ]0.6, 1.0] droite;
		*/
		static Ogre::Real getAngle(Ogre::Vector3 ship, Ogre::Vector3 shipFutur, Ogre::Vector3 asteroid);
};


#endif // __UTILS_H__
