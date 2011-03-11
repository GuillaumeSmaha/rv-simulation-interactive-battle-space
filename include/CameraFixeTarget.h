/*!
 *  \file  CameraFixeTarget.h
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
 * \class CameraFixeTarget
 * \brief Classe permettant de gérer une caméra fixe ciblé sur un noeud.
 */
class CameraFixeTarget : public CameraFixeAbstract {
	private:
		/*!
		 * \brief Le noeud ciblé par la caméra
		 */
		Ogre::SceneNode * nodeTarget;
		/*!
		 * \brief Le noeud position de la caméra
		 */
		Ogre::SceneNode * nodePosition;

		/*!
		 * \brief Système de particules associé à la caméra (vitesse lumière)
		 */
		Ogre::ParticleSystem * lightSpeedSystem;

		Ogre::SceneNode * nodeLightSpeed;
		
	public:
		/*!
		 * \brief Constructeur
		 * \param sceneMgr Pointeur sur le manager de la scène
		 * \param cameraName Nom de la nouvelle caméra
		 * \param nodeTarget Cible noeud à suivre
		 * \param nodePosition Position de la caméra par rapport au noeud
		 */
		CameraFixeTarget(Ogre::SceneManager * sceneMgr, Ogre::String cameraName, Ogre::SceneNode * nodeTarget, Ogre::SceneNode * nodePosition);
		/*!
		 * \brief Destructeur virtuel
		 */
		 virtual ~CameraFixeTarget();
		 
		/*!
		 * \brief Initialise la position de la caméra
		 */
		virtual void init_camera();
		 
		/*!
		 * \brief Met à jour la position de la caméra
		 */
		void update_camera();
		
		//getter/setter
		
		/*!
		 * \brief Récupère le noeud ciblé par la caméra
		 * \return Le noeud target
		 */
		Ogre::SceneNode * getNodeTarget()
		{
			return this->nodeTarget;
		}		
		/*!
		 * \brief Récupère le noeud ciblé par la caméra
		 * \return Le noeud target
		 */
		Ogre::SceneNode * getNodePosition()
		{
			return this->nodePosition;
		}
};

#endif //__CAMERA_FIXE_TARGET_ABSTRACT_H__
