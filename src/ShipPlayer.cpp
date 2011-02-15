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
    std::cout<<"vitesse"<<this->getRollSpeed()<<std::endl;
    std::cout<<"acceleration"<<this->getRollAcceleration()<<std::endl;
	Vector3 position = this->getPosition();
    //calcule des nouvelles vitesses et positions
    this->setSpeed(this->getSpeed()+this->getAcceleration());
	if (this->getSpeed() != 0)
	{
		this->moveRelative(0.0, 0.0, this->getSpeed());
	}
    this->setRollSpeed(this->getRollSpeed()+this->getRollAcceleration());
    this->rotateRelative(this->getRollSpeed());

    this->setPitchSpeed(this->getPitchSpeed()+this->getPitchAcceleration());
    this->goUp(this->getPitchSpeed());

    //on réduit chacune des accélération
    this->setAcceleration(0);
    this->setPitchAcceleration(Ogre::Radian(0));
    this->setRollAcceleration(Ogre::Radian(0));

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
