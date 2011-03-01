/*!
*  \file  Planet.h
*  \brief Ce fichier contient la d�claration de la classe Planet.
*/
#ifndef __PLANET_H__
#define __PLANET_H__

#include <Ogre.h>
#include "MeshLoader.h"
#include "Utils.h"

/*!
* \class Planet
* \brief Classe g�rant les plan�tes
*/
class Planet
{
	private:
		static int planetNumber;

		// Sph�re interne de la plan�te (sol)
		Ogre::Entity* innerSphere;
		// Sph�re externe (atmosph�re, si activ�e)
		Ogre::Entity* outerSphere;

		// Node de la plan�te
		Ogre::SceneNode* planetNode;

		//Type de plan�te qui correspond les mod�les de mesh
		Ogre::int16 type;
		
		//L'axe de rotation
		//Ogre::Vector3 orbit_axis;
		
		//Ogre::Real orbit_radius;
		
		//La vitesse de rotation(2 types de vitesse de rotation, entrain de penser)
		//Ogre::Real speed;

		// Indique si la plan�te poss�de une atmosph�re ou pas
		bool hasAtmosphere;

		// Material du sol
		Ogre::MaterialPtr mGroundFromSpace;
		// Material de l'atmosph�re
		Ogre::MaterialPtr mSkyFromSpace;

		// Param�tres du shader "atmosph�re"
		// voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html
		// pour le d�tail des param�tres =)
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

		// Permet de cr�er la/les sph�re(s) repr�sentant la plan�te (2 sph�res si atmosph�re)
		void createSpheres(const Ogre::String& innerName, const Ogre::String& outerName = "");

		// Mise � jour des calculs des param�tres du shader
		void updateCalculations();

		// Permet de r�gler le material � utiliser pour le sol
		void setMaterialGroundFromSpace(const Ogre::String& name)
		{
			mGroundFromSpace = Ogre::MaterialManager::getSingleton().getByName(name);
			innerSphere->setMaterialName(name);
		}

		// Permet de r�gler le material � utiliser pour l'atmosph�re
		void setMaterialSkyFromSpace(const Ogre::String& name)
		{
			mSkyFromSpace = Ogre::MaterialManager::getSingleton().getByName(name);
			outerSphere->setMaterialName(name);
		}

		// Mise � jour de la position de la plan�te
		void updatePosition(void);
		
	public:
		/*!
		 * \brief Constructeur par d�faut de Planet
		 */
		Planet(void);

		/*!
		 * \brief Constructeur d'une plan�te d'un certain rayon et du type par d�faut (Terre).
		 * \param radius Rayon de la plan�te.
		 * \param hasAtmosphere Indique si la plan�te poss�de une atmosph�re ou non
		 */
		Planet(Ogre::Real radius, bool hasAtmosphere = false);

		/*!
		 * \brief Constructeur d'une plan�te d'un certain rayon et d'un certain type.
		 * \param radius Rayon de la plan�te.
		 * \param type Type de la plan�te (voir MeshLoader)
		 * \param hasAtmosphere Indique si la plan�te poss�de une atmosph�re ou non
		 */
		Planet(Ogre::Real radius, Ogre::int16 type, bool hasAtmosphere = false);

		/*!
		 * \brief Destructeur de Planet (sisi)
		 */
		~Planet(void);
		
		//Configurer la position de plan�te par rapport au noeud de groupe de plan�tes
		void setPosition(Ogre::Real x, Ogre::Real y, Ogre::Real z);
		void setScale(Ogre::Real x, Ogre::Real y, Ogre::Real z);
		
		/*!
		 * \brief Getter du radius de la planete
		 * \return radius Rayon de la plan�te.
		 */
		Ogre::Real getMInnerRadius();

		// Envoi des param�tres modifi�s aux shaders
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
