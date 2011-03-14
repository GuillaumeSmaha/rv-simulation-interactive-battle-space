#include "CameraAbstract.h"

CameraAbstract::CameraAbstract(Ogre::SceneManager * sceneMgr, Ogre::String cameraName)
{
	this->sceneMgr = sceneMgr;
	this->cameraName = cameraName;
	this->camera = this->sceneMgr->createCamera(cameraName);
	
	// set the frustrum plan
	this->camera->setNearClipDistance(1);
	this->camera->setFarClipDistance(1000);
	
	// enable infinite far clip distance if we can
	if (Ogre::Root::getSingleton().getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE))
		this->camera->setFarClipDistance(0);

}

CameraAbstract::~CameraAbstract()
{
	this->sceneMgr->destroyCamera(this->cameraName);
}

void CameraAbstract::update_particles()
{
}

void CameraAbstract::setDirection( Ogre::Real x, Ogre::Real y, Ogre::Real z )
{
	this->camera->lookAt( Ogre::Vector3(x, y, z) );
}


void CameraAbstract::setDirection( Ogre::Vector3 direction )
{
	this->camera->lookAt( direction );
}


void CameraAbstract::setDirection( Ogre::SceneNode * nodeDirection )
{
	this->camera->lookAt( nodeDirection->getPosition() );
}


void CameraAbstract::setPosition( Ogre::Real x, Ogre::Real y, Ogre::Real z )
{
	this->camera->setPosition( Ogre::Vector3(x, y, z) );
}


void CameraAbstract::setPosition( Ogre::Vector3 position )
{
	this->camera->setPosition( position );
}

