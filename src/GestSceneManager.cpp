#include "GestSceneManager.h"
GestSceneManager* GestSceneManager::_instance = NULL;


GestSceneManager * GestSceneManager::getSingleton(void)
{
    if(_instance == NULL)
    {
        new GestSceneManager();
    }
	return _instance;
}
GestSceneManager::GestSceneManager()
{
    if(_instance == NULL)
	{
	    _instance = this;
	}
	 _listCameras.clear();
}

GestSceneManager::~GestSceneManager()
{
    //dtor
}
void GestSceneManager::addCam(CameraFixeAbstract * camera)
{

    this->_listCameras.push_back(camera);
}

CameraFixeAbstract * GestSceneManager::getCam(int id)
{

    if(id > _listCameras.size())
    {
        return NULL;
    }
    return _listCameras.at(id);
}

Ogre::SceneManager * GestSceneManager::getSceneMgr()
{
    return _sceneManager;
}

void GestSceneManager::setSceneManager(Ogre::SceneManager * sceneManager)
{
    this->_sceneManager = sceneManager;
}

void GestSceneManager::remCam(CameraFixeAbstract * cam)
{
   int i;
   for(i=0; i<_listCameras.size(); i++)
   {
       if(_listCameras[i]==cam)
       {
           _listCameras.erase(_listCameras.begin()+i);
           return;
       }
   }
}
int GestSceneManager::getCount()
{
   return _listCameras.size();
}
