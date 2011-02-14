#include "ShipPlayer.h"

using namespace Ogre;

ShipPlayer::ShipPlayer(PlayerControls * pControl) : ShipAbstract()
{
   pControl->signalKeyPressed.add(&ShipPlayer::keyPressed, this);
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

void ShipPlayer::keyPressed(PlayerControls::Controls key)
{
    Quaternion r(Degree(90), Vector3::UNIT_X);
    Quaternion orientation;
    switch(key)
	{
		case PlayerControls::ACCELERATION :
            //std::cout<<"shoot";
            this->setAcceleration(15);
        break;
        case PlayerControls::LEFT :
            orientation = this->getOrientation();

            //orientation = orientation * r;
            this->setOrientation(orientation* r);
        break;
		default:
			break;
	}
}
