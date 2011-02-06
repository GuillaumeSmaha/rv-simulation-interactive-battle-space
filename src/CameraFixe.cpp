#include "CameraFixe.h"


CameraFixe::CameraFixe(Ogre::SceneManager * sceneMgr, std::string cameraName) : Camera(sceneMgr, cameraName) {
}
		
int CameraFixe::init_camera() {
	this->camera->setPosition(Ogre::Vector3(90, 25, 90));
	this->camera->lookAt(this->sceneMgr->getRootSceneNode()->getPosition());
	
	return 1;
}
