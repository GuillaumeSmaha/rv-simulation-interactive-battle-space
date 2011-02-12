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
        //std::cout<<(*itShip)->getSpeed()<<std::endl;
        (*itShip)->updatePosition();
    }
}

void GestShip::deleteAllShips()
{
    vector<Ship*>::iterator itShip;
    for(itShip=lstShip.begin(); itShip<lstShip.end();itShip++){
        delete (*itShip);
    }
}


