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

void GestGroupAsteroids::createGroup(int nb, Ogre::Radian angleRotation, Ogre::Real rayon, Ogre::Vector3 centreRotation, Ogre::Real rotationSpeed) 
{
	int x;
	int y;
	Asteroid *asteroid1;	
	GroupAsteroid * groupAsteroid = new GroupAsteroid();
	for (x = rayon; x > 0; x=x-rayon/(nb/4)) //le 4 car on crée les asteroids 4 par 4
	{
		asteroid1 = new Asteroid();
	//normaliser le nb par rapport au x -> le rayon
		//(x - a)² + (y - b)² = r²
		//	Ou (a,b) sont les coordonnées du centre et r est le rayon. 
		//  tous les couples (x,y) qui vérifient l'équation sont des points du cercle.
		//-> si x fixé par le for :
		// on fait 4 asteroids à la fois:
		y =  Ogre::Math::Sqrt(rayon*rayon-x*x-centreRotation[0]*centreRotation[0]+2*x*centreRotation[0]);
		asteroid1->setPosition(centreRotation[0]+x,centreRotation[1]+y,centreRotation[2]);
		groupAsteroid->addAsteroid(asteroid1);
		asteroid1 = new Asteroid();
		asteroid1->setPosition(centreRotation[0]-x,centreRotation[1]+y,centreRotation[2]);
		groupAsteroid->addAsteroid(asteroid1);
		asteroid1 = new Asteroid();
		asteroid1->setPosition(centreRotation[0]+x,centreRotation[1]-y,centreRotation[2]);
		groupAsteroid->addAsteroid(asteroid1);
		asteroid1 = new Asteroid();
		asteroid1->setPosition(centreRotation[0]-x,centreRotation[1]-y,centreRotation[2]);
		groupAsteroid->addAsteroid(asteroid1);
	}
	GestGroupAsteroids::getSingleton()->addGroupAsteroids(groupAsteroid);
}

