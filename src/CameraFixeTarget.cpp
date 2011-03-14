#include "CameraFixeTarget.h"


CameraFixeTarget::CameraFixeTarget(Ogre::SceneManager * sceneMgr, Ogre::String cameraName, Ogre::SceneNode * nodeTarget, Ogre::SceneNode * nodePosition) : CameraAbstract(sceneMgr, cameraName)
{
	this->nodeTarget = nodeTarget;
	this->nodePosition = nodePosition;

	//this->lightSpeedSystem = this->sceneMgr->createParticleSystem("LightSpeedParticles", "Space/Dust2");
	//lightSpeedSystem->setEmitting(false);
}

CameraFixeTarget::~CameraFixeTarget()
{
}

void CameraFixeTarget::init_camera()
{	
	this->camera->setFixedYawAxis(false);
	
	this->update_camera();

	//nodeLightSpeed = this->nodePosition->createChildSceneNode("LightSpeedNode");
	//nodeLightSpeed->attachObject(lightSpeedSystem);
	//nodeLightSpeed->setPosition(0, 0, 50);
}

void CameraFixeTarget::update_camera()
{
	this->camera->setPosition(this->getNodePosition()->_getDerivedPosition());
	this->camera->setOrientation(this->getNodePosition()->_getDerivedOrientation());
	this->camera->lookAt(this->getNodeTarget()->_getDerivedPosition());
	Ogre::Vector3 v = this->getNodeTarget()->_getDerivedPosition()-this->getNodePosition()->_getDerivedPosition();
	this->camera->rotate(v, Ogre::Degree(180));
}
