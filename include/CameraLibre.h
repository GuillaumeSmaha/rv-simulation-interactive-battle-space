/*!
 *  \file  CameraLibre.h
 *  \brief Ce fichier contient la déclaration de la classe CameraLibre. C'est la classe gérant une caméra fixe.
 */
#ifndef __CAMERA_LIBRE_H__
#define __CAMERA_LIBRE_H__

#include "CameraAbstract.h"

/*!
 * \class CameraLibre
 * \brief Classe permettant de gérer une caméra fixe.
 */
class CameraLibre : public CameraAbstract {
	public:
		/*!
		 * \brief Constructeur
		 * \param sceneMgr Pointeur sur le manager de la scène
		 * \param cameraName Nom de la nouvelle caméra
		 * \param nodeInit Position initiale de la caméra
		 */
		CameraLibre(Ogre::SceneManager * sceneMgr, Ogre::String cameraName, Ogre::SceneNode * nodeInit);
		
		/*!
		 * \brief Initialise la position de la caméra
		 */
		void init_camera();
		/*!
		 * \brief Initialise la position de la caméra
		 */
		void update_camera();
};

#endif //__CAMERA_LIBRE_H__
