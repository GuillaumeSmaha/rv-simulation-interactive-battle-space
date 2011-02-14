#include "ShipIA.h"

using namespace Ogre;

ShipIA::ShipIA(void) : ShipAbstract()
{

}

ShipIA::~ShipIA(void)
{

}

void ShipIA::updatePosition(void)
{
	Vector3 position = this->getPosition();
	if (this->getAcceleration() != 0) 
	{
		this->setSpeed(this->getSpeed()+this->getAcceleration());
		this->setAcceleration(0);
	}
	if (this->getSpeed() != 0) 
	{
		this->moveRelative(0.0, 0.0, this->getSpeed());
	}
}
