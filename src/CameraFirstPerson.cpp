#include "CameraFirstPerson.h"

CameraFirstPerson::CameraFirstPerson(Ogre::SceneManager * sceneMgr, Ogre::String cameraName, Ogre::SceneNode * target) : CameraFixeTargetAbstract(sceneMgr, cameraName, target)
{
	
}


void CameraFirstPerson::init_camera()
{
    
	this->camera->yaw(Ogre::Radian(180));
	this->camera->pitch(Ogre::Radian(0));
	this->camera->moveRelative(Ogre::Vector3(0, 5, 0));
}
