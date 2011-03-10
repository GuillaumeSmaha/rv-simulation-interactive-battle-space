#include "GestSceneManager.h"
#include "Utils.h"
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

    if(_sceneManager != NULL)
    {
        _sceneManager = NULL;
    }
    _listCameras.clear();

}

void GestSceneManager::addCam(CameraFixeAbstract * camera)
{

    this->_listCameras.push_back(camera);
}

CameraFixeAbstract * GestSceneManager::getCam(unsigned int id)
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
   for(unsigned int i = 0; i < _listCameras.size() ; i++)
   {
       if(_listCameras[i] == cam)
       {
		   //~ delete cam;
           _listCameras.erase(_listCameras.begin()+i);
           return;
       }
   }
}

int GestSceneManager::getCount()
{
   return _listCameras.size();
}

void GestSceneManager::destroy()
{
    if(_instance != NULL)
    {
        delete _instance;
    }
}

void GestSceneManager::deleteAll()
{
    _listCameras.clear();
}

Ogre::Real GestSceneManager::getProjectedSize(Ogre::MovableObject* object, Ogre::Real size, Ogre::Vector3 point, Ogre::Camera* cam)
{
	  if(!object->isInScene())
	  {
		return -1;
	  }
	  Ogre::Vector3 eyeSpacePos = cam->getViewMatrix(true) * point;
	  //équivalent à getRendering distance ?
	  if (eyeSpacePos.z > 0)
      {
            return -1;
	  }
	  Ogre::Vector3 spheresize(size, size, eyeSpacePos.z);
      spheresize = cam->getProjectionMatrix() * spheresize;
	  //TODO:vérifier que quand c supérieur à 1 == vraiment hors champ sinon utilisé eyeSpacePoz.z<0
      return  spheresize.x;//spheresize.x>1?-1:spheresize.x;
}

/*
bool  GestSceneManager::projectSizeAndPos(Ogre::Camera* cam,const Ogre::Vector3& pos,const Ogre::Real rad,Ogre::Real& x,Ogre::Real& y,Ogre::Real& cx,Ogre::Real& cy) {
    Ogre::Vector3 eyeSpacePos = cam->getViewMatrix(true) * pos;

    // z < 0 means in front of cam
    if (eyeSpacePos.z < 0) {
        // calculate projected pos
        Ogre::Vector3 screenSpacePos = cam->getProjectionMatrix() * eyeSpacePos;
        x = screenSpacePos.x;
        y = screenSpacePos.y;
        // calculate projected size
        Ogre::Vector3 spheresize(rad, rad, eyeSpacePos.z);
        spheresize = cam->getProjectionMatrix() * spheresize;
        cx = spheresize.x;
        cy = spheresize.y;
        return true;
    } else {
        cx = 0;
        cy = 0;
        x = (-eyeSpacePos.x > 0) ? -1 : 1;
        y = (-eyeSpacePos.y > 0) ? -1 : 1;
        return false;
    }
}
bool GestSceneManager::getScreenspaceCoords(Ogre::MovableObject* object, Ogre::Camera* camera, Ogre::Vector2& result)
{
   if(!object->isInScene())
      return false;

   const Ogre::AxisAlignedBox &AABB = object->getWorldBoundingBox(true);


   // Get the center point of the object's bounding box
   Ogre::Vector3 point = AABB.getCenter();

   // Is the camera facing that point? If not, return false
   Ogre::Plane cameraPlane = Ogre::Plane(Ogre::Vector3(camera->getDerivedOrientation().zAxis()), camera->getDerivedPosition());
   if(cameraPlane.getSide(point) != Ogre::Plane::NEGATIVE_SIDE)
      return false;

   // Transform the 3D point into screen space
   point = camera->getProjectionMatrix() * (camera->getViewMatrix() * point);

   // Transform from coordinate space [-1, 1] to [0, 1] and update in-value
   result.x = (point.x / 2) + 0.5f;
   result.y = 1 - ((point.y / 2) + 0.5f);

   return true;
}
*/
