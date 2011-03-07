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
#include "GestSceneManager.h"
/*!
 * \class MeshLoader
 *  \brief Définit les différents types de mesh. Crée les entités et les ajoute au graphe de scène
 */
class MeshLoader
{
	public:
		/*!
		 *  \brief Définit les différents types de matériel des mesh
		 */
		enum MeshMaterielType {
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
			ASTEROID = 14,
			MISSILE = 15,
			LASER = 16,
			SHIP_REACTOR = 17
		};

	private:
        /*!
		 *  \brief Graphe de scène
		 */
		Ogre::SceneManager * sceneMgr;
		/*!
		 *  \brief Instance de MeshLoader pour le singleton
		 */
		static MeshLoader * _instance ;
        /*!
		 * \brief Constructor
         */
		MeshLoader();
		
	public:
        /*!
		 *  \brief Retourne une instance du singleton
		 */
		static MeshLoader * getSingleton(void);
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
		 * \brief Retourne un Ogre::MovableObject correspondant au type de mesh transmis
		 * \param meshType Correspond au mesh à créer
		 * \param random Indique si le mesh doit être créer de manière aléatoire. i.e. pour les planètes et astéroïdes le type est choisi aléatoirement.
		 * \return Une object correspondante dont le nom est de la forme "object[0-9]+"
		 */
		Ogre::MovableObject * getMovableObject(MeshLoader::MeshMaterielType meshType, bool random = false)
		{
			return getMovableObject(meshType, "object"+Utils::toString(Utils::unique()), random);
		}
        /*!
		 * \brief Retourne un Ogre::MovableObject correspondant au type de mesh transmis
		 * \param meshType Correspond au mesh à créer
         * \param name Nom de l'object
		 * \param random Indique si le mesh doit être créer de manière aléatoire. i.e. pour les planètes et astéroïdes le type est choisi aléatoirement.
		 * \return Une object correspondante
		 */
		Ogre::MovableObject * getMovableObject(MeshLoader::MeshMaterielType meshType, Ogre::String name,  bool random = false);
        /*!
		 * \brief Retourne un Ogre::MovableObject correspondant au type de mesh transmis et l'insère dans le graphe de scène dans un node placé en fonction du type de mesh
		 * \param meshType Correspond au mesh à créer
		 * \param random Indique si le mesh doit être créer de manière aléatoire. i.e. pour les planètes et astéroïdes le type est choisi aléatoirement.
		 * \return Une object correspondante dont le nom est de la forme "object[0-9]+" et attachée au node dont le nom est de la forme "node[0-9]+" lui même rattaché au graphe en fonction du type de mesh
		 */
		Ogre::MovableObject * getNodedMovableObject(MeshLoader::MeshMaterielType meshType, bool random = false)
		{
			return getNodedMovableObject(meshType, "node"+Utils::toString(Utils::unique()), random);
		}
        /*!
		 * \brief Retourne un Ogre::MovableObject correspondant au type de mesh transmis et l'insère dans le graphe de scène dans un node placé en fonction du type de mesh
		 * \param meshType Correspond au mesh à créer
         * \param nodeName Nom du node
		 * \param random Indique si le mesh doit être créer de manière aléatoire. i.e. pour les planètes et astéroïdes le type est choisi aléatoirement.
		 * \return Une object correspondante dont le nom est de la forme "object[0-9]+" et attachée au node dont le nom est celui indiqué lui même rattaché au graphe en fonction du type de mesh
		 */
		Ogre::MovableObject * getNodedMovableObject(MeshLoader::MeshMaterielType meshType, Ogre::String nodeName, bool random = false)
		{
			return getNodedMovableObject(meshType, nodeName, "objet"+Utils::toString(Utils::unique()), random);
		}
        /*!
		 * \brief Retourne un Ogre::MovableObject correspondant au type de mesh transmis et l'insère dans le graphe de scène dans un node placé en fonction du type de mesh
		 * \param meshType Correspond au mesh à créer
         * \param nodeName Nom du node
         * \param meshName Nom de l'object
		 * \param random Indique si le mesh doit être créer de manière aléatoire. i.e. pour les planètes et astéroïdes le type est choisi aléatoirement.
		 * \return Une object correspondante dont le nom est passé en paramètre et attachée au node dont le nom est celui indiqué lui même rattaché au graphe en fonction du type de mesh
		 */
		Ogre::MovableObject * getNodedMovableObject(MeshLoader::MeshMaterielType meshType, Ogre::String nodeName, Ogre::String meshName,  bool random = false);
		
        /*!
		 * \brief Supprime un noeud et l'entité du noeud
		 * \param type Correspond au mesh à supprimer
		 * \param object Objet/Entité/Particule à supprimer
		 */
		void deleteNodedObject(MeshLoader::MeshMaterielType type, Ogre::MovableObject * object);
         
		/*!
		* \brief Renvoie un simple noeud correspondant à un type de mesh.
		* (Utile pour gérer la création de le MovableObject séparemment pour ensuite l'attacher au noeud correspondant)
		* \param meshType Correspond au mesh à créer
		* \param nodeName Nom du node
		* \return Le nouveau node correspondant au mesh voulu (pour y attacher par la suite l'object)
		*/
		Ogre::SceneNode* getNode(MeshLoader::MeshMaterielType meshType, Ogre::String nodeName);

		/*!
		* \brief Renvoie un simple noeud correspondant à un type de mesh.
		* (Utile pour gérer la création de le MovableObject séparemment pour ensuite l'attacher au noeud correspondant)
		* \param meshType Correspond au mesh à créer
		* \return Le nouveau node correspondant au mesh voulu (pour y attacher par la suite l'object)
		*/
		Ogre::SceneNode* getNode(MeshLoader::MeshMaterielType meshType)
		{
			return getNode(meshType, "node"+Utils::toString(Utils::unique()));
		}
		
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
         * \param object dont on veut changer le material d'affichage
         * \param meshType Correspondant au material
         */
		void setMaterial(Ogre::MovableObject * object, MeshLoader::MeshMaterielType meshType);

		/*!
		* \brief Permet de créer une sphère de manière optimisée
		* \param strName Nom de l'objet à créer (très important pour ensuite récupérer l'object)
		* \param radius Rayon de la sphère à créer
		* \param nRings Nombre d'anneaux de la sphère (128 permet d'avoir une qualité suffisante pour des gros objets)
		* \param nSegments Nombre de segments par anneau (128 est bon aussi)
		*/
		void createSphere(const std::string& strName, const float radius, const int nRings = 64, const int nSegments = 64);
};

#endif // __MESH_LOADER_H__
