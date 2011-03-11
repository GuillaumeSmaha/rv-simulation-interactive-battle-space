#include "CameraFixeTarget.h"


CameraFixeTarget::CameraFixeTarget(Ogre::SceneManager * sceneMgr, Ogre::String cameraName, Ogre::SceneNode * nodeTarget, Ogre::SceneNode * nodePosition) : CameraFixeAbstract(sceneMgr, cameraName)
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

void CameraFixeTarget::update_particles()
{
	const float maxDist  = 250.0;
	const float mirrorDist = maxDist*0.99;
	const float dimFactor = 0.8*0.005*0.005;   
	const float maxDist2 = maxDist*maxDist;
	Ogre::Camera* cam = this->getCamera();
	const Ogre::Vector3& camPos = cam->getRealPosition();

	const float twiceMaxDist = 2 * maxDist;

	Ogre::ParticleIterator pit = lightSpeedSystem->_getIterator();
   
	while (!pit.end())
	{
		Ogre::Particle* particle = pit.getNext();
		Ogre::Vector3& pos = particle->position;
		//particle->timeToLive = 999999.0f;

		// position particles near camera
		// (keep moving them toward camera until within range)
		while (pos.x - camPos.x > maxDist)
			pos.x -= twiceMaxDist;
		while (pos.x - camPos.x < -maxDist)
			pos.x += twiceMaxDist;
		while (pos.y - camPos.y > maxDist)
			pos.y -= twiceMaxDist;
		while (pos.y - camPos.y < -maxDist)
			pos.y += twiceMaxDist;
		while (pos.z - camPos.z > maxDist)
			pos.z -= twiceMaxDist;
		while (pos.z - camPos.z < -maxDist)
			pos.z += twiceMaxDist;



		//Ogre::Vector3 pDir = pos-camPos;
		//float dist = pDir.squaredLength();
		//float dim = dist*dimFactor;
		//particle->setDimensions(dim, dim);
		//Ogre::ParticleEmitter* emiter = lightSpeedSystem->getEmitter(0);
		//emiter->setDirection(cam->getDirection());
		Ogre::Vector3 &dir = particle->direction;
		Ogre::Vector3 camDir = cam->getDirection();
		
		//dir.x = camDir.x;
		//dir.y = camDir.y;
		//dir.z = -camDir.z;
		dir = camDir;
		
		//Ogre::LogManager::getSingleton().logMessage(Ogre::StringConverter::toString(camDir));
		//camDir.z = -1;
		//dir = camDir;

		//Ogre::ParticleEmitter *emitter = lightSpeedSystem->getEmitter(0);
		//emitter->setDirection(
		//dir = cam->getDirection();
	}         

	Ogre::LogManager::getSingleton().logMessage(Ogre::StringConverter::toString(cam->getDerivedPosition()));

}