#include "ShipPlayer.h"

using namespace Ogre;

ShipPlayer::ShipPlayer(PlayerControls * pControl) : ShipAbstract()
{
   pControl->signalKeyPressed.add(&ShipPlayer::keyPressed, this);
}

ShipPlayer::~ShipPlayer(void)
{

}



void ShipPlayer::keyPressed(PlayerControls::Controls key)
{
    Quaternion r(Degree(90), Vector3::UNIT_X);
    Quaternion orientation;
    switch(key)
	{
		case PlayerControls::ACCELERATION :
            this->accelerate(1);
            break;
        case PlayerControls::BRAKE:
            this->accelerate(-1);
            break;
        case PlayerControls::LEFT :
            this->rollAccelerate(Ogre::Radian(0.001));
            break;
        case PlayerControls::RIGHT :
            this->rollAccelerate(Ogre::Radian(-0.001));
            break;
        case PlayerControls::UP :
            this->pitchAccelerate(Ogre::Radian(0.001));
            break;
            case PlayerControls::DOWN :
            this->pitchAccelerate(Ogre::Radian(-0.001));
		default:
			break;
	}
}
