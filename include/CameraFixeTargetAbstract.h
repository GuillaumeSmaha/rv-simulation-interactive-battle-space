/*!
 *  \file  CameraFixeTargetAbstract.h
 *  \brief Ce fichier contient la déclaration de la classe CameraFixe. C'est la classe gérant une caméra fixe ciblé sur un noeud.
 */
#ifndef __CAMERA_FIXE_TARGET_ABSTRACT_H__
#define __CAMERA_FIXE_TARGET_ABSTRACT_H__

#include <OgreRoot.h>
#include <OgreCamera.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgrePrerequisites.h>

#include "CameraFixeAbstract.h"

/*!
 * \class CameraFixeTargetAbstract
 * \brief Classe permetttant de gérer une caméra fixe ciblé sur un noeud.
 */
class CameraFixeTargetAbstract : public CameraFixeAbstract {
	public:
		/*!
		 * \brief Constructeur
		 * \param sceneMgr Pointeur sur le manager de la scène
		 * \param cameraName Nom de la nouvelle caméra
		 */
		CameraFixeTargetAbstract(Ogre::SceneManager * sceneMgr, Ogre::String cameraName, Ogre::SceneNode * target);
		/*!
		 * \brief Destructeur virtuel
		 */
		 virtual ~CameraFixeTargetAbstract();
		 
		/*!
		 * \brief Initialise la position de la caméra\n
		 * Méthode virtuelle pure à réimplémenter.
		 */
		virtual void init_camera() = 0;
		
		/*!
		 * \brief Récupère le noeud ciblé par la caméra
		 * \return Le noeud target
		 */
		Ogre::SceneNode * getTarget()
		{
			return this->target;
		}
		
	protected:
		/*!
		 * \brief Le noeud ciblé par la caméra
		 */
		Ogre::SceneNode * target;
};

#endif //__CAMERA_FIXE_TARGET_ABSTRACT_H__
