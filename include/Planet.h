/*!
*  \file  Planet.h
*  \brief Ce fichier contient la déclaration de la classe Planet.
*/
#ifndef __PLANET_H__
#define __PLANET_H__

#include <Ogre.h>
#include "MeshLoader.h"
#include "ObjectRoot.h"
#include "Utils.h"


/*!
* \class Planet
* \brief Classe gérant les planètes
*/
class Planet : public ObjectRoot
{
	private:
		/*!
		* \brief Compteur de planètes
		*/
		static int numberOfPlanet;
		
		/*!
		* \brief Sphère interne de la planète (sol)
		*/
		Ogre::Entity * innerSphere;
		/*!
		* \brief Sphère externe (atmosphère, si activée)
		*/
		Ogre::Entity * outerSphere;

		/*!
		* \brief Node de la planète
		*/
		Ogre::SceneNode* planetNode;

		/*!
		* \brief Type de planète qui correspond les modèles de mesh
		*/
		Ogre::int16 type;
		
		/*!
		* \brief L'axe de rotation		
		*/
		// Ogre::Vector3 orbit_axis;
		/*!
		* \brief Angle de rotation
		*/
		//Ogre::Real orbit_radius;
		
		/*!
		* \brief La vitesse de rotation(2 types de vitesse de rotation, entrain de penser)
		//Ogre::Real speed;
		*/

		/*!
		* \brief Indique si la planète possède une atmosphère ou pas
		*/
		bool hasAtmosphere;

		/*!
		* \brief Material du sol
		*/
		Ogre::MaterialPtr mGroundFromSpace;
		/*!
		* \brief Material de l'atmosphère
		*/
		Ogre::MaterialPtr mSkyFromSpace;

		/*!
		* \brief Paramètres du shader "atmosphère"
			voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html
			pour le détail des paramètres =)
		*/
		Ogre::Vector3 mWaveLengths;
		
		///brief Paramètres du shader "atmosphère"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le détail des paramètres =)
		Ogre::Vector3 mInvWaveLengthsPow4;
		///brief Paramètres du shader "atmosphère"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le détail des paramètres =)
		Ogre::Real mInnerRadius;
		///brief Paramètres du shader "atmosphère"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le détail des paramètres =)
		Ogre::Real mInnerRadiusSqr;
		///brief Paramètres du shader "atmosphère"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le détail des paramètres =)
		Ogre::Real mOuterRadius;
		///brief Paramètres du shader "atmosphère"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le détail des paramètres =)
		Ogre::Real mOuterRadiusSqr;
		///brief Paramètres du shader "atmosphère"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le détail des paramètres =)
		Ogre::Real mKr;
		///brief Paramètres du shader "atmosphère"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le détail des paramètres =)
		Ogre::Real mKm;
		///brief Paramètres du shader "atmosphère"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le détail des paramètres =)
		Ogre::Real mKr4PI;
		///brief Paramètres du shader "atmosphère"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le détail des paramètres =)
		Ogre::Real mKm4PI;
		///brief Paramètres du shader "atmosphère"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le détail des paramètres =)
		Ogre::Real mESun;
		///brief Paramètres du shader "atmosphère"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le détail des paramètres =)
		Ogre::Real mKrESun;
		///brief Paramètres du shader "atmosphère"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le détail des paramètres =)
		Ogre::Real mKmESun;
		///brief Paramètres du shader "atmosphère"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le détail des paramètres =)
		Ogre::Real mScale;
		///brief Paramètres du shader "atmosphère"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le détail des paramètres =)
		Ogre::Real mScaleDepth;
		///brief Paramètres du shader "atmosphère"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le détail des paramètres =)
		Ogre::Real mScaleOverScaleDepth;
		///brief Paramètres du shader "atmosphère"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le détail des paramètres =)
		Ogre::Real mDepth;
		///brief Paramètres du shader "atmosphère"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le détail des paramètres =)
		Ogre::Real mG;
		///brief Paramètres du shader "atmosphère"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le détail des paramètres =)
		Ogre::Real mG2;
		///brief Paramètres du shader "atmosphère"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le détail des paramètres =)
		Ogre::Real mExposure;
		
