#include "Ship.h"

using namespace Ogre;

Ship::Ship(void) : shipLife(100), speed(0), acceleration(0)
{
    this->entity = MeshLoader::getSingleton()->getNodedEntity(MeshLoader::SHIP);
    this->getNode()->setPosition(0, 0, 0);
    //this->node->getAttachedObject(this->getName())-setMaterialName("razor");

    //TODO:voir pour creer un MeshLoader::getParticleSystem
    Ogre::ParticleSystem* thrusters = MeshLoader::getSingleton()->getSceneManager()->createParticleSystem(25);
    thrusters->setMaterialName("Reactor");
    thrusters->setDefaultDimensions(25, 25);

	// Création de 2 émetteurs pour le système de particules
	for (unsigned int i = 0; i < 2; i++)
	{
		Ogre::ParticleEmitter * emitter = thrusters ->addEmitter("Point");

		// set the emitter properties
		emitter->setAngle(Ogre::Degree(3));
		emitter->setTimeToLive(0.5);
		emitter->setEmissionRate(25);
		emitter->setParticleVelocity(5);
		emitter->setDirection(Vector3::NEGATIVE_UNIT_Z);
		emitter->setColour(ColourValue::White, ColourValue::Red);
		emitter->setPosition(Ogre::Vector3(i == 0 ? 5.7 : -18, 0, 0));
	}
	//this->node->createChildSceneNode(Vector3(0, 6.5, -67))->attachObject(thrusters);
    this->getNode()->createChildSceneNode(Vector3(0, 6.5, -77))->attachObject(thrusters);
}

Ship::~Ship(void)
{

}

void Ship::setShipLife(int shipLife)
{
	this->shipLife = shipLife;
}
int Ship::getShipLife(void)
{
	return this->shipLife;
}

Quaternion Ship::getOrientation(void) 
{
	return this->getNode()->getOrientation();
}
void Ship::setOrientation(Ogre::Quaternion  q)
{
	this->getNode()->setOrientation(q);
}
void Ship::setOrientation(Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Real a) 
{
	this->getNode()->setOrientation(x,y,z,a);
}

Ogre::Real Ship::getSpeed(void)
{
	return this->speed;
}
void Ship::setSpeed (Ogre::Real speed) 
{
	this->speed = speed;
}

Ogre::Real Ship::getAcceleration(void) 
{
	return this->acceleration;
}
void Ship::setAcceleration (Ogre::Real acceleration) 
{
	this->acceleration = acceleration;
}

Ogre::Vector3 Ship::getPosition(void)
{
    return this->getNode()->getPosition();   
}
void Ship::setPosition(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z)
{
    this->getNode()->setPosition(x, y, z);
}

void Ship::move(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z)
{
	Vector3 pos = this->getPosition();
	this->setPosition(pos[0]+x, pos[1]+y, pos[2]+z);
}
void Ship::move(const Ogre::Vector3 &vec)
{
	Vector3 pos = this->getPosition() + vec;
	this->setPosition(pos[0], pos[1], pos[2]);
}

void Ship::moveRelative(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z)
{
	Ogre::Vector3 vec = Ogre::Vector3(x, y, z);
	this->moveRelative(vec);
}
void Ship::moveRelative(const Ogre::Vector3 &vec)
{
	Vector3 trans = this->getOrientation() * vec;
	Vector3 pos = this->getPosition() + trans;
	this->setPosition(pos[0], pos[1], pos[2]);
}

void Ship::updatePosition(void)
{
	Vector3 position = this->getPosition();
	if (this->acceleration != 0) 
	{
		this->setSpeed(this->getSpeed()+this->acceleration);
		this->acceleration = 0;
	}
	if (this->speed != 0) 
	{
		this->moveRelative(0.0, 0.0, this->getSpeed());
	}
}

void Ship::touched(void)
{
   MeshLoader::getSingleton()->setMaterial(this->entity, MeshLoader::SHIP_TOUCHED);
}

