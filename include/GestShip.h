#include <Ogre.h>
#include "Ship.h"

/***Permet de gérer une liste de vaiseau***/
class GestShip
{
    private:
        std::vector<Ship *> lstShip;

    public:
        GestShip();
        ~GestShip();
        void addShip(Ship * ship);
        std::vector<Ship> getAllShips();
        
        void updateShips();

        void deleteAllShips();
};
