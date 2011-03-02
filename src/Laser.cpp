#include "Laser.h"

using namespace std;


Laser::Laser(const Ogre::Vector3 &position, const Ogre::Quaternion &orientation) : position(position), orientation(orientation)
{
	this->timerLife = new Ogre::Timer();
	
    //~ this->billboardChain = GestSceneManager::getSceneManager()->createBillboardChain("laser"+Utils::toString(Utils::unique()));
	//~ this->billboardChain->setMaterialName("laser");
	//~ this->billboardChain->setMaxChainElements(1000);
	this->node = GestSceneManager::getSceneManager()->getSceneNode(NODE_NAME_GROUPE_LASERS)->createChildSceneNode("laserNode"+Utils::toString(Utils::unique()));
	
	this->node->_setDerivedPosition(position);
	this->node->_setDerivedOrientation(orientation);
	
	
    Ogre::ParticleSystem* thrusters = GestSceneManager::getSceneManager()->createParticleSystem(25);
    thrusters->setMaterialName("Reactor");
    thrusters->setDefaultDimensions(25, 25);

// Création de 2 émetteurs pour le système de particules
	Ogre::ParticleEmitter * emitter = thrusters->addEmitter("Point");

	// set the emitter properties
	emitter->setAngle(Ogre::Degree(3));
	emitter->setTimeToLive(0.5);
	emitter->setEmissionRate(25);
	emitter->setParticleVelocity(5);
	emitter->setDirection(Ogre::Vector3::NEGATIVE_UNIT_Z);
	emitter->setColour(Ogre::ColourValue::White, Ogre::ColourValue::Red);
	emitter->setPosition(Ogre::Vector3(5.7, 0, 0));
	
	
	this->billboardChain = thrusters;
	this->node->attachObject(this->billboardChain);
	
}

Laser::~Laser()
{
    delete this->timerLife;
    this->signalDestruction.dispatch();
}

void Laser::updatePosition(void)
{
    
    //~ if(this->timerLife->getMilliseconds() > GestLaser::timeLife)
    //~ {
        //~ delete this;
    //~ }
    //~ else
    //~ {
		this->moveRelative(0.0, 0.0, GestLaser::speedLaserBase);
	//~ }    
}


void Laser::move(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z)
{
	Ogre::Vector3 pos = this->getPosition();
	this->setPosition(pos[0]+x, pos[1]+y, pos[2]+z);
}

void Laser::move(const Ogre::Vector3 &vec)
{
	Ogre::Vector3 pos = this->getPosition() + vec;
	this->setPosition(pos[0], pos[1], pos[2]);
}

void Laser::moveRelative(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z)
{
	Ogre::Vector3 vec = Ogre::Vector3(x, y, z);
	this->moveRelative(vec);
}

void Laser::moveRelative(const Ogre::Vector3 &vec)
{
	Ogre::Vector3 trans = this->getOrientation() * vec;
	Ogre::Vector3 pos = this->getPosition() + trans;
	this->setPosition(pos[0], pos[1], pos[2]);
}

//Getter-Setter




Ogre::Quaternion Laser::getOrientation(void) 
{
	return this->getNode()->getOrientation();
}

void Laser::setOrientation(const Ogre::Quaternion &q)
{
	this->getNode()->setOrientation(q);
}

void Laser::setOrientation(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z, const Ogre::Real a) 
{
	this->getNode()->setOrientation(x, y, z, a);
}


Ogre::Vector3 Laser::getPosition(void)
{
    return this->getNode()->getPosition();   
}

void Laser::setPosition(const Ogre::Vector3 &v)
{
    this->getNode()->setPosition(v);
}

void Laser::setPosition(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z)
{
    this->getNode()->setPosition(x, y, z);
}

