/*!
*  \file  MeshLoader.h
*  \brief Ce fichier contient la déclaration de la classe MeshLoader. 
*/
#ifndef __MESH_LOADER_H__
#define __MESH_LOADER_H__

#include <Ogre.h>
#include <OgreParticleSystem.h>
#include <sstream>
#include "nodeName.h"
#include "Utils.h"
/*!
 * \class MeshLoader
 *  \brief Définit les différents types de mesh. Crée les entités et les ajoute au graphe de scène
 */
class MeshLoader
{
	public:
		/*!
		 *  \brief Définit les différents types de mesh
		 */
		enum MeshType {
			SHIP = 0,
			POMPIDOU = 2, //peut etre a modifier
			ARLEQUIN = 3,
			SHIP_TOUCHED = 4,
			PLANET = 5,
			PLANET2 = 6,
			PLANET3 = 7,
			PLANET4 = 8,
			PLANET5 = 9,
			PLANET6 = 10,
			PLANET7 = 11,
			PLANET8 = 12,
			PLANET9 = 13,
			ASTEROID = 14
		} ;

	private:
        /*!
		 *  \brief Graphe de scène
		 */
		Ogre::SceneManager * sceneMgr;
		/*!
		 *  \brief Instance de MeshLoader pour le singleton
		 */
		static MeshLoader * _instance ;

	public:
        /*!
		 *  \brief Retourne une instance du singleton
		 */
		static MeshLoader * getSingleton(void);

        /*!
		 * \brief Constructor
		 * \param sceneMgr Scène de graphe
		 */
		MeshLoader(Ogre::SceneManager * sceneMgr);
		/*!
		 * \brief Destructor
		 */
		~MeshLoader(void);
		/*!
		 * \brief Supprime l'instance singleton de MeshLoader
		 * \return Return true si l'instance à a été détruite. false si l'instance n'existait pas ou plus.
		 */
        static bool deleteMeshLoader(void);
        /*!
		 * \brief Retourne un Ogre::Entity correspondant au type de mesh transmis
		 * \param meshType Correspond au mesh à créer
		 * \param random Indique si le mesh doit être créer de manière aléatoire. i.e. pour les planètes et astéroïdes le type est choisi aléatoirement.
		 * \return Une entity correspondante dont le nom est de la forme "object[0-9]+"
		 */
		Ogre::Entity * getEntity(MeshLoader::MeshType meshType, bool random = false)
		{
			return getEntity(meshType, "object"+Utils::toString(Utils::unique()), random);
		}
        /*!
		 * \brief Retourne un Ogre::Entity correspondant au type de mesh transmis
		 * \param meshType Correspond au mesh à créer
         * \param name Nom de l'entity
		 * \param random Indique si le mesh doit être créer de manière aléatoire. i.e. pour les planètes et astéroïdes le type est choisi aléatoirement.
		 * \return Une entity correspondante
		 */
		Ogre::Entity * getEntity(MeshLoader::MeshType meshType, Ogre::String name,  bool random = false);
        /*!
		 * \brief Retourne un Ogre::Entity correspondant au type de mesh transmis et l'insère dans le graphe de scène dans un node placé en fonction du type de mesh
		 * \param meshType Correspond au mesh à créer
		 * \param random Indique si le mesh doit être créer de manière aléatoire. i.e. pour les planètes et astéroïdes le type est choisi aléatoirement.
		 * \return Une entity correspondante dont le nom est de la forme "object[0-9]+" et attachée au node dont le nom est de la forme "node[0-9]+" lui même rattaché au graphe en fonction du type de mesh
		 */
		Ogre::Entity * getNodedEntity(MeshLoader::MeshType meshType, bool random = false)
		{
			return getNodedEntity(meshType, "node"+Utils::toString(Utils::unique()), random);
		}
        /*!
		 * \brief Retourne un Ogre::Entity correspondant au type de mesh transmis et l'insère dans le graphe de scène dans un node placé en fonction du type de mesh
		 * \param meshType Correspond au mesh à créer
         * \param nodeName Nom du node
		 * \param random Indique si le mesh doit être créer de manière aléatoire. i.e. pour les planètes et astéroïdes le type est choisi aléatoirement.
		 * \return Une entity correspondante dont le nom est de la forme "object[0-9]+" et attachée au node dont le nom est celui indiqué lui même rattaché au graphe en fonction du type de mesh
		 */
		Ogre::Entity * getNodedEntity(MeshLoader::MeshType meshType, Ogre::String nodeName, bool random = false)
		{
			return getNodedEntity(meshType, nodeName, "objet"+Utils::toString(Utils::unique()), random);
		}
        /*!
		 * \brief Retourne un Ogre::Entity correspondant au type de mesh transmis et l'insère dans le graphe de scène dans un node placé en fonction du type de mesh
		 * \param meshType Correspond au mesh à créer
         * \param nodeName Nom du node
         * \param meshName Nom de l'entity
		 * \param random Indique si le mesh doit être créer de manière aléatoire. i.e. pour les planètes et astéroïdes le type est choisi aléatoirement.
		 * \return Une entity correspondante dont le nom est passé en paramètre et attachée au node dont le nom est celui indiqué lui même rattaché au graphe en fonction du type de mesh
		 */
		Ogre::Entity * getNodedEntity(MeshLoader::MeshType meshType, Ogre::String nodeName, Ogre::String meshName,  bool random = false);
         /*!
		 * \brief Retourne le graphe de scène
		 * \return Le graphe de scène
         */
		Ogre::SceneManager * getSceneManager()
		{
			return sceneMgr;
		}
        /*!
		 * \brief Permet de modifier le material pour l'affichage d'un mesh
         * \param entity dont on veut changer le material d'affichage
         * \param meshType Correspondant au material
         */
		void setMaterial(Ogre::Entity * entity, MeshLoader::MeshType meshType);
};

#endif // __MESH_LOADER_H__
