#include "ShipIA.h"

using namespace Ogre;

ShipIA::ShipIA(void) : ShipAbstract()
{
    this->typeObject = ObjectRoot::SHIP_IA;
}

ShipIA::~ShipIA(void)
{

}

void ShipIA::updatePosition(void)
{
   Ogre::Real sx, sy, cx, cy;

    if(GestSceneManager::projectSizeAndPos(GestSceneManager::getCamera(0)->getCamera(), this->getNode()->convertLocalToWorldPosition(this->getNode()->getPosition()), this->getEntity()->getWorldBoundingSphere().getRadius(),sx, sy, cx, cy)){
        cx *= 800;
        cy *= 600;
        sx = (sx + 1)* 400;
        sy = (sy + 1)* 300;
        //Utils::log("("+Utils::toString(sx)+";"+Utils::toString(sy)+")   =   "+""+"["+Utils::toString(cx)+";"+Utils::toString(cy)+"]"+":"+Utils::toString(this->getEntity()->getBoundingRadius()));
        Ogre::Vector2 pos;
        //GestSceneManager::getScreenspaceCoords()
        GestSceneManager::getScreenspaceCoords(this->getEntity(), GestSceneManager::getCamera(0)->getCamera(),pos);
       // Utils::log("("+Utils::toString(pos.x*800)+";"+Utils::toString(pos.y*600)+")");
    }else
    {
        //Utils::log("hidden("+Utils::toString(sx)+";"+Utils::toString(sy)+")   =   "+""+"["+Utils::toString(cx)+";"+Utils::toString(cy)+"]"+":"+Utils::toString(this->getEntity()->getBoundingRadius()));

    }
	if (this->getAcceleration() != 0)
	{
		this->setSpeed(this->getSpeed()+this->getAcceleration());
		this->setAcceleration(0);
	}
	if (this->getSpeed() != 0)
	{
		this->moveRelative(0.0, 0.0, this->getSpeed());
	}
}
