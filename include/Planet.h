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
		/*!
		* \brief Compteur de plan�tes
		*/
		static int planetNumber;

		/*!
		* \brief Sph�re interne de la plan�te (sol)
		*/
		Ogre::Entity * innerSphere;
		/*!
		* \brief Sph�re externe (atmosph�re, si activ�e)
		*/
		Ogre::Entity * outerSphere;

		/*!
		* \brief Node de la plan�te
		*/
		Ogre::SceneNode* planetNode;

		/*!
		* \brief Type de plan�te qui correspond les mod�les de mesh
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
		* \brief Indique si la plan�te poss�de une atmosph�re ou pas
		*/
		bool hasAtmosphere;

		/*!
		* \brief Material du sol
		*/
		Ogre::MaterialPtr mGroundFromSpace;
		/*!
		* \brief Material de l'atmosph�re
		*/
		Ogre::MaterialPtr mSkyFromSpace;

		/*!
		* \brief Param�tres du shader "atmosph�re"
			voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html
			pour le d�tail des param�tres =)
		*/
		Ogre::Vector3 mWaveLengths;
		
		///brief Param�tres du shader "atmosph�re"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le d�tail des param�tres =)
		Ogre::Vector3 mInvWaveLengthsPow4;
		///brief Param�tres du shader "atmosph�re"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le d�tail des param�tres =)
		Ogre::Real mInnerRadius;
		///brief Param�tres du shader "atmosph�re"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le d�tail des param�tres =)
		Ogre::Real mInnerRadiusSqr;
		///brief Param�tres du shader "atmosph�re"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le d�tail des param�tres =)
		Ogre::Real mOuterRadius;
		///brief Param�tres du shader "atmosph�re"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le d�tail des param�tres =)
		Ogre::Real mOuterRadiusSqr;
		///brief Param�tres du shader "atmosph�re"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le d�tail des param�tres =)
		Ogre::Real mKr;
		///brief Param�tres du shader "atmosph�re"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le d�tail des param�tres =)
		Ogre::Real mKm;
		///brief Param�tres du shader "atmosph�re"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le d�tail des param�tres =)
		Ogre::Real mKr4PI;
		///brief Param�tres du shader "atmosph�re"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le d�tail des param�tres =)
		Ogre::Real mKm4PI;
		///brief Param�tres du shader "atmosph�re"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le d�tail des param�tres =)
		Ogre::Real mESun;
		///brief Param�tres du shader "atmosph�re"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le d�tail des param�tres =)
		Ogre::Real mKrESun;
		///brief Param�tres du shader "atmosph�re"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le d�tail des param�tres =)
		Ogre::Real mKmESun;
		///brief Param�tres du shader "atmosph�re"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le d�tail des param�tres =)
		Ogre::Real mScale;
		///brief Param�tres du shader "atmosph�re"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le d�tail des param�tres =)
		Ogre::Real mScaleDepth;
		///brief Param�tres du shader "atmosph�re"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le d�tail des param�tres =)
		Ogre::Real mScaleOverScaleDepth;
		///brief Param�tres du shader "atmosph�re"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le d�tail des param�tres =)
		Ogre::Real mDepth;
		///brief Param�tres du shader "atmosph�re"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le d�tail des param�tres =)
		Ogre::Real mG;
		///brief Param�tres du shader "atmosph�re"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le d�tail des param�tres =)
		Ogre::Real mG2;
		///brief Param�tres du shader "atmosph�re"\n voir http://http.developer.nvidia.com/GPUGems2/gpugems2_chapter16.html\n pour le d�tail des param�tres =)
		Ogre::Real mExposure;
		
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
		~Planet();

		/*!
		* \brief Envoi des param�tres modifi�s aux shaders
		 */
		void update();

		/*!
		* \brief Mise � jour de la position de la plan�te
		*/
		void updatePosition(void);
		
		
		//Getter/setter
		
		/*!
		* \brief [Setter] Configure la position de plan�te par rapport au noeud de groupe de plan�tes
		* \param x Position en X
		* \param y Position en Y
		* \param z Position en Z
		*/
		void setPosition(Ogre::Real x, Ogre::Real y, Ogre::Real z);
		/*!
		* \brief [Setter] Configure le redimmensionnement de plan�te par rapport au noeud de groupe de plan�tes
		* \param x Dimension en X
		* \param y Dimension en Y
		* \param z Dimension en Z
		*/
		void setScale(Ogre::Real x, Ogre::Real y, Ogre::Real z);
		
		/*!
		 * \brief [Getter] Radius de la planete
		 * \return radius Rayon de la plan�te.
		 */
		Ogre::Real getMInnerRadius()
		{
			return this->mInnerRadius;
		}


		/*!
		 * \brief [Getter] R�cup�re le nom du noeud
		 * \return Nom du noeud
		*/
		Ogre::String getName(void)
		{
			return innerSphere->getName();
		}
		
		/*!
		 * \brief [Getter] R�cup�re un pointeur sur le noeud content le mesh
		 * \return Nom du noeud
		*/
		Ogre::SceneNode * getNode(void)
		{
			return planetNode;
		}
		
		/*!
		 * \brief [Getter] R�cup�re un pointeur sur le mesh
		 * \return Nom du noeud
		*/
		Ogre::Entity * getEntity(void)
		{
			return innerSphere;
		}
		
		
	private:

		/*!
		* \brief Permet de cr�er la/les sph�re(s) repr�sentant la plan�te (2 sph�res si atmosph�re)
		* \param innerName Nom d'entr�
		* \param outerName Nom de sortie
		*/
		void createSpheres(const Ogre::String& innerName, const Ogre::String& outerName = "");

		/*!
		* \brief Mise � jour des calculs des param�tres du shader
		*/
		void updateCalculations();

		/*!
		* \brief Permet de r�gler le material � utiliser pour le sol
		*/
		void setMaterialGroundFromSpace(const Ogre::String& name)
		{
			mGroundFromSpace = Ogre::MaterialManager::getSingleton().getByName(name);
			innerSphere->setMaterialName(name);
		}

		/*!
		* \brief Permet de r�gler le material � utiliser pour l'atmosph�re
		*/
		void setMaterialSkyFromSpace(const Ogre::String& name)
		{
			mSkyFromSpace = Ogre::MaterialManager::getSingleton().getByName(name);
			outerSphere->setMaterialName(name);
		}
		
};

#endif // __PLANET_H__
