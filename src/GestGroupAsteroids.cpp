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
	GroupAsteroid * groupAsteroid = new GroupAsteroid();
	for (x = rayon; x > 0; x=x-rayon/(nb/4)) //le 4 car on crée les asteroids 4 par 4
	{

	//normaliser le nb par rapport au x -> le rayon
	//for (i = 0; i < nb/4; i++)
	//{
		Asteroid *asteroid1 = new Asteroid();
		Asteroid *asteroid2 = new Asteroid();
		Asteroid *asteroid3 = new Asteroid();
		Asteroid *asteroid4 = new Asteroid();
		//(x - a)² + (y - b)² = r²
		//	Ou (a,b) sont les coordonnées du centre et r est le rayon. 
		//  tous les couples (x,y) qui vérifient l'équation sont des points du cercle.
		//-> si x fixé par le for :
		// on fait 4 asteroids à la fois:
		y =  Ogre::Math::Sqrt(rayon*rayon-x*x-centreRotation[0]*centreRotation[0]+2*x*centreRotation[0]);
		Utils::log("asteroid");
		Utils::log(x);
		Utils::log(y);
		asteroid1->setPosition(centreRotation[0]+x,centreRotation[1]+y,centreRotation[2]);
		groupAsteroid->addAsteroid(asteroid1);
		asteroid2->setPosition(centreRotation[0]-x,centreRotation[1]+y,centreRotation[2]);
		groupAsteroid->addAsteroid(asteroid2);
		asteroid3->setPosition(centreRotation[0]+x,centreRotation[1]-y,centreRotation[2]);
		groupAsteroid->addAsteroid(asteroid3);
		asteroid4->setPosition(centreRotation[0]-x,centreRotation[1]-y,centreRotation[2]);
		groupAsteroid->addAsteroid(asteroid4);
		GestGroupAsteroids::getSingleton()->addGroupAsteroids(groupAsteroid);
	}
}

