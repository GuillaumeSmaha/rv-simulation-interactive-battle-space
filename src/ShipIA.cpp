#include "ShipIA.h"
#include <OgreNode.h>
#include "GestShip.h"

using namespace Ogre;


ShipIA::ShipIA(void) : ShipAbstract(ObjectRoot::SHIP_IA)
{
    this->typeObject = ObjectRoot::SHIP_IA;
    this->speed = 30;
    this->setShipLife(30);
    this->setShipLifeMax(30);
    this->target = Utils::randRangeInt(0,GestShip::getSingleton()->getAllShips(ObjectRoot::SHIP_BATTLE_STATION).size()+GestShip::getSingleton()->getAllShips(ObjectRoot::SHIP_PLAYER).size()-1);//0;
    this->mRotFrames = 100;
    this->destination = Ogre::Vector3(130,0,9000);
    mRotating = true;
    mRotFactor = 1;
    mRotProgress = 1;
    
	this->setColorLaser(Ogre::ColourValue::Red);
}

ShipIA::~ShipIA(void)
{

}

void ShipIA::updatePosition(void)
{
    Ogre::Vector3 direction = this->getNode()->_getDerivedPosition()-this->destination;
    ShipAbstract * targetShip;
    
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
				if(Utils::randRangeInt(0,100) == 42 || GestShip::getSingleton()->getAllShips(ObjectRoot::SHIP_BATTLE_STATION).size()+GestShip::getSingleton()->getAllShips(ObjectRoot::SHIP_PLAYER).size()<=target)
				{
					target = Utils::randRangeInt(0, GestShip::getSingleton()->getAllShips(ObjectRoot::SHIP_BATTLE_STATION).size()+GestShip::getSingleton()->getAllShips(ObjectRoot::SHIP_PLAYER).size()-1);
				}

				if(target < GestShip::getSingleton()->getAllShips(ObjectRoot::SHIP_PLAYER).size())
				{
					targetShip = GestShip::getSingleton()->getAllShips(SHIP_PLAYER).at(target);
				}
				else
				{
					targetShip = GestShip::getSingleton()->getAllShips(SHIP_BATTLE_STATION).at(target- GestShip::getSingleton()->getAllShips(ObjectRoot::SHIP_PLAYER).size());
				}


				this->destination = targetShip->getNode()->_getDerivedPosition()+Ogre::Vector3(Utils::randRangeInt(-10000,10000),Utils::randRangeInt(-10000,10000),Utils::randRangeInt(-10000,10000));
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
