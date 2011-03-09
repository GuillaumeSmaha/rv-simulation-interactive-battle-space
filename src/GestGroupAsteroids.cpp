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


void GestGroupAsteroids::updateGroupsAsteroids(void * useless)
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

void GestGroupAsteroids::createGroup(int nb, int degreLiberte, int scale, Ogre::Radian angleRotation, Ogre::Real rayon, Ogre::SceneNode *planet, Ogre::Real rotationSpeed, ListenerCollision * listenerCollision) 
{
	Ogre::Real x;
	Ogre::Real y;
	rayon = 2 * rayon;
	//rayon = 12;
	Asteroid *asteroid1;

	GroupAsteroid * groupAsteroid = new GroupAsteroid();
	groupAsteroid->setRotationSpeed(rotationSpeed);

	groupAsteroid->setNodeGroupAsteroid(planet->createChildSceneNode("GroupAsteroids"+Utils::toString(Utils::unique())));
	for (x = rayon; x > 0; x=x-rayon/(nb/4)) //le 4 car on crée les asteroids 4 par 4
	{
		asteroid1 = new Asteroid();
		asteroid1->getNode()->setScale(scale+Utils::randRangeInt(-10,10),scale+Utils::randRangeInt(-10,10),scale+Utils::randRangeInt(-10,10));
		//normaliser le nb par rapport au x -> le rayon
		//(x - a)² + (y - b)² = r²
		//	Ou (a,b) sont les coordonnées du centre et r est le rayon. 
		//  tous les couples (x,y) qui vérifient l'équation sont des points du cercle.
		//-> si x fixé par le for :
		// on fait 4 asteroids à la fois:

		y =  Ogre::Math::Sqrt(rayon*rayon-x*x)+Utils::randRangeInt(-degreLiberte,degreLiberte);
		asteroid1->setPosition(x+Utils::randRangeInt(-degreLiberte,degreLiberte),y,Utils::randRangeInt(-degreLiberte,degreLiberte));
		if (groupAsteroid->isCollided(asteroid1)==false)
		{
    		groupAsteroid->addAsteroid(asteroid1, listenerCollision);
		}
		else 
		{
			delete asteroid1;
		}
		
		asteroid1 = new Asteroid();
		asteroid1->getNode()->setScale(scale+Utils::randRangeInt(-10,10),scale+Utils::randRangeInt(-10,10),scale+Utils::randRangeInt(-10,10));
		asteroid1->setPosition(-x+Utils::randRangeInt(-degreLiberte,degreLiberte),y,Utils::randRangeInt(-degreLiberte,degreLiberte));
		if (groupAsteroid->isCollided(asteroid1)==false)
		{	
			groupAsteroid->addAsteroid(asteroid1, listenerCollision);
		}
		else 
		{
			delete asteroid1;
		}
		
		asteroid1 = new Asteroid();
		asteroid1->getNode()->setScale(scale+Utils::randRangeInt(-10,10),scale+Utils::randRangeInt(-10,10),scale+Utils::randRangeInt(-10,10));
		asteroid1->setPosition(x+Utils::randRangeInt(-degreLiberte,degreLiberte),-y,Utils::randRangeInt(-degreLiberte,degreLiberte));
		if (groupAsteroid->isCollided(asteroid1)==false)
		{
			groupAsteroid->addAsteroid(asteroid1, listenerCollision);
		}
		else 
		{
			delete asteroid1;
		}
		
		asteroid1 = new Asteroid();
		asteroid1->getNode()->setScale(scale+Utils::randRangeInt(-10,10),scale+Utils::randRangeInt(-10,10),scale+Utils::randRangeInt(-10,10));
		asteroid1->setPosition(-x+Utils::randRangeInt(-degreLiberte,degreLiberte),-y,Utils::randRangeInt(-degreLiberte,degreLiberte));
		if (groupAsteroid->isCollided(asteroid1)==false)
		{
			groupAsteroid->addAsteroid(asteroid1, listenerCollision);
		}
		else 
		{
			delete asteroid1;
		}
	}
	GestGroupAsteroids::getSingleton()->addGroupAsteroids(groupAsteroid);
}

