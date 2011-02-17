#include "MeshLoader.h"

MeshLoader* MeshLoader::_instance = NULL;


MeshLoader * MeshLoader::getSingleton(void)
{
	return _instance;
}


MeshLoader::MeshLoader()
{
	this->sceneMgr = GestSceneManager::getSceneManager();
	if(_instance == NULL)
	{
	    _instance = this;
	}
}


bool MeshLoader::deleteMeshLoader(void)
{
    if(_instance != NULL)
    {
        delete _instance;
        return true;
    }
    return false;
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
		case PLANET4:
		case PLANET5:
		case PLANET6:
		case PLANET7:
		case PLANET8:
		case PLANET9:
			entity = sceneMgr->createEntity(name, "Prefab_Sphere");
			if(random)
			{
				type = (MeshLoader::MeshType)((int)PLANET + Utils::randRangeInt(0,7));
			}
	    break;
		case ASTEROID:
			entity = this->sceneMgr->createEntity(name, "asteroid.mesh");
			if(random)
			{
				type = (MeshLoader::MeshType)((int)ASTEROID + Utils::randRangeInt(0,1));
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
		case PLANET4:
		case PLANET5:
		case PLANET6:
		case PLANET7:
		case PLANET8:
		case PLANET9:
          node = this->sceneMgr->getSceneNode(NODE_NAME_GROUPE_DECOR_GROUPE_PLANETES);
          node = node->createChildSceneNode(nodeName);
          node->attachObject(entity);
	    break;
		case ASTEROID:
          node = this->sceneMgr->getSceneNode(NODE_NAME_ENSEMBLE_GROUPE_ASTEROIDES);
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
		case PLANET2:
		case PLANET3:
		case PLANET4:
		case PLANET5:
		case PLANET6:
		case PLANET7:
		case PLANET8:
		case PLANET9:
			entity->setMaterialName("planet"+Utils::toString(type-PLANET+1));
		break;
		case ASTEROID:
			entity->setMaterialName("asteroid"+Utils::toString(type-ASTEROID+1));
		break;
	}
}
