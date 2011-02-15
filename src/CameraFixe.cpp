#include "CameraFixe.h"


CameraFixe::CameraFixe(Ogre::SceneManager * sceneMgr, Ogre::String cameraName) : CameraFixeAbstract(sceneMgr, cameraName)
{
	
}
		
void CameraFixe::init_camera()
{
	
	this->camera->setPosition(Ogre::Vector3(100, 100, -500));
	this->camera->lookAt(this->sceneMgr->getRootSceneNode()->getPosition());
}
		
void CameraFixe::update_camera()
{
}
