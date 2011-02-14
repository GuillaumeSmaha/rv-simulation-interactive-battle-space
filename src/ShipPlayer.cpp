#include "ShipPlayer.h"

using namespace Ogre;

ShipPlayer::ShipPlayer(void) : ShipAbstract()
{
    
}

ShipPlayer::~ShipPlayer(void)
{

}

void ShipPlayer::updatePosition(void)
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
