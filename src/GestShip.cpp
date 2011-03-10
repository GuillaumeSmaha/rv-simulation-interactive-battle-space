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
    switch(ship->getTypeObject())
    {
            case ObjectRoot::SHIP_IA:
                lstShipIA.push_back(ship);
            break;
            
            case ObjectRoot::SHIP_PLAYER:
                lstShipPlayer.push_back(ship);
            break;
            
            case ObjectRoot::SHIP_BATTLE_STATION:
                lstShipBattleStation.push_back(ship);
            break;
            
            default:
            break;
    }
}

void GestShip::remShip(ShipAbstract * ship)
{
	switch(ship->getTypeObject())
    {
            case ObjectRoot::SHIP_IA:
                for(unsigned int i = 0 ; i < lstShipIA.size() ; i++)
                {
                    if(lstShipIA[i]==ship)
                    {
                        lstShipIA.erase(lstShipIA.begin()+i);
                        break;
                    }
                }
            break;
            
            case ObjectRoot::SHIP_PLAYER:
               for(unsigned int i = 0 ; i < lstShipPlayer.size() ; i++)
                {
                    if(lstShipPlayer[i]==ship)
                    {
                        lstShipPlayer.erase(lstShipPlayer.begin()+i);
                        break;
                    }
                }
            break;
            
            case ObjectRoot::SHIP_BATTLE_STATION:
                for(unsigned int i = 0 ; i < lstShipBattleStation.size() ; i++)
                {
                    if(lstShipBattleStation[i]==ship)
                    {
                        lstShipBattleStation.erase(lstShipBattleStation.begin()+i);
                        break;
                    }
                }
            break;
            
            default:
            break;
    }
    
	for(unsigned int i = 0 ; i < lstShip.size() ; i++)
	{
		if(lstShip[i] == ship)
		{
			delete ship;
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
    vector<ShipAbstract *>::iterator itShip = lstShip.begin();
	while(itShip != lstShip.end())
    {
		delete *itShip;
		itShip = lstShip.erase(itShip);
    }
    
    lstShipIA.clear();
    lstShipPlayer.clear();
    lstShipBattleStation.clear();
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

