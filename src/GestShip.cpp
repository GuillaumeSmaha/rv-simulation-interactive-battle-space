#include "GestShip.h"

using namespace std;

GestShip* GestShip::_instance = NULL;

GestShip* GestShip::getSingleton(void)
{
	if (_instance == NULL)
	{
		_instance = new GestShip();
	}
	return _instance;
}

GestShip::GestShip()
{
	if (_instance == NULL)
	{
		_instance = this;
	}
}

GestShip::~GestShip()
{
    lstShip.clear();
}

void GestShip::addShip(ShipAbstract * ship)
{
    lstShip.push_back(ship);
    ship->signalDestruction.add(&GestShip::remShip, this);
}

void GestShip::remShip(ShipAbstract * ship)
{
	for(unsigned int i = 0 ; i < lstShip.size() ; i++)
	{
		if(lstShip[i]==ship)
		{
			lstShip.erase(lstShip.begin()+i);
			break;
		}
	}
}

void GestShip::updateShips(void *)
{
    vector<ShipAbstract *>::iterator itShip;
    for(itShip=lstShip.begin(); itShip<lstShip.end();itShip++)
    {
        (*itShip)->updatePosition();
    }
}

void GestShip::deleteAllShips()
{
	//Utils::logFile("kill hsips");
    vector<ShipAbstract *>::iterator itShip = lstShip.begin();
    //for(itShip=lstShip.begin(); itShip<lstShip.end();itShip++)
	while(itShip != lstShip.end())
    {
        //delete (*itShip);
		itShip = lstShip.erase(itShip);
    }
}

void GestShip::destroy()
{
    if(_instance != NULL)
    {
        delete _instance;
    }
}

void GestShip::resetPosAllShips()
{
    vector<ShipAbstract *>::iterator itShip;
    for(itShip=lstShip.begin(); itShip<lstShip.end();itShip++)
    {
        (*itShip)->reset();
    }
}

