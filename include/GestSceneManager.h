#ifndef GESTSCENEMANAGER_H
#define GESTSCENEMANAGER_H
#include <Ogre.h>
#include "CameraFixeAbstract.h"

class GestSceneManager
{
    private:
        static GestSceneManager * _instance ;
        std::vector<CameraFixeAbstract*>_listCameras;
        Ogre::SceneManager * _sceneManager;
    public:
        GestSceneManager();
        virtual ~GestSceneManager();
        static GestSceneManager * getSingleton(void);


        void addCam(CameraFixeAbstract * camera);
        static void addCamera(CameraFixeAbstract * camera)
        {
            getSingleton()->addCam(camera);
        }
        CameraFixeAbstract * getCam(int id);
        static CameraFixeAbstract * getCamera(int id)
        {
            return getSingleton()->getCam(id);
        }
        void remCam(CameraFixeAbstract * cam);
        static void remCamera(CameraFixeAbstract * cam)
        {
            getSingleton()->remCam(cam);
        }
        Ogre::SceneManager * getSceneMgr();
        static  Ogre::SceneManager * getSceneManager()
        {
            return getSingleton()->getSceneMgr();
        }
        void setSceneManager(Ogre::SceneManager * sceneManager);
        int getCount();
        static  int getCamCount()
        {
            return getSingleton()->getCount();
        }
    protected:
};

#endif // GESTSCENEMANAGER_H
