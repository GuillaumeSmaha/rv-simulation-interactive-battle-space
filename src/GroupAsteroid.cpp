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

void GroupAsteroid::addAsteroid(Asteroid * asteroid, ListenerCollision * listenerCollision)
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
    //gestion des collisions avec les astéroides
     asteroid->createCollisionObject(listenerCollision);

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
	vector<Asteroid*>::iterator itAsteroid = lstGroupAsteroid.begin();
    //for(itAsteroid=lstGroupAsteroid.begin(); itAsteroid<lstGroupAsteroid.end();itAsteroid++)
	while (itAsteroid != lstGroupAsteroid.end())
	{
        //delete (*itAsteroid);
		itAsteroid = lstGroupAsteroid.erase(itAsteroid);
    }
	this->node->removeAllChildren(); //	>removeAndDestroyAllChildren();
}


//Getter/setter


std::vector<Asteroid *> GroupAsteroid::getAllGroupAsteroids()
{
	return this->lstGroupAsteroid;
}

void GroupAsteroid::setAngleRotation(Ogre::Radian angleRotation) 
{
	this->angleRotation = angleRotation;
}

Ogre::Radian GroupAsteroid::getAngleRotation(void) 
{
	return this->angleRotation;
}

void GroupAsteroid::setCentreRotation(Ogre::Vector3 &coord)
{
	this->centreRotation = coord;
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
bool GroupAsteroid::isCollided(Asteroid * asteroid) 
{
	vector<Asteroid*>::iterator itGroupAsteroids;
	std::vector<Asteroid *> lstGroupAsteroids= GroupAsteroid::getAllGroupAsteroids();
	Ogre::Real x = asteroid->getPosition()[0];
	Ogre::Real y = asteroid->getPosition()[1];
	Ogre::Real z = asteroid->getPosition()[2];
	for (itGroupAsteroids = lstGroupAsteroids.begin(); itGroupAsteroids<lstGroupAsteroids.end();itGroupAsteroids++)
	{
		if (x < (*itGroupAsteroids)->getPosition()[0]+55 && x > (*itGroupAsteroids)->getPosition()[0]-55)
		{			
			if (y < (*itGroupAsteroids)->getPosition()[1]+55 && y > (*itGroupAsteroids)->getPosition()[1]-55)
			{
				if (z < (*itGroupAsteroids)->getPosition()[2]+55 && z > (*itGroupAsteroids)->getPosition()[2]-55)
				{
					return true;
				}
			}
		}
	}
	return false;
}
void GroupAsteroid::setNodeGroupAsteroid(Ogre::SceneNode * node)
{
	this->node = node;
}

Ogre::SceneNode * GroupAsteroid::getNodeGroupAsteroid(void)
{
	return this->node;
}


