#include "GroupAsteroid.h"

using namespace std;

GroupAsteroid::GroupAsteroid(){
   lstGroupAsteroid.clear();
}

GroupAsteroid::~GroupAsteroid()
{
}

void GroupAsteroid::addAsteroid(Asteroid * asteroid)
{
    lstGroupAsteroid.push_back(asteroid);
}


void GroupAsteroid::updateGroupAsteroids()
{
    vector<Asteroid *>::iterator itAsteroid;
    for(itAsteroid=lstGroupAsteroid.begin(); itAsteroid<lstGroupAsteroid.end();itAsteroid++)
	{
        (*itAsteroid)->updatePosition();
    }
}

void GroupAsteroid::deleteAllGroupAsteroids()
{
    vector<Asteroid*>::iterator itAsteroid;
    for(itAsteroid=lstGroupAsteroid.begin(); itAsteroid<lstGroupAsteroid.end();itAsteroid++)
	{
        delete (*itAsteroid);
    }
}


