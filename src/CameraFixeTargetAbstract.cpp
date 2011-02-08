#include "CameraFixeTargetAbstract.h"


CameraFixeTargetAbstract::CameraFixeTargetAbstract(Ogre::SceneManager * sceneMgr, Ogre::String cameraName, Ogre::SceneNode * target) : CameraFixeAbstract(sceneMgr, cameraName) {
	this->target = target;
	
	this->camera->lookAt(this->target->_getDerivedPosition());
	this->camera->setPosition(this->target->_getDerivedPosition());
	this->camera->setOrientation(this->target->_getDerivedOrientation());
	
	// set the camera to track itself the target and don't 'roll' rotate 
	this->camera->setAutoTracking(true, this->target);
	this->camera->setFixedYawAxis(true);
}

CameraFixeTargetAbstract::~CameraFixeTargetAbstract() {
}
