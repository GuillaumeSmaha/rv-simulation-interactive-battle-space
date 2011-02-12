#include "Ship.h"

using namespace Ogre;

Ship::Ship(void) : shipLife(100)
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
int Ship::getShipLife()
{
	return this->shipLife;
}


void Ship::setOrientation(Ogre::Quaternion  q)
{
	this->getNode()->setOrientation(q);
}

void Ship::setOrientation(Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Real a) 
{
	this->getNode()->setOrientation(x,y,z,a);
}

Quaternion Ship::getOrientation() 
{
	return this->getNode()->getOrientation();
}

void Ship::setSpeed (Ogre::Real speed) 
{
	this->speed = speed;
}
void Ship::setAcceleration (Ogre::Real acceleration) 
{
	this->acceleration = acceleration;
}
Ogre::Real Ship::getSpeed() {
	return this->speed;
}
Ogre::Real Ship::getAcceleration() 
{
	return this->acceleration;
}

void Ship::setPosition(Ogre::Real x, Ogre::Real y, Ogre::Real z)
{
    this->getNode()->setPosition(x, y, z);
}


Ogre::Vector3 Ship::getPosition()
{
    return this->getNode()->getPosition();   
}

void Ship::touched(void)
{
   MeshLoader::getSingleton()->setMaterial(this->entity, MeshLoader::SHIP_TOUCHED);
}

void Ship::updatePosition()
{
    
    /*TODO*/
}

