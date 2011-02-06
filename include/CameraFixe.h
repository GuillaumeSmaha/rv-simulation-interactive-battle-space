/*!
 *  \file  CameraFixe.h
 *  \brief Ce fichier contient la déclaration de la classe CameraFixe. C'est la classe gérant une caméra fixe.
 */
#ifndef __CAMERA_FIXE_H__
#define __CAMERA_FIXE_H__

#include "Camera.h"

/*!
 * \class CameraFixe
 * \brief Classe permetttant de gérer une caméra fixe.
 */
class CameraFixe : public Camera {
	public:
		/*!
		 * \brief Constructeur
		 * \param sceneMgr Pointeur sur le manager de la scène
		 * \param cameraName Nom de la nouvelle caméra
		 */
		CameraFixe(Ogre::SceneManager * sceneMgr, Ogre::String cameraName);
		
		/*!
		 * \brief Initialise la position de la caméra
		 * \return Int
		 */
		int init_camera();
};

#endif //__CAMERA_FIXE_H__
