#include "Planet.h"

using namespace Ogre;

Planet::Planet(void)
{
	this->entity = MeshLoader::getSingleton()->getNodedEntity(MeshLoader::PLANET);
    this->getNode()->setPosition(150, 100, -100);
}

Planet::Planet(Ogre::int16 _type) : type(_type)
{
	//Choix de types de planètes 
	switch(type)
	{
		case 1 : this->entity = MeshLoader::getSingleton()->getNodedEntity(MeshLoader::PLANET); break;
		case 2 : this->entity = MeshLoader::getSingleton()->getNodedEntity(MeshLoader::PLANET2); break;
		case 3 : this->entity = MeshLoader::getSingleton()->getNodedEntity(MeshLoader::PLANET3); break;
		case 4 : this->entity = MeshLoader::getSingleton()->getNodedEntity(MeshLoader::PLANET4); break;
		case 5 : this->entity = MeshLoader::getSingleton()->getNodedEntity(MeshLoader::PLANET5); break;
		case 6 : this->entity = MeshLoader::getSingleton()->getNodedEntity(MeshLoader::PLANET6); break;
		case 7 : this->entity = MeshLoader::getSingleton()->getNodedEntity(MeshLoader::PLANET7); break;
		case 8 : this->entity = MeshLoader::getSingleton()->getNodedEntity(MeshLoader::PLANET8); break;
	}
	this->getNode()->setPosition(150, 100, -100);
}

Planet::~Planet(void)
{

}

void Planet::setPosition(Ogre::Real x, Ogre::Real y, Ogre::Real z)
{
    this->getNode()->setPosition(x, y, z);
}

