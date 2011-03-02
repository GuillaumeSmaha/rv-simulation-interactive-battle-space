#include "GestLaser.h"

using namespace std;

Ogre::Real GestLaser::speedLaserBase = 250.0;
Ogre::Real GestLaser::timeLife = 5000.0;

GestLaser * GestLaser::_instance = NULL;

GestLaser * GestLaser::getSingleton(void)
{
	if (_instance == NULL)
	{
		_instance = new GestLaser();
	}
	return _instance;
}

GestLaser::GestLaser()
{
	if (_instance == NULL)
	{
		_instance = this;
	}
}

GestLaser::~GestLaser()
{
    this->listLasers.clear();
}

Laser * GestLaser::create(const Ogre::Vector3 &position, const Ogre::Quaternion &orientation, const Ogre::ColourValue &color)
{
	Laser * laser = new Laser(position, orientation, color);
	
    this->add(laser);
    
    return laser;
}

void GestLaser::add(Laser * laser)
{
    this->listLasers.push_back(laser);
    laser->signalDestruction.add(&GestLaser::remove, this);
}

void GestLaser::remove(Laser * laser)
{
	for(unsigned int i = 0 ; i < this->listLasers.size() ; i++)
	{
		if(this->listLasers[i] == laser)
		{
			this->listLasers.erase(this->listLasers.begin()+i);
			break;
		}
	}
}

void GestLaser::updateLasers(void *)
{
    vector<Laser *>::iterator itLaser;
    
    for(itLaser = this->listLasers.begin(); itLaser < this->listLasers.end() ; itLaser++)
    {
		if((*itLaser)->isAlive())
		{
			(*itLaser)->updatePosition();
		}
		else
		{
			delete (*itLaser);
		}
    }
}

void GestLaser::deleteAll()
{
    vector<Laser *>::iterator itLaser;
    for(itLaser = this->listLasers.begin(); itLaser < this->listLasers.end() ; itLaser++)
    {
        delete (*itLaser);
    }
}

void GestLaser::destroy()
{
    if(_instance != NULL)
    {
        delete _instance;
    }
}
