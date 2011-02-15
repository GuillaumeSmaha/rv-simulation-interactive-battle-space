#include "CameraFixeTarget.h"


CameraFixeTarget::CameraFixeTarget(Ogre::SceneManager * sceneMgr, Ogre::String cameraName, Ogre::SceneNode * nodeTarget, Ogre::SceneNode * nodePosition) : CameraFixeAbstract(sceneMgr, cameraName)
{
	this->nodeTarget = nodeTarget;
	this->nodePosition = nodePosition;
}

CameraFixeTarget::~CameraFixeTarget()
{
}

void CameraFixeTarget::init_camera()
{	
	this->camera->setFixedYawAxis(false);
	
	this->update_camera();
}

void CameraFixeTarget::update_camera()
{
	this->camera->setPosition(this->getNodePosition()->_getDerivedPosition());
	this->camera->setOrientation(this->getNodePosition()->_getDerivedOrientation());
	this->camera->lookAt(this->getNodeTarget()->_getDerivedPosition());
	Ogre::Vector3 v = this->getNodeTarget()->_getDerivedPosition()-this->getNodePosition()->_getDerivedPosition();
	this->camera->rotate(v, Ogre::Degree(180));
}
