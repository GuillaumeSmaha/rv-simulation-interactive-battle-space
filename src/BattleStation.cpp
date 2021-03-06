#include "BattleStation.h"
#include <OgreNode.h>
#include "GestShip.h"
using namespace Ogre;

BattleStation::BattleStation(void) : ShipAbstract(ObjectRoot::SHIP_BATTLE_STATION)
{
    this->typeObject = ObjectRoot::SHIP_BATTLE_STATION;
    this->setShipLife(250);
    this->setShipLifeMax(250);
    this->speed = 0.4;
    this->mRotFrames = 10000;
    this->destination = Ogre::Vector3(130,0,9000);
    mRotating = true;
    mRotFactor = 1;
    mRotProgress = 1;
    
	this->setColorLaser(Ogre::ColourValue::Green);
	
    this->getNode()->setScale(Ogre::Vector3(0.1,0.1,0.1));
}

BattleStation::~BattleStation(void)
{

}

void BattleStation::updatePosition(void)
{
    Ogre::Vector3 direction = this->getNode()->_getDerivedPosition()-this->destination;
    //commenté pke bouffeur de FPS = les particules ne meurent pas
        
    if(direction.squaredLength()<40000000)
    {
		if(!this->getIsDead())
			this->shootLaser();
    }

    //Se tourne vers nous plus ou moins (mRotFactor == vitesse à laquelle c fait et avant que le vsx change de destination => inversement proportionnel)
		if(mRotating)
		{
			mRotProgress += mRotFactor;
			if(mRotProgress>1)
			{
				int iRand = Utils::randRangeInt(0, GestShip::getSingleton()->getAllShips(ObjectRoot::SHIP_IA).size()-1);
				this->destination = GestShip::getSingleton()->getAllShips(ObjectRoot::SHIP_IA).at(iRand)->getNode()->_getDerivedPosition()+Ogre::Vector3(Utils::randRangeInt(-10000,10000),Utils::randRangeInt(-10000,10000),Utils::randRangeInt(-10000,10000));
				mRotating = false;
				mRotating = true;
				mRotFactor = 1.0f / mRotFrames;
				mOrientSrc = this->getNode()->getOrientation();
				Ogre::Quaternion quat =  (this->getNode()->getOrientation()* Vector3::UNIT_Z).getRotationTo(    this->destination-this->getNode()->_getDerivedPosition());
				mOrientDest = quat * mOrientSrc;           // We want dest orientation, not a relative rotation (quat)
				mRotProgress = 0;
			}
			else
			{
				//rotation
				Quaternion delta = Quaternion::Slerp(mRotProgress, mOrientSrc, mOrientDest, true);
				this->getNode()->setOrientation(delta);
			}
		}
        //si on est encore loin on avance
        if(direction.squaredLength()>4000000)
        {
            this->setSpeed(speed);

        }else{
            this->setSpeed(0);
        }
             if (this->getSpeed() != 0)
            {
                this->moveRelative(0.0, 0.0, this->getSpeed());
            }
        //TODO:peut etre translaté tjs tout droit par rapport à lui meme et on corrige l'orientation du vsx = effet plus smoothy je pense
   /* }else
    {
        mRotating = true;
        mRotFactor = 1.0f / 10;
        mOrientSrc = this->getNode()->getOrientation();
        Ogre::Quaternion quat =  (this->getNode()->getOrientation()* Vector3::UNIT_X).getRotationTo( GestShip::getSingleton()->getAllShips().at(0)->getNode()->_getDerivedPosition());
        mOrientDest = quat * mOrientSrc;           // We want dest orientation, not a relative rotation (quat)
        mRotProgress = 0;
        /*
        Ogre::Vector3 dir = Ogre::Vector3(Utils::randRangeInt(0,10000),Utils::randRangeInt(0,10000),Utils::randRangeInt(0,10000));
        dir.normalise();
        this->destination = GestShip::getSingleton()->getAllShips().at(0)->getNode()->_getDerivedPosition()+dir*1000;
        */
   // }
/*
	if (this->getAcceleration() != 0)
	{
		this->setSpeed(this->getSpeed()+this->getAcceleration());
		this->setAcceleration(0);
	}
	if (this->getSpeed() != 0)
	{
		this->moveRelative(0.0, 0.0, this->getSpeed());
	}*/
}
