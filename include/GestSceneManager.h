/*!
*  \file  GestSceneManager.h
*  \brief Ce fichier contient la déclaration de la classe GestSceneManager.
*/
#ifndef GESTSCENEMANAGER_H
#define GESTSCENEMANAGER_H
#include <Ogre.h>
#include "CameraFixeAbstract.h"
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
        std::vector<CameraFixeAbstract*>_listCameras;
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
		 *  \brief Rajoute une caméra à la liste
		 *  \param camera Caméra à rajouter à la liste
		 */
        void addCam(CameraFixeAbstract * camera);
        /*!
		 *  \brief [Static] Rajoute une caméra à la liste
		 *  \param camera Caméra à rajouter à la liste
		 */
        static void addCamera(CameraFixeAbstract * camera)
        {
            getSingleton()->addCam(camera);
        }
        /*!
		 *  \brief Récupère l'instance d'une caméra (nonsafe)
		 *  \param id ID de la caméra à récupérer
		 *  \return Instance de la caméra
		 */
        CameraFixeAbstract * getCam(int id);
        /*!
		 *  \brief [Static] Récupère l'instance d'une caméra (nonsafe)
		 *  \param id ID de la caméra à récupérer
		 *  \return Instance de la caméra
		 */
        static CameraFixeAbstract * getCamera(int id)
        {
            return getSingleton()->getCam(id);
        }
        /*!
		 *  \brief Supprime la caméra de la liste
		 *  \param cam Camera à supprimer
		 */
        void remCam(CameraFixeAbstract * cam);
        /*!
		 *  \brief [Static] Supprime la caméra de la liste
		 *  \param cam Camera à supprimer
		 */
        static void remCamera(CameraFixeAbstract * cam)
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
    protected:
};

#endif // GESTSCENEMANAGER_H
