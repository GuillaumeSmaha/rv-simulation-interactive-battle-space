/*!
*  \file  Planet.h
*  \brief Ce fichier contient la déclaration de la classe Planet.
*/
#ifndef __PLANET_H__
#define __PLANET_H__

#include <Ogre.h>
#include "MeshLoader.h"
#include "Utils.h"

/*!
* \class Planet
* \brief Classe gérant les planètes
*/
class Planet
{
	private:
		static int planetNumber;

		// Sphère interne de la planète (sol)
		Ogre::Entity* innerSphere;
		// Sphère externe (atmosphère, si activée)
		Ogre::Entity* outerSphere;

		// Node de la planète
		Ogre::SceneNode* planetNode;

		//Type de planète qui correspond les modèles de mesh
		Ogre::int16 type;
		
		//L'axe de rotation
		//Ogre::Vector3 orbit_axis;
		
		//Ogre::Real orbit_radius;
		
		//La vitesse de rotation(2 types de vitesse de rotation, entrain de penser)
		//Ogre::Real speed;

		// Indique si la planète possède une atmosphère ou pas
		bool hasAtmosphere;

		// Material du sol
		Ogre::MaterialPtr mGroundFromSpace;
		// Material de l'atmosphère
		Ogre::MaterialPtr mSkyFromSpace;

		// Paramètres du shader "atmosphère"
		// voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html
		// pour le détail des paramètres =)
		Ogre::Vector3 mWaveLengths;
		Ogre::Vector3 mInvWaveLengthsPow4;
		Ogre::Real mInnerRadius;
		Ogre::Real mInnerRadiusSqr;
		Ogre::Real mOuterRadius;
		Ogre::Real mOuterRadiusSqr;
		Ogre::Real mKr;
		Ogre::Real mKm;
		Ogre::Real mKr4PI;
		Ogre::Real mKm4PI;
		Ogre::Real mESun;
		Ogre::Real mKrESun;
		Ogre::Real mKmESun;
		Ogre::Real mScale;
		Ogre::Real mScaleDepth;
		Ogre::Real mScaleOverScaleDepth;
		Ogre::Real mDepth;
		Ogre::Real mG;
		Ogre::Real mG2;
		Ogre::Real mExposure;

		// Permet de créer la/les sphère(s) représentant la planète (2 sphères si atmosphère)
		void createSpheres(const Ogre::String& innerName, const Ogre::String& outerName = "");

		// Mise à jour des calculs des paramètres du shader
		void updateCalculations();

		// Permet de régler le material à utiliser pour le sol
		void setMaterialGroundFromSpace(const Ogre::String& name)
		{
			mGroundFromSpace = Ogre::MaterialManager::getSingleton().getByName(name);
			innerSphere->setMaterialName(name);
		}

		// Permet de régler le material à utiliser pour l'atmosphère
		void setMaterialSkyFromSpace(const Ogre::String& name)
		{
			mSkyFromSpace = Ogre::MaterialManager::getSingleton().getByName(name);
			outerSphere->setMaterialName(name);
		}

		// Mise à jour de la position de la planète
		void updatePosition(void);
		
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
		Planet(Ogre::Real radius, bool hasAtmosphere = false);

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
		~Planet(void);
		
		//Configurer la position de planète par rapport au noeud de groupe de planètes
		void setPosition(Ogre::Real x, Ogre::Real y, Ogre::Real z);
		void setScale(Ogre::Real x, Ogre::Real y, Ogre::Real z);
		
		/*!
		 * \brief Getter du radius de la planete
		 * \return radius Rayon de la planète.
		 */
		Ogre::Real getMInnerRadius();

		// Envoi des paramètres modifiés aux shaders
		void update();

		Ogre::String getName(void)
		{
			return innerSphere->getName();
		}
		
		Ogre::SceneNode * getNode(void)
		{
			return planetNode;
		}
		
		Ogre::Entity * getEntity(void)
		{
			return innerSphere;
		}
		
};

#endif // __PLANET_H__
