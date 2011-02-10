#include "CameraFixeTarget.h"


CameraFixeTarget::CameraFixeTarget(Ogre::SceneManager * sceneMgr, Ogre::String cameraName, Ogre::SceneNode * target) : CameraFixeAbstract(sceneMgr, cameraName)
{
	this->target = target;
	
	this->camera->lookAt(this->target->_getDerivedPosition());
	this->camera->setPosition(this->target->_getDerivedPosition());
	this->camera->setOrientation(this->target->_getDerivedOrientation());
	
	// set the camera to track itself the target and don't 'roll' rotate 
	this->camera->setAutoTracking(true, this->target);
	this->camera->setFixedYawAxis(true);
}

CameraFixeTarget::~CameraFixeTarget()
{
}

void CameraFixeTarget::init_camera()
{
	this->camera->yaw(Ogre::Radian(180));
	this->camera->pitch(Ogre::Radian(0));
	this->camera->moveRelative(Ogre::Vector3(0, 5, 0));
}
