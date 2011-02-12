#include "GestShip.h"

using namespace std;

GestShip::GestShip(){
   lstShip.clear();
}

GestShip::~GestShip()
{
}

void GestShip::addShip(Ship * ship)
{
    lstShip.push_back(ship);
}


void GestShip::updateShips()
{
    vector<Ship *>::iterator itShip;
    for(itShip=lstShip.begin(); itShip<lstShip.end();itShip++){
        (*itShip)->updatePosition();
		if ((*itShip)->getSpeed()<1)
		{
			(*itShip)->setSpeed((*itShip)->getSpeed()+1);
		}
		(*itShip)->updatePosition();
		//std::cout<<(*itShip)->getSpeed()<<std::endl;
    }
}

void GestShip::deleteAllShips()
{
    vector<Ship*>::iterator itShip;
    for(itShip=lstShip.begin(); itShip<lstShip.end();itShip++){
        delete (*itShip);
    }
}


