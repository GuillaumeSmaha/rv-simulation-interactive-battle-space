#include "CameraFixe.h"


CameraFixe::CameraFixe(Ogre::SceneManager * sceneMgr, Ogre::String cameraName) : CameraFixeAbstract(sceneMgr, cameraName)
{
	
}
		
void CameraFixe::init_camera()
{
	
	this->camera->setPosition(Ogre::Vector3(100, 100, -500));
	this->camera->lookAt(this->sceneMgr->getRootSceneNode()->getPosition());
	this->camera->setOrientation(Ogre::Quaternion(0, 0, 0, 1));
}
		
void CameraFixe::update_camera()
{
}
