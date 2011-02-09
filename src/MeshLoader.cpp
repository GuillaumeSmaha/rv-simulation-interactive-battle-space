#include "MeshLoader.h"

MeshLoader* MeshLoader::_instance = NULL;

MeshLoader::MeshLoader(Ogre::SceneManager * sceneMgr)
{
	this->sceneMgr = sceneMgr;
	if(_instance == NULL)
	{
	    _instance = this;
	}

}

MeshLoader::~MeshLoader(void)
{
	//this->sceneMgr = NULL;
}

Ogre::Entity* MeshLoader::getEntity(MeshLoader::MeshType type, Ogre::String name, bool random)
{
    Ogre::Entity *entity;
	switch(type)
	{
	    case SHIP:
          entity = this->sceneMgr->createEntity(name, "razor.mesh");
	    break;
	    case SHIP_TOUCHED:
          entity = this->sceneMgr->createEntity(name, "razor.mesh");
	    break;
		case PLANET:
          entity = this->sceneMgr->createEntity(name, "sphere.mesh");
	    break;
	}
	MeshLoader::setMaterial(entity, type);
	return entity;
}
Ogre::Entity* MeshLoader::getNodedEntity(MeshLoader::MeshType type, Ogre::String nodeName, Ogre::String meshName, bool random)
{
    Ogre::SceneNode *node;
    Ogre::Entity *entity = getEntity(type, meshName, random);
	switch(type)
	{
	    case SHIP:
	    case SHIP_TOUCHED:
          node = this->sceneMgr->getSceneNode("GroupeVaisseaux");
          node = node->createChildSceneNode(nodeName);
          node->attachObject(entity);
	    break;
		case PLANET:
          node = this->sceneMgr->getSceneNode("GroupeDecors_GroupePlanetes");
          node = node->createChildSceneNode(nodeName);
          node->attachObject(entity);
	    break;
	}
	return entity;
}
void MeshLoader::setMaterial(Ogre::Entity * entity, MeshLoader::MeshType type)
{
    switch(type)
	{
	    case SHIP:
            entity->setMaterialName("razor");
	    break;
	    case SHIP_TOUCHED:
          entity->setMaterialName("razor2");
	    break;
		case PLANET :
			entity->setMaterialName("pluton");
		break;
	}
}

MeshLoader * MeshLoader::getSingleton(void)
{
	return _instance;
}
