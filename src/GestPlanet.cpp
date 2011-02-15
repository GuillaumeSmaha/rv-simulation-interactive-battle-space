#include "GestPlanet.h"

using namespace std;

GestPlanet::GestPlanet(){
   lstPlanet.clear();
}

GestPlanet::~GestPlanet()
{
}

void GestPlanet::addPlanet(Planet * planet)
{
    lstPlanet.push_back(planet);
}


void GestPlanet::updatePlanet()
{
    vector<Planet *>::iterator itPlanet;
    for(itPlanet=lstPlanet.begin(); itPlanet<lstPlanet.end();itPlanet++)
	{
        (*itPlanet)->updatePosition();
	}
}

void GestPlanet::deleteAllPlanet()
{
    vector<Planet *>::iterator itPlanet;
    for(itPlanet=lstPlanet.begin(); itPlanet<lstPlanet.end();itPlanet++)
	{
        delete (*itPlanet);
    }
}
