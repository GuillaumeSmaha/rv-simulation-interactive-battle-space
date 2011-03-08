#include "Laser.h"

using namespace std;


Laser::Laser(const Ogre::Vector3 &position, const Ogre::Quaternion &orientation, const Ogre::ColourValue &color) : position(position), orientation(orientation)
{
	//~ this->typeObject = ObjectRoot::LASER;
	this->timerLife = new Ogre::Timer();
		
    this->particule = static_cast<Ogre::ParticleSystem *>(MeshLoader::getSingleton()->getNodedMovableObject(MeshLoader::LASER));
	this->particule->getEmitter(0)->setColour(color);
    
	this->getNode()->_setDerivedPosition(position);
	this->getNode()->_setDerivedOrientation(orientation);
	
	
}

Laser::~Laser()
{
	this->signalDestruction.dispatch(this);
    delete this->timerLife;
	MeshLoader::getSingleton()->deleteNodedObject(MeshLoader::LASER, this->getEntity());
}

void Laser::updatePosition(void)
{
	this->moveRelative(0.0, 0.0, GestLaser::speedLaserBase);
}

bool Laser::isAlive()
{
    
    if(this->timerLife->getMilliseconds() > GestLaser::timeLife)
    {
		return false;
    }
    
    return true;
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

void Laser::exploded(void)
{
}
