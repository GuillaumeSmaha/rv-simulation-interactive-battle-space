#include "GestLaser.h"

using namespace std;

Ogre::Real GestLaser::speedLaserBase = 250.0;
Ogre::Real GestLaser::timeLife = 2500.0;

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
    vector<Laser *>::iterator itLaser = listLasers.begin();
    
	while (itLaser != this->listLasers.end())
    {
		if(!(*itLaser)->isAlive())
		{
			itLaser = this->listLasers.erase(itLaser);
		}
		else
		{
			(*itLaser)->updatePosition();
			itLaser++;
		}
    }
}

void GestLaser::deleteAll()
{
	vector<Laser *>::iterator itLaser = this->listLasers.begin();
	while (itLaser != listLasers.end())
    {
		itLaser = this->listLasers.erase(itLaser);
    }
}

void GestLaser::destroy()
{
    if(_instance != NULL)
    {
        delete _instance;
    }
}
