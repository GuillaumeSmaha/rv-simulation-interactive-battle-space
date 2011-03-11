#include "CameraFixe.h"


CameraFixe::CameraFixe(Ogre::SceneManager * sceneMgr, Ogre::String cameraName, Ogre::SceneNode * nodeInit) : CameraFixeAbstract(sceneMgr, cameraName)
{
    this->camera->setFixedYawAxis(true);
	this->camera->setOrientation(nodeInit->_getDerivedOrientation());
	this->camera->setPosition(nodeInit->_getDerivedPosition());
	this->camera->moveRelative(Ogre::Vector3(0.0, 0.0, 50.0));
	this->camera->lookAt(nodeInit->getPosition()+Ogre::Vector3(0.0, 0.0, 10.0));
	//this->camera->lookAt(nodeInit->_getDerivedPosition());
}
		
void CameraFixe::init_camera()
{
	/*
	this->camera->setPosition(Ogre::Vector3(100, 100, -500));
	this->camera->lookAt(this->sceneMgr->getRootSceneNode()->getPosition());
	this->camera->setOrientation(Ogre::Quaternion(0, 0, 0, 1));
	*/

}
		
void CameraFixe::update_camera()
{
}
