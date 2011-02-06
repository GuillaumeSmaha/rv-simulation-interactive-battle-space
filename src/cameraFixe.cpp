#include "cameraFixe.h"


CameraFixe::CameraFixe(Ogre::Camera * camera, Ogre::SceneManager * sceneMgr){
    this->camera= camera;
    this->sceneMgr= sceneMgr;
}

//CameraFixe::CameraFixe(const Ogre::Camera & camera){
//    this = &camera;       
//}

int CameraFixe::init_camera(){

	this->camera->setPosition(Ogre::Vector3(90, 25, 90));
	this->camera->lookAt(this->sceneMgr->getRootSceneNode()->getPosition());
	
}
