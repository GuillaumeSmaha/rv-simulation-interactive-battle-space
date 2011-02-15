#include "GroupAsteroid.h"

using namespace std;

GroupAsteroid::GroupAsteroid(){
   lstGroupAsteroid.clear();
}

GroupAsteroid::~GroupAsteroid()
{
}

void GroupAsteroid::setAngleRotation(Ogre::Quaternion angleRotation) 
{
	this->angleRotation=angleRotation;
}
Ogre::Quaternion GroupAsteroid::getAngleRotation(void) 
{
	return this->angleRotation;
}
void GroupAsteroid::setCentreRotation(Ogre::Vector3 coord)
{
	this->centreRotation=coord;
}
Ogre::Vector3 GroupAsteroid::getCentreRotation(void)
{
	return this->centreRotation;
}
void GroupAsteroid::setRotationSpeed(Ogre::Real rotationSpeed)
{
	this->rotationSpeed=rotationSpeed;
}
Ogre::Real GroupAsteroid::getRotationSpeed(void) 
{
	return this->rotationSpeed;
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


