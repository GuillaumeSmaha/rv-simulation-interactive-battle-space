#include "Asteroid.h"

using namespace Ogre;

Asteroid::Asteroid(void) : speed(0), rotationSpeed(0)
{
    this->entity = MeshLoader::getSingleton()->getNodedEntity(MeshLoader::ASTEROID);
    this->getNode()->setPosition(0, 0, 0);
}

Asteroid::~Asteroid(void)
{

}

Quaternion Asteroid::getOrientation(void) 
{
	return this->getNode()->getOrientation();
}
void Asteroid::setOrientation(Ogre::Quaternion  q)
{
	this->getNode()->setOrientation(q);
}
void Asteroid::setOrientation(Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Real a) 
{
	this->getNode()->setOrientation(x,y,z,a);
}

Ogre::Real Asteroid::getSpeed(void)
{
	return this->speed;
}
void Asteroid::setSpeed (Ogre::Real speed) 
{
	this->speed = speed;
}

Ogre::Real Asteroid::getRotationSpeed(void) 
{
	return this->rotationSpeed;
}
void Asteroid::setRotationSpeed (Ogre::Real rotationSpeed) 
{
	this->rotationSpeed = rotationSpeed;
}

Ogre::Vector3 Asteroid::getPosition(void)
{
    return this->getNode()->getPosition();   
}
void Asteroid::setPosition(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z)
{
    this->getNode()->setPosition(x, y, z);
}

void Asteroid::move(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z)
{
	Vector3 pos = this->getPosition();
	this->setPosition(pos[0]+x, pos[1]+y, pos[2]+z);
}
void Asteroid::move(const Ogre::Vector3 &vec)
{
	Vector3 pos = this->getPosition() + vec;
	this->setPosition(pos[0], pos[1], pos[2]);
}

void Asteroid::moveRelative(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z)
{
	Ogre::Vector3 vec = Ogre::Vector3(x, y, z);
	this->moveRelative(vec);
}
void Asteroid::moveRelative(const Ogre::Vector3 &vec)
{
	Vector3 trans = this->getOrientation() * vec;
	Vector3 pos = this->getPosition() + trans;
	this->setPosition(pos[0], pos[1], pos[2]);
}

void Asteroid::updatePosition(void)
{
	Vector3 position = this->getPosition();
	if (this->rotationSpeed != 0) 
	{
		this->setSpeed(this->getSpeed()+this->rotationSpeed);
		this->rotationSpeed = 0;
	}
	if (this->speed != 0) 
	{
		this->moveRelative(0.0, 0.0, this->getSpeed());
	}
}
