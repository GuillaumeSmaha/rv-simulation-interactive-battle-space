/*!
 *  \file  CameraFixe.h
 *  \brief Ce fichier contient la déclaration de la classe CameraFixe. C'est la classe gérant une caméra fixe.
 */
#ifndef __CAMERA_FIXE_H__
#define __CAMERA_FIXE_H__

#include "CameraFixeAbstract.h"

/*!
 * \class CameraFixe
 * \brief Classe permettant de gérer une caméra fixe.
 */
class CameraFixe : public CameraFixeAbstract {
	public:
		/*!
		 * \brief Constructeur
		 * \param sceneMgr Pointeur sur le manager de la scène
		 * \param cameraName Nom de la nouvelle caméra
		 * \param nodeInit Position initiale de la caméra
		 */
		CameraFixe(Ogre::SceneManager * sceneMgr, Ogre::String cameraName, Ogre::SceneNode * nodeInit);
		
		/*!
		 * \brief Initialise la position de la caméra
		 */
		void init_camera();
		/*!
		 * \brief Initialise la position de la caméra
		 */
		void update_camera();
};

#endif //__CAMERA_FIXE_H__
