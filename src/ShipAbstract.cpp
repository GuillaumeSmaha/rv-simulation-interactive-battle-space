#include "ShipAbstract.h"

using namespace Ogre;

ShipAbstract::ShipAbstract(void) : shipLife(100), speed(0), acceleration(0)
{
    this->entity = MeshLoader::getSingleton()->getNodedEntity(MeshLoader::SHIP);
    this->getNode()->setPosition(0, 0, 0);
    //this->node->getAttachedObject(this->getName())-setMaterialName("razor");
    
    this->defineParticules();
}

ShipAbstract::~ShipAbstract(void)
{

}

void ShipAbstract::touched(void)
{
   MeshLoader::getSingleton()->setMaterial(this->entity, MeshLoader::SHIP_TOUCHED);
}

void ShipAbstract::defineParticules(void)
{
    Ogre::ParticleSystem* thrusters = MeshLoader::getSingleton()->getSceneManager()->createParticleSystem(25);
    thrusters->setMaterialName("Reactor");
    thrusters->setDefaultDimensions(25, 25);

	// Création de 2 émetteurs pour le système de particules
	for (unsigned int i = 0; i < 2; i++)
	{
		Ogre::ParticleEmitter * emitter = thrusters->addEmitter("Point");

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


void ShipAbstract::move(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z)
{
	Vector3 pos = this->getPosition();
	this->setPosition(pos[0]+x, pos[1]+y, pos[2]+z);
}

void ShipAbstract::move(const Ogre::Vector3 &vec)
{
	Vector3 pos = this->getPosition() + vec;
	this->setPosition(pos[0], pos[1], pos[2]);
}


void ShipAbstract::moveRelative(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z)
{
	Ogre::Vector3 vec = Ogre::Vector3(x, y, z);
	this->moveRelative(vec);
}

void ShipAbstract::moveRelative(const Ogre::Vector3 &vec)
{
	Vector3 trans = this->getOrientation() * vec;
	Vector3 pos = this->getPosition() + trans;
	this->setPosition(pos[0], pos[1], pos[2]);
}

//Getter-Setter

int ShipAbstract::getShipLife(void)
{
	return this->shipLife;
}

void ShipAbstract::setShipLife(int shipLife)
{
	this->shipLife = shipLife;
}


int ShipAbstract::getShipLifeMax(void)
{
	return this->shipLifeMax;
}

void ShipAbstract::setShipLifeMax(int shipLife)
{
	this->shipLifeMax = shipLifeMax;
}


Ogre::Real ShipAbstract::getSpeed(void)
{
	return this->speed;
}

void ShipAbstract::setSpeed(const Ogre::Real speed) 
{
	this->speed = speed;
}


Ogre::Real ShipAbstract::getAcceleration(void) 
{
	return this->acceleration;
}

void ShipAbstract::setAcceleration(const Ogre::Real acceleration) 
{
	this->acceleration = acceleration;
}


Quaternion ShipAbstract::getOrientation(void) 
{
	return this->getNode()->getOrientation();
}

void ShipAbstract::setOrientation(const Ogre::Quaternion &q)
{
	this->getNode()->setOrientation(q);
}

void ShipAbstract::setOrientation(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z, const Ogre::Real a) 
{
	this->getNode()->setOrientation(x, y, z, a);
}


Ogre::Vector3 ShipAbstract::getPosition(void)
{
    return this->getNode()->getPosition();   
}

void ShipAbstract::setPosition(const Ogre::Vector3 &v)
{
    this->getNode()->setPosition(v);
}

void ShipAbstract::setPosition(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z)
{
    this->getNode()->setPosition(x, y, z);
}
