#include "GestGroupAsteroids.h"
GestGroupAsteroids* GestGroupAsteroids::_instance = NULL;
using namespace std;

GestGroupAsteroids::GestGroupAsteroids()
{
    if(_instance == NULL)
    {
        _instance= this;
    }
   lstGroupAsteroids.clear();
}

GestGroupAsteroids::~GestGroupAsteroids()
{
    lstGroupAsteroids.clear();
}
GestGroupAsteroids * GestGroupAsteroids::getSingleton(void)
{
    if(_instance == NULL)
    {

        _instance = new GestGroupAsteroids();
    }
    return _instance;
}
void GestGroupAsteroids::addGroupAsteroids(GroupAsteroid * groupAsteroid)
{
    lstGroupAsteroids.push_back(groupAsteroid);
}


void GestGroupAsteroids::updateGroupsAsteroids(void*)
{
    vector<GroupAsteroid *>::iterator itGroupAsteroid;
    for(itGroupAsteroid=lstGroupAsteroids.begin(); itGroupAsteroid<lstGroupAsteroids.end();itGroupAsteroid++)
	{
        (*itGroupAsteroid)->updateGroupAsteroids();
	}
}

void GestGroupAsteroids::deleteAllGroupsAsteroids()
{
    vector<GroupAsteroid*>::iterator itGroupAsteroids;
    for(itGroupAsteroids=lstGroupAsteroids.begin(); itGroupAsteroids<lstGroupAsteroids.end();itGroupAsteroids++)
	{
        delete (*itGroupAsteroids);
    }
}

void GestGroupAsteroids::destroy()
{
    if(_instance != NULL)
    {
        delete _instance;
    }
}
