/*!
 *  \file  CameraFirstPerson.h
 *  \brief Ce fichier contient la déclaration de la classe Camera. C'est la classe gérant une caméra à la premiere personne
 */
#ifndef __CAMERA_FIRST_PERSON_H__
#define __CAMERA_FIRST_PERSON_H__

#include "CameraFixeTargetAbstract.h"


/*!
 * \class CameraFirstPerson
 * \brief Classe permetttant de gérer une caméra à la première personne
 */
class CameraFirstPerson : public CameraFixeTargetAbstract {	
		
	public:
		/*!
		 * \brief Constructeur
		 * \param sceneMgr Pointeur sur le manager de la scène
		 * \param cameraName Nom de la nouvelle caméra
		 * \param target Noeud auquel est attaché la caméra
		 */
		CameraFirstPerson(Ogre::SceneManager * sceneMgr, Ogre::String cameraName, Ogre::SceneNode * target);
		/*!
		 * \brief Initialise la caméra
		 */
		void init_camera();

};

#endif //__CAMERA_FIRST_PERSON_H__
