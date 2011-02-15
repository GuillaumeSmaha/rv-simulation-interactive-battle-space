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
            this->setAcceleration(15);
            break;
        case PlayerControls::BRAKE:
            this->setAcceleration(-15);
            break;
        case PlayerControls::LEFT :
            this->rotateRelative(Ogre::Radian(0.2));
            break;
        case PlayerControls::RIGHT :
            this->rotateRelative(Ogre::Radian(-0.2));
            break;
        case PlayerControls::UP :
            this->goUp(Ogre::Radian(0.2));
            break;
            case PlayerControls::DOWN :
            this->goUp(Ogre::Radian(-0.2));
		default:
			break;
	}
}
