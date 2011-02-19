#include "Asteroid.h"

using namespace Ogre;

int q1=1;
int toggle=0;

Asteroid::Asteroid(void) : speed(0), rotationSpeed(0.1)
{
    this->entity = MeshLoader::getSingleton()->getNodedEntity(MeshLoader::ASTEROID);
	this->getNode()->setOrientation(0.5, 2, 2, 1);
	this->getNode()->setScale(10,10,10);
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
	if (this->getRotationSpeed() >0 && this->getRotationSpeed() <1)  
	{
		Ogre::Real quat1= Ogre::Real(this->getOrientation()[0]+q1*this->getRotationSpeed()/10);
		Ogre::Real quat2= Ogre::Real(this->getOrientation()[1]);
		Ogre::Real quat3= Ogre::Real(this->getOrientation()[2]);
		Ogre::Real quat4= Ogre::Real(this->getOrientation()[3]);
		//Utils::log(Ogre::Real(this->getOrientation()[3]));
		if (quat1>1 && toggle==0)
		{
			toggle=1;
			q1=-1;
			quat1=1;
			quat2=-quat2;
			quat3=-quat3;
			quat4=-quat4;
			Utils::log("quat1:");
			Utils::log(quat1);
		}
		if (quat1<0.01 && toggle==1)
		{
			toggle=0;
			q1=1;
			quat1=0;
			quat2=-quat2;
			quat3=-quat3;
			quat4=-quat4;
			Utils::log("quat1:");
			Utils::log(quat1);
		}
		this->setOrientation(quat1, quat2, quat3, quat4);
	}
	if (this->speed != 0) 
	{
		this->moveRelative(0.0, 0.0, this->getSpeed());
	}
}