        //rajouté pour les collision avec ogreBullet

	public:
		/*!
		 * \brief Constructeur par défaut de Planet
		 */
		Planet(void);

		/*!
		 * \brief Constructeur d'une planète d'un certain rayon et du type par défaut (Terre).
		 * \param radius Rayon de la planète.
		 * \param hasAtmosphere Indique si la planète possède une atmosphère ou non
		 */
		Planet(Ogre::Real radius, bool hasAtmosphere = false );

		/*!
		 * \brief Constructeur d'une planète d'un certain rayon et d'un certain type.
		 * \param radius Rayon de la planète.
		 * \param type Type de la planète (voir MeshLoader)
		 * \param hasAtmosphere Indique si la planète possède une atmosphère ou non
		 */
		Planet(Ogre::Real radius, Ogre::int16 type, bool hasAtmosphere = false);

		/*!
		 * \brief Destructeur de Planet (sisi)
		 */
		~Planet();

		/*!
		* \brief Envoi des paramètres modifiés aux shaders
		 */
		void update();

		/*!
		* \brief Mise à jour de la position de la planète
		*/
		void updatePosition(void);
		
		
		//Getter/setter
		
		/*!
		* \brief [Setter] Configure la position de planète par rapport au noeud de groupe de planètes
		* \param x Position en X
		* \param y Position en Y
		* \param z Position en Z
		*/
		void setPosition(Ogre::Real x, Ogre::Real y, Ogre::Real z);
		/*!
		* \brief [Setter] Configure le redimmensionnement de planète par rapport au noeud de groupe de planètes
		* \param x Dimension en X
		* \param y Dimension en Y
		* \param z Dimension en Z
		*/
		void setScale(Ogre::Real x, Ogre::Real y, Ogre::Real z);
		
		/*!
		 * \brief [Getter] Radius de la planete
		 * \return radius Rayon de la planète.
		 */
		Ogre::Real getMInnerRadius()
		{
			return this->mInnerRadius;
		}


		/*!
		 * \brief [Getter] Récupère le nom du noeud
		 * \return Nom du noeud
		*/
		Ogre::String getName(void)
		{
			return innerSphere->getName();
		}
		
		/*!
		 * \brief [Getter] Récupère un pointeur sur le noeud content le mesh
		 * \return Nom du noeud
		*/
		Ogre::SceneNode * getNode(void)
		{
			return planetNode;
		}
		
		/*!
		 * \brief [Getter] Récupère un pointeur sur le mesh
		 * \return Nom du noeud
		*/
		Ogre::Entity * getEntity(void)
		{
			return innerSphere;
		}

		/*!
         * \brief Fonction qui permet 'assigner les objets de bullet-ogres (RigidBody...)
        */
        //void createCollisionObject(ListenerCollision * listenerCollision);
	private:

		/*!
		* \brief Permet de créer la/les sphère(s) représentant la planète (2 sphères si atmosphère)
		* \param innerName Nom d'entré
		* \param outerName Nom de sortie
		*/
		void createSpheres(const Ogre::String& innerName, const Ogre::String& outerName = "");


        //void destroyCollisionObject();


		/*!
		* \brief Mise à jour des calculs des paramètres du shader
		*/
		void updateCalculations();

		/*!
		* \brief Permet de régler le material à utiliser pour le sol
		*/
		void setMaterialGroundFromSpace(const Ogre::String& name)
		{
			mGroundFromSpace = Ogre::MaterialManager::getSingleton().getByName(name);
			innerSphere->setMaterialName(name);
		}

		/*!
		* \brief Permet de régler le material à utiliser pour l'atmosphère
		*/
		void setMaterialSkyFromSpace(const Ogre::String& name)
		{
			mSkyFromSpace = Ogre::MaterialManager::getSingleton().getByName(name);
			outerSphere->setMaterialName(name);
		}
		
};

#endif // __PLANET_H__
