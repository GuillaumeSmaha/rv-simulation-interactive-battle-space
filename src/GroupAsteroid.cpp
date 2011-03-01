#include "GroupAsteroid.h"

using namespace std;

GroupAsteroid::GroupAsteroid(): rotationSpeed(0.001)
{
	this->node = GestSceneManager::getSingleton()->getSceneManager()->createSceneNode("GroupAsteroids"+Utils::toString(Utils::unique()));
    lstGroupAsteroid.clear();
}

GroupAsteroid::~GroupAsteroid()
{
}

void GroupAsteroid::setAngleRotation(Ogre::Radian angleRotation) 
{
	this->angleRotation=angleRotation;
}
Ogre::Radian GroupAsteroid::getAngleRotation(void) 
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
	this->rotationSpeed = rotationSpeed;
}
Ogre::Real GroupAsteroid::getRotationSpeed(void) 
{
	return this->rotationSpeed;
}

void GroupAsteroid::addAsteroid(Asteroid * asteroid)
{
	Ogre::SceneNode *nodeAsteroid;
	//node = this->sceneMgr->getSceneNode(NODE_NAME_ENSEMBLE_GROUPE_ASTEROIDES);
	//node = node->createChildSceneNode(nodeName);
	nodeAsteroid = asteroid->getNode();
	if (nodeAsteroid->getParentSceneNode()!=NULL)
	{
		nodeAsteroid->getParentSceneNode()->removeChild(nodeAsteroid);
	}
	this->node->addChild(nodeAsteroid);
    lstGroupAsteroid.push_back(asteroid);
}
void GroupAsteroid::rotateRelative(const Ogre::Radian angle)
{
    this->getNodeGroupAsteroid()->roll(angle);
}
void GroupAsteroid::updateGroupAsteroids(void)
{
	this->rotateRelative(Ogre::Radian(this->getRotationSpeed()));
    vector<Asteroid *>::iterator itAsteroid;
    for(itAsteroid=lstGroupAsteroid.begin(); itAsteroid<lstGroupAsteroid.end();itAsteroid++)
	{
        (*itAsteroid)->updatePosition();
    }
}

void GroupAsteroid::deleteAllGroupAsteroids(void)
{
    vector<Asteroid*>::iterator itAsteroid;
    for(itAsteroid=lstGroupAsteroid.begin(); itAsteroid<lstGroupAsteroid.end();itAsteroid++)
	{
        delete (*itAsteroid);
    }
	this->node->removeAllChildren(); //	>removeAndDestroyAllChildren();
}

void GroupAsteroid::setNodeGroupAsteroid(Ogre::SceneNode* node)
{
	this->node = node;
}

Ogre::SceneNode* GroupAsteroid::getNodeGroupAsteroid(void)
{
	return this->node;
}


