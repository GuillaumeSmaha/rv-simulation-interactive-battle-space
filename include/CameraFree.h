/*!
 *  \file  CameraFree.h
 *  \brief Ce fichier contient la déclaration de la classe CameraFree. C'est la classe gérant une caméra fixe.
 */
#ifndef __CAMERA_FREE_H__
#define __CAMERA_FREE_H__

#include "CameraAbstract.h"

/*!
 * \class CameraFree
 * \brief Classe permettant de gérer une caméra fixe.
 */
class CameraFree : public CameraAbstract {
	public:
		/*!
		 * \brief Constructeur
		 * \param sceneMgr Pointeur sur le manager de la scène
		 * \param cameraName Nom de la nouvelle caméra
		 * \param nodeInit Position initiale de la caméra
		 */
		CameraFree(Ogre::SceneManager * sceneMgr, Ogre::String cameraName, Ogre::SceneNode * nodeInit);
		
		/*!
		 * \brief Initialise la position de la caméra
		 */
		void init_camera();
		/*!
		 * \brief Initialise la position de la caméra
		 */
		void update_camera();
};

#endif //__CAMERA_FREE_H__
