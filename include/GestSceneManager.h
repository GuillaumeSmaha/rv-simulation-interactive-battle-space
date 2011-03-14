/*!
*  \file  GestSceneManager.h
*  \brief Ce fichier contient la déclaration de la classe GestSceneManager.
*/
#ifndef __GEST_SCENE_MANAGER_H__
#define __GEST_SCENE_MANAGER_H__

#include <Ogre.h>
#include "CameraAbstract.h"

/*!
 * \class GestSceneManager
 *  \brief Gère le SceneManager et les Cameras
 */
class GestSceneManager
{
    private:
        /*!
		 *  \brief Instance du GestSceneManager
		 */
        static GestSceneManager * _instance ;
        /*!
		 *  \brief Vecteur des caméras
		 */
        std::vector<CameraAbstract*>_listCameras;
        /*!
		 *  \brief SceneManager
		 */
        Ogre::SceneManager * _sceneManager;
    public:
        /*!
		 *  \brief Constructor
		 */
        GestSceneManager();
        /*!
		 *  \brief Destructor
		 */
        virtual ~GestSceneManager();
        /*!
		 *  \brief Donne l'instance du GestSceneManager
		 */
        static GestSceneManager * getSingleton(void);
        /*!
         * \brief Detruit le singleton
         */
        static void destroy();

        /*!
         * \brief Détruit les caméras
         */
        void deleteAll();
        /*!
		 *  \brief Rajoute une caméra à la liste
		 *  \param camera Caméra à rajouter à la liste
		 */
        void addCam(CameraAbstract * camera);
        /*!
		 *  \brief [Static] Rajoute une caméra à la liste
		 *  \param camera Caméra à rajouter à la liste
		 */
        static void addCamera(CameraAbstract * camera)
        {
            getSingleton()->addCam(camera);
        }
        /*!
		 *  \brief Récupère l'instance d'une caméra (nonsafe)
		 *  \param id ID de la caméra à récupérer
		 *  \return Instance de la caméra
		 */
        CameraAbstract * getCam(unsigned int id);
        /*!
		 *  \brief [Static] Récupère l'instance d'une caméra (nonsafe)
		 *  \param id ID de la caméra à récupérer
		 *  \return Instance de la caméra
		 */
        static CameraAbstract * getCamera(int id)
        {
            return getSingleton()->getCam(id);
        }
        /*!
		 *  \brief Supprime la caméra de la liste
		 *  \param cam Camera à supprimer
		 */
        void remCam(CameraAbstract * cam);
        /*!
		 *  \brief [Static] Supprime la caméra de la liste
		 *  \param cam Camera à supprimer
		 */
        static void remCamera(CameraAbstract * cam)
        {
            getSingleton()->remCam(cam);
        }
        /*!
		 *  \brief Récupère l'instance du SceneManager
		 *  \return L'instance du SceneManager
		 */
        Ogre::SceneManager * getSceneMgr();
        /*!
		 *  \brief [Static] Récupère l'instance du SceneManager
		 *  \return L'instance du SceneManager
		 */
        static  Ogre::SceneManager * getSceneManager()
        {
            return getSingleton()->getSceneMgr();
        }
        /*!
		 *  \brief Passe l'instance du SceneManager
		 *  \param sceneManager L'instance du SceneManager
		 */
        void setSceneManager(Ogre::SceneManager * sceneManager);
        /*!
         *  \brief Renvoie le nombre de Caméras
         *  \return Le nombre de caméras
         */
        int getCount();
        /*!
         *  \brief [Static] Renvoie le nombre de Caméras
         *  \return Le nombre de caméras
         */
        static  int getCamCount()
        {
            return getSingleton()->getCount();
        }
        static Ogre::Real getProjectedSize(Ogre::MovableObject* object, Ogre::Real size, Ogre::Vector3 point)
        {
             Ogre::Real fsize = -1;
			Ogre::Real tmp;
			int i = GestSceneManager::getCamCount();
			for(;i>0;i--)
			{
				tmp = GestSceneManager::getProjectedSize(object, size, point,  GestSceneManager::getCamera(i-1)->getCamera());
				if(tmp > fsize)
				{
					fsize = tmp;
				}
			}
			return fsize;

        }
		static Ogre::Real getProjectedSize(Ogre::MovableObject* object, Ogre::Real size)
		{
			Ogre::Real fsize = -1;
			Ogre::Real tmp;
			int i = GestSceneManager::getCamCount();
			for(;i>0;i--)
			{
				tmp = GestSceneManager::getProjectedSize(object, size,  GestSceneManager::getCamera(i-1)->getCamera());
				if(tmp > fsize)
				{
					fsize = tmp;
				}
			}
			return fsize;
		}
		static Ogre::Real getProjectedSize(Ogre::MovableObject* object, Ogre::Vector3 point)
		{
			Ogre::Real fsize = -1;
			Ogre::Real tmp;
			int i = GestSceneManager::getCamCount();
			for(;i>0;i--)
			{
				tmp = GestSceneManager::getProjectedSize(object, object->getWorldBoundingSphere().getRadius(), point,  GestSceneManager::getCamera(i-1)->getCamera());
				if(tmp > fsize)
				{
					fsize = tmp;
				}
			}
			return fsize;
		}
		/*!
         *  \brief [Static] Renvoie la taille normalisée affichée de l'objet [0;1]
         *  \return la taille normalisée
         */
		static Ogre::Real getProjectedSize(Ogre::MovableObject* object)
		{
			return getProjectedSize(object, object->getWorldBoundingSphere().getRadius());
		}
		static Ogre::Real getProjectedSize(Ogre::MovableObject* object, Ogre::Camera* cam)
		{
			return GestSceneManager::getProjectedSize(object, object->getWorldBoundingSphere().getRadius(), cam);
		}
		static Ogre::Real getProjectedSize(Ogre::MovableObject* object, Ogre::Real size, Ogre::Camera* cam)
		{
			return getProjectedSize(object, size, object->getWorldBoundingBox(true).getCenter(), cam);
		}
		static Ogre::Real getProjectedSize(Ogre::MovableObject* object, Ogre::Vector3 point, Ogre::Camera* cam)
		{
			return getProjectedSize(object, object->getWorldBoundingSphere().getRadius(), point , cam);
		}
		static Ogre::Real getProjectedSize(Ogre::MovableObject* object, Ogre::Real size, Ogre::Vector3 point, Ogre::Camera* cam);

		//bool getScreenspaceCoords(Ogre::MovableObject* object, Ogre::Camera* camera, Ogre::Vector2& result);
    protected:
};

#endif // __GEST_SCENE_MANAGER_H__
