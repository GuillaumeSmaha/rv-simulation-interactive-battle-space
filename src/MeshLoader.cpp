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

Ogre::Entity* MeshLoader::getEntity(int meshType, Ogre::String name, bool random)
{
    Ogre::Entity *entity;
	switch(meshType)
	{
	    case SHIP:
          entity = this->sceneMgr->createEntity(name, "razor.mesh");
          entity->setMaterialName("razor");
	    break;
	}
	return entity;
}

Ogre::SceneNode* MeshLoader::getNode(int meshType, Ogre::String nodeName, Ogre::String meshName, bool random)
{
    Ogre::SceneNode *node;
    Ogre::Entity *entity = getEntity(meshType, meshName, random);
	switch(meshType)
	{
	    case SHIP:
          node = this->sceneMgr->getSceneNode("GroupeVaisseaux");
          node = node->createChildSceneNode(nodeName);
          node->attachObject(entity);
	    break;
	}
	return node;
}

MeshLoader * MeshLoader::getSingleton(void)
{
	return _instance;
}
