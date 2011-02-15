/*!
 *  \file  Camera.h
 *  \brief Ce fichier contient la déclaration de la classe CameraFixeAbstract. C'est la classe une classe abstraite qui permet d'utiliser différents types de caméras fixes.
 */
#ifndef __CAMERA_FIXE_ABSTRACT_H__
#define __CAMERA_FIXE_ABSTRACT_H__

#include <OgreRoot.h>
#include <OgreCamera.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgrePrerequisites.h>

/*!
 * \class CameraFixeAbstract
 * \brief Classe abstraite entre le programme principale et la caméra effectivement utilisé. Elle ne peut donc pas être instancié directement
 */
class CameraFixeAbstract {
	public:

		/// Définit les différents types de caméra
		enum CameraType
		{
			/// Caméra Null
			CAMERA_NULL = 0,
			/// Caméra fixe
			CAMERA_FIXE = 1,
			/// Caméra à la première personne attachée à un noeud
			CAMERA_FISRT_PERSON = 2,
			/// Caméra Extérieure fixe attachée à un noeud
			CAMERA_EXTERIEURE_FIXE = 3
		};
	
	public:		 
		/*!
		 * \brief Constructeur
		 * \param sceneMgr Pointeur sur le manager de la scène
		 * \param cameraName Nom de la nouvelle caméra
		 */
		CameraFixeAbstract(Ogre::SceneManager * sceneMgr, Ogre::String cameraName);
		/*!
		 * \brief Destructeur virtuel
		 */
		 virtual ~CameraFixeAbstract();
		 
		/*!
		 * \brief Initialise la position de la caméra\n
		 * Méthode virtuelle pure à réimplémenter.
		 */
		virtual void init_camera() = 0;
		/*!
		 * \brief Met à jour la position de la caméra\n
		 * Méthode virtuelle pure à réimplémenter.
		 */
		virtual void update_camera() = 0;
		/*!
		 *  \brief Direction de la caméra
		 * 	\param x Coordonnée en X
		 * 	\param y Coordonnée en Y
		 * 	\param z Coordonnée en Z
		 */
        virtual void setDirection( Ogre::Real x, Ogre::Real y, Ogre::Real z );
		/*!
		 *  \brief Direction de la caméra
		 * 	\param vector Direction
		 */
        virtual void setDirection( Ogre::Vector3 direction );
		/*!
		 *  \brief Direction de la caméra
		 * 	\param vector Direction
		 */
        virtual void setDirection( Ogre::SceneNode * nodeDirection );
		/*!
		 *  \brief Position de la caméra
		 * 	\param x Coordonnée en X
		 * 	\param y Coordonnée en Y
		 * 	\param z Coordonnée en Z
		 */
        virtual void setPosition( Ogre::Real x, Ogre::Real y, Ogre::Real z );
		/*!
		 *  \brief Position de la caméra
		 * 	\param vector Position
		 */
        virtual void setPosition( Ogre::Vector3 position );
		
		/*!
		 * \brief [Getter] Pointeur sur la caméra
		 * \return Le nom de la caméra
		 */
		Ogre::Camera * getCamera()
		{
			return camera;
		}
		/*!
		 * \brief [Getter] Nom de la caméra
		 * \return Le nom de la caméra
		 */
		Ogre::String getCameraName()
		{
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
		Ogre::String cameraName;
};

#endif // __CAMERA_FIXE_ABSTRACT_H__ 
