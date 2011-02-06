/*!
 *  \file  CameraThirdPerson.h
 *  \brief Contient la déclaration de la classe gérant une caméra à la troizième personne
 */
#ifndef __CAMERA_THIRD_PERSON_H__
#define __CAMERA_THIRD_PERSON_H__

#include <Ogre.h>
#include <OISMouse.h>
#include "Camera.h"

/*!
 * \class CameraThirdPerson
 * \brief Classe permetttant de gérer une caméra à la troizième personne
 */
class CameraThirdPerson : public Camera
{
	private:
		/*!
		 * \brief Noeud sur lequel est attaché la caméra
		 */
		Ogre::SceneNode *targetNode;
		/*!
		 * \brief Si le mode orbital est actif
		 */
		bool orbiting;
		/*!
		 * \brief Si le mode zoom est actif
		 */
		bool zooming;

	public:
		/*!
		 * \brief Constructeur
		 * \param sceneMgr Pointeur sur le manager de la scène
		 * \param cameraName Nom de la nouvelle caméra
		 * \param target Noeud auquel est attaché la caméra
		 */
		CameraThirdPerson(Ogre::SceneManager * sceneMgr, Ogre::String cameraName, Ogre::SceneNode * target);
		/*!
		 * \brief Initialise la position de la caméra
		 * \return Int
		 */
		int init_camera();
		
		/*!
		 *  \brief Action à effectuer pour l'événement "souis en mouvement"
		 * 	\param evt Evenement de la souris
		 */
		void updateMovement(const OIS::MouseEvent &evt);
		
		/*!
		 * \brief [Getter] Mode orbital
		 * \return Si le mode est actif
		 */
		bool getOrbiting(void);
		/*!
		 * \brief [Setter] Mode orbital
		 * \param orbiting Définit le mode orbital
		 */
		void setOrbiting(bool orbiting);
		
		/*!
		 * \brief [Getter] Mode zoom
		 * \return Si le mode est actif
		 */
		bool getZooming(void);
		/*!
		 * \brief [Setter] Mode zoom
		 * \param zooming Définit le mode zoom
		 */
		void setZooming(bool zooming);
};

#endif // __CAMERA_THIRD_PERSON_H__
