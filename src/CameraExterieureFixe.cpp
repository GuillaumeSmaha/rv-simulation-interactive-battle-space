#include "CameraExterieureFixe.h"

CameraExterieureFixe::CameraExterieureFixe(Ogre::SceneManager * sceneMgr, Ogre::String cameraName, Ogre::SceneNode * target) : CameraFixeTargetAbstract(sceneMgr, cameraName, target) {
}


void CameraExterieureFixe::init_camera() {
	
	this->camera->yaw(Ogre::Radian(180));
	this->camera->pitch(Ogre::Radian(-15));
	this->camera->moveRelative(Ogre::Vector3(0, 0, 75));
}
