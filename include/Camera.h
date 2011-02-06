/*!
 **  \file  Camera.h
 **  \brief Ce fichier contient la déclaration de la classe Camera. C'est la classe une classe abstraite qui permet d'utiliser différents types de caméras.
 **/
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <iostream>
#include <OgreCamera.h>
#include <OgreSceneManager.h>

/*!
 * \class Camera
 * \brief Classe abstraite entre le programme principale et la caméra effectivement utilisé. Elle ne peut donc pas être instancié directement
 */
class Camera {
	public:		 
		/*!
		 * \brief Constructeur
		 * \param sceneMgr Pointeur sur le manager de la scène
		 * \param cameraName Nom de la nouvelle caméra
		 */
		Camera(Ogre::SceneManager * sceneMgr, std::string cameraName) {
			this->sceneMgr = sceneMgr;
			this->cameraName = cameraName;
			this->camera = this->sceneMgr->createCamera(cameraName);
		}
		/*!
		 * \brief Destructeur virtuel
		 */
		 virtual ~Camera() {
			delete this->camera;
		}
		 
		/*!
		 * \brief Initialise la position de la caméra\n
		 * Méthode virtuelle pure à réimplémenter.
		 * \return Int
		 */
		virtual int init_camera() = 0;
		
		/*!
		 * \brief [Getter] Pointeur sur la caméra
		 * \return Le nom de la caméra
		 */
		Ogre::Camera * get_camera() {
			return camera;
		}
		/*!
		 * \brief [Getter] Nom de la caméra
		 * \return Le nom de la caméra
		 */
		std::string get_cameraName() {
			return cameraName;
		}
	protected:
		/*!
		 * \brief Pointeur sur le SceneManager de l'application
		 */
		Ogre::SceneManager * sceneMgr;
		/*!
		 * \brief Camera instanciée
		 */
		Ogre::Camera * camera;
		/*!
		 * \brief Nom de la caméra
		 */
		std::string cameraName;
};

#endif // __CAMERA_H__ 
