#include "GestShip.h"
#include "Utils.h"
using namespace std;

GestShip::GestShip()
{
   lstShip.clear();
}

GestShip::~GestShip()
{
}

void GestShip::addShip(ShipAbstract * ship)
{
    lstShip.push_back(ship);
}


void GestShip::updateShips()
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
    vector<ShipAbstract *>::iterator itShip;
    for(itShip=lstShip.begin(); itShip<lstShip.end();itShip++)
    {
        delete (*itShip);
    }
}


