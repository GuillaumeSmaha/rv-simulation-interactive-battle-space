#include "CameraThirdPerson.h"

CameraThirdPerson::CameraThirdPerson(Ogre::SceneManager * sceneMgr, Ogre::String cameraName, Ogre::SceneNode * target) : Camera(sceneMgr, cameraName)
{
	this->targetNode = target;
}


int CameraThirdPerson::init_camera() {
	this->orbiting = false;
	this->zooming = false;

	// create the camera
	this->camera->setNearClipDistance(1);
	this->camera->setFarClipDistance(1000);
	
	// enable infinite far clip distance if we can
	if (Ogre::Root::getSingleton().getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE))
		this->camera->setFarClipDistance(0);   
    
	// set the position ant rotation of the camera to look at the target
	this->camera->setPosition(this->targetNode->_getDerivedPosition());
	this->camera->setOrientation(this->targetNode->_getDerivedOrientation());
	this->camera->yaw(Ogre::Radian(180));
	this->camera->pitch(Ogre::Radian(-15));
	this->camera->moveRelative(Ogre::Vector3(0, 0, 20));

	// set the camera to track itself the target and don't 'roll' rotate 
	this->camera->setAutoTracking(true, this->targetNode);
	this->camera->setFixedYawAxis(true);
}


void CameraThirdPerson::updateMovement(const OIS::MouseEvent &evt) {
	Ogre::Real dist = (this->camera->getPosition() - this->targetNode->_getDerivedPosition()).length();
	
	if (this->orbiting)   // yaw around the target, and pitch locally
	{
		this->camera->setPosition(this->targetNode->_getDerivedPosition());
		this->camera->yaw(Ogre::Degree(-evt.state.X.rel * 0.25f));
		
//		Ogre::Vector3 pitch = (this->camera->getOrientation() * Ogre::Vector3::UNIT_Y);
//		std::cout << pitch << std::endl;
//		
//		if(pitch < 0) pitch = -pitch;
//		if((-evt.state.Y.rel > 0 && pitch > 10) ||
//			(-evt.state.Y.rel < 0 && pitch < 80))
			this->camera->pitch(Ogre::Degree(-evt.state.Y.rel * 0.25f));
		
		this->camera->moveRelative(Ogre::Vector3(0, 0, dist));
	}
	else if (this->zooming)  // move the camera toward or away from the target
	{
		this->camera->moveRelative(Ogre::Vector3(0, 0, -evt.state.Y.rel * 0.004f * dist));		
	}
	else if (evt.state.Z.rel != 0)  // move the camera toward or away from the target
	{
		if((-evt.state.Z.rel > 0 && dist < 400) ||
			(-evt.state.Z.rel < 0 && dist > 10))
			this->camera->moveRelative(Ogre::Vector3(0, 0, -evt.state.Z.rel * 0.0008f * dist));
	}
}


bool CameraThirdPerson::getOrbiting(void) {
	return this->orbiting;
}


void CameraThirdPerson::setOrbiting(bool orbiting) {
	this->orbiting = orbiting;
}


bool CameraThirdPerson::getZooming(void) {
	return this->zooming;
}


void CameraThirdPerson::setZooming(bool zooming) {
	this->zooming = zooming;
}

