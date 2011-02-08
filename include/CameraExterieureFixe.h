/*!
 *  \file  CameraExterieureFixe.h
 *  \brief Ce fichier contient la déclaration de la classe Camera. C'est la classe gérant une caméra fixe de dos
 */
#ifndef __CAMERA_EXTERIEURE_FIXE_H__
#define __CAMERA_EXTERIEURE_FIXE_H__

#include "CameraFixeTargetAbstract.h"


/*!
 * \class CameraExterieureFixe
 * \brief Classe permetttant de gérer une caméra fixe de dos
 */
class CameraExterieureFixe : public CameraFixeTargetAbstract {
		
	public:
		/*!
		 * \brief Constructeur
		 * \param sceneMgr Pointeur sur le manager de la scène
		 * \param cameraName Nom de la nouvelle caméra
		 * \param target Noeud auquel est attaché la caméra
		 */
		CameraExterieureFixe(Ogre::SceneManager * sceneMgr, Ogre::String cameraName, Ogre::SceneNode * target);
		/*!
		 * \brief Initialise la caméra
		 * \return Int
		 */
		void init_camera();

/*TODO*/

};

#endif //__CAMERA_EXTERIEURE_FIXE_H__
