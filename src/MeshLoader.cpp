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
		case PLANET2:
		case PLANET3:
          //entity = this->sceneMgr->createEntity(name, "sphere.mesh");
			entity = sceneMgr->createEntity(name, "Prefab_Sphere");
			if(random)
			{
			//	type = (MeshLoader::MeshType)((int)PLANET + Utils::randRangeInt(0,2));
			}
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
          node = this->sceneMgr->getSceneNode(NODE_NAME_GROUPE_VAISSEAUX);
          node = node->createChildSceneNode(nodeName);
          node->attachObject(entity);
	    break;
		case PLANET:
		case PLANET2:
		case PLANET3:
          node = this->sceneMgr->getSceneNode(NODE_NAME_GROUPE_DECOR_GROUPE_PLANETES);
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
			entity->setMaterialName("planet");
		break;
		case PLANET2 :
			entity->setMaterialName("planet2");
		break;
		case PLANET3 :
			entity->setMaterialName("planet3");
		break;
	}
}

MeshLoader * MeshLoader::getSingleton(void)
{
	return _instance;
}
