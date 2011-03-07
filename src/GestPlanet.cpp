#include "GestPlanet.h"

using namespace std;

GestPlanet* GestPlanet::_instance = NULL;

GestPlanet* GestPlanet::getSingleton(void)
{
	if (_instance == NULL)
	{
		_instance = new GestPlanet();
	}
	return _instance;
}


GestPlanet::GestPlanet()
{
	if (_instance == NULL)
	{
		//lstPlanet.clear();
		_instance = this;
	}
}

GestPlanet::~GestPlanet()
{
	lstPlanet.clear();
}

void GestPlanet::addPlanet(Planet * planet)
{
    lstPlanet.push_back(planet);
}


void GestPlanet::updatePlanet(const Ogre::FrameEvent &evt)
{
    vector<Planet *>::iterator itPlanet;
    for(itPlanet=lstPlanet.begin(); itPlanet<lstPlanet.end();itPlanet++)
	{
		(*itPlanet)->update();
	}
}

void GestPlanet::deleteAllPlanet()
{
    vector<Planet *>::iterator itPlanet = lstPlanet.begin();
    //for(itPlanet=lstPlanet.begin(); itPlanet<lstPlanet.end();itPlanet++)
	while (itPlanet != lstPlanet.end())
	{
        //delete (*itPlanet);
		itPlanet = lstPlanet.erase(itPlanet);
    }
}

void GestPlanet::destroy()
{
    if(_instance != NULL)
    {
        delete _instance;
    }
}
