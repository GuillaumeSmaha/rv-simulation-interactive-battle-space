#ifndef _SHIP_H_
#define _SHIP_H_

#include <MeshLoader.h>
#include <Utils.h>
#include <Ogre.h>

class Ship
{
private:
    Ogre::SceneNode * node;
public:
    Ship(void);
    ~Ship(void);
    void setPosition(Ogre::Real x, Ogre::Real y, Ogre::Real z);
    Ogre::String getName(void)
    {
        return this->node->getName();
    }
    Ogre::SceneNode * getNode(void)
    {
        return this->node;
    }
};
#endif
