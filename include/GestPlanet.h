#include <Ogre.h>
#include "Planet.h"

class GestPlanet
{
    private:
        std::vector<Planet *> lstPlanet;

    public:
        GestPlanet();
        ~GestPlanet();
        void addPlanet(Planet * planet);
        std::vector<Planet> getAllPlanet();
        void updatePlanet();
        void deleteAllPlanet();
};
