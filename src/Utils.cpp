#include "Utils.h"

int Utils::_count = 0;

int Utils::initialize(void)
{
	srand(time(NULL));
	return 0;
}

int Utils::randRangeInt(int min, int max)
{
    static bool init = false;
    if(init == false)
    {
        init = true;
        Utils::initialize();
    }
	return (int)((double)rand() / ((double)RAND_MAX + 1) * (max-min+1)+min);
}

int Utils::unique(void)
{
	return _count++;
}

void Utils::log(Ogre::String text)
{
	Ogre::LogManager::getSingletonPtr()->logMessage(text);
}
Ogre::String Utils::toString( int Value)
{

    // utiliser un flux de sortie pour créer la chaîne
    std::ostringstream oss;
    // écrire la valeur dans le flux
    oss << Value;
    // renvoyer une string
    return oss.str();
}
template <typename T>
Ogre::String Utils::toString( const T & Value )
{
    // utiliser un flux de sortie pour créer la chaîne
    std::ostringstream oss;
    // écrire la valeur dans le flux
    oss << Value;
    // renvoyer une string
    return oss.str();
}
