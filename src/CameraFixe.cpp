#include "CameraFixe.h"


CameraFixe::CameraFixe(Ogre::SceneManager * sceneMgr, Ogre::String cameraName) : Camera(sceneMgr, cameraName) {
}
		
int CameraFixe::init_camera() {
	this->camera->setPosition(Ogre::Vector3(100, 100, -500));
	this->camera->lookAt(this->sceneMgr->getRootSceneNode()->getPosition());
	this->camera->setNearClipDistance(5);
	
	return 1;
}
