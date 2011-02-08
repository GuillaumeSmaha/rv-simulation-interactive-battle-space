#ifndef __MESH_LOADER_H__
#define __MESH_LOADER_H__

#include <Ogre.h>
#include "meshType.h"
#include "Utils.h"

class MeshLoader
{
	private:
		Ogre::SceneManager * sceneMgr;
		static MeshLoader * _instance ;
	public:
		static MeshLoader * getSingleton(void);
		
		MeshLoader(Ogre::SceneManager * sceneMgr);
		~MeshLoader(void);
		
		Ogre::Entity * getEntity(int meshType, bool random = false)	{
			return getEntity(meshType, "object"+Utils::unique(), random);
		}
		Ogre::Entity * getEntity(int meshType, Ogre::String name,  bool random = false);
		
		Ogre::SceneNode * getNode(int meshType, bool random = false) {
			return getNode(meshType, "node"+Utils::unique(), random);
		}
		Ogre::SceneNode * getNode(int meshType, Ogre::String nodeName, bool random = false)	{
			return getNode(meshType, nodeName, "object"+Utils::unique(), random);
		}
		Ogre::SceneNode * getNode(int meshType, Ogre::String nodeName, Ogre::String meshName,  bool random = false);
		
		Ogre::SceneManager * getSceneManager() {
			return sceneMgr;
		}
};

#endif // __MESH_LOADER_H__
