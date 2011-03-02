#include "MeshLoader.h"

using namespace Ogre;

MeshLoader* MeshLoader::_instance = NULL;


MeshLoader * MeshLoader::getSingleton(void)
{
	if(_instance == NULL)
	{
		_instance = new MeshLoader();
	}
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

Ogre::Entity * MeshLoader::getEntity(MeshLoader::MeshType type, Ogre::String name, bool random)
{
	Ogre::Entity * entity;
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
		case MISSILE:
			entity = this->sceneMgr->createEntity(name, "missile.mesh");
			break;
			
		default:
			Utils::log("@Ogre::Entity * MeshLoader::getEntity(MeshLoader::MeshType type, Ogre::String name, bool random) : type inconnu");
			break;
	}
	
	MeshLoader::setMaterial(entity, type);
	return entity;
}

Ogre::Entity * MeshLoader::getNodedEntity(MeshLoader::MeshType type, Ogre::String nodeName, Ogre::String meshName, bool random)
{
	Ogre::SceneNode * node;
	Ogre::Entity * entity = getEntity(type, meshName, random);
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
		case MISSILE:
			node = this->sceneMgr->getSceneNode(NODE_NAME_GROUPE_MISSILES);
			node = node->createChildSceneNode(nodeName);
			node->attachObject(entity);
			break;
			
		default:
			Utils::log("@Ogre::Entity * MeshLoader::getNodedEntity(MeshLoader::MeshType type, Ogre::String nodeName, Ogre::String meshName, bool random) : type inconnu");
			break;
	}
	return entity;
}

Ogre::SceneNode * MeshLoader::getNode(MeshLoader::MeshType type, Ogre::String nodeName)
{
	Ogre::SceneNode * node;
	switch(type)
	{
		case SHIP:
		case SHIP_TOUCHED:
			node = this->sceneMgr->getSceneNode(NODE_NAME_GROUPE_VAISSEAUX);
			node = node->createChildSceneNode(nodeName);
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
			break;
		case ASTEROID:
			node = this->sceneMgr->getSceneNode(NODE_NAME_ENSEMBLE_GROUPE_ASTEROIDES);
			node = node->createChildSceneNode(nodeName);
			break;
		case MISSILE:
			node = this->sceneMgr->getSceneNode(NODE_NAME_GROUPE_MISSILES);
			node = node->createChildSceneNode(nodeName);
			break;
			
		default:
			Utils::log("@Ogre::SceneNode * MeshLoader::getNode(MeshLoader::MeshType type, Ogre::String nodeName) : type inconnu");
			break;
	}
	return node;
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
			entity->setMaterialName("asteroid1");
		case MISSILE:
			entity->setMaterialName("missile");
			break;
			
		default:
			Utils::log("@void MeshLoader::setMaterial(Ogre::Entity * entity, MeshLoader::MeshType type) : type inconnu");
			break;
	}
}

void MeshLoader::createSphere(const std::string& strName, const float r, const int nRings, const int nSegments)
{
	MeshPtr pSphere = MeshManager::getSingleton().createManual(strName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	SubMesh *pSphereVertex = pSphere->createSubMesh();

	pSphere->sharedVertexData = new VertexData();
	VertexData* vertexData = pSphere->sharedVertexData;

	// define the vertex format
	VertexDeclaration* vertexDecl = vertexData->vertexDeclaration;
	size_t currOffset = 0;
	// positions
	vertexDecl->addElement(0, currOffset, VET_FLOAT3, VES_POSITION);
	currOffset += VertexElement::getTypeSize(VET_FLOAT3);
	// normals
	vertexDecl->addElement(0, currOffset, VET_FLOAT3, VES_NORMAL);
	currOffset += VertexElement::getTypeSize(VET_FLOAT3);
	// two dimensional texture coordinates
	vertexDecl->addElement(0, currOffset, VET_FLOAT2, VES_TEXTURE_COORDINATES, 0);
	currOffset += VertexElement::getTypeSize(VET_FLOAT2);

	// allocate the vertex buffer
	vertexData->vertexCount = (nRings + 1) * (nSegments+1);
	HardwareVertexBufferSharedPtr vBuf = HardwareBufferManager::getSingleton().createVertexBuffer(vertexDecl->getVertexSize(0), vertexData->vertexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY, false);
	VertexBufferBinding* binding = vertexData->vertexBufferBinding;
	binding->setBinding(0, vBuf);
	float* pVertex = static_cast<float*>(vBuf->lock(HardwareBuffer::HBL_DISCARD));

	// allocate index buffer
	pSphereVertex->indexData->indexCount = 6 * nRings * (nSegments + 1);
	pSphereVertex->indexData->indexBuffer = HardwareBufferManager::getSingleton().createIndexBuffer(HardwareIndexBuffer::IT_16BIT, pSphereVertex->indexData->indexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY, false);
	HardwareIndexBufferSharedPtr iBuf = pSphereVertex->indexData->indexBuffer;
	unsigned short* pIndices = static_cast<unsigned short*>(iBuf->lock(HardwareBuffer::HBL_DISCARD));

	float fDeltaRingAngle = (PI / nRings);
	float fDeltaSegAngle = (2 * PI / nSegments);
	unsigned short wVerticeIndex = 0 ;

	// Generate the group of rings for the sphere
	for( int ring = 0; ring <= nRings; ring++ ) {
		float r0 = r * sinf (ring * fDeltaRingAngle);
		float y0 = r * cosf (ring * fDeltaRingAngle);

		// Generate the group of segments for the current ring
		for(int seg = 0; seg <= nSegments; seg++) {
			float x0 = r0 * sinf(seg * fDeltaSegAngle);
			float z0 = r0 * cosf(seg * fDeltaSegAngle);

			// Add one vertex to the strip which makes up the sphere
			*pVertex++ = x0;
			*pVertex++ = y0;
			*pVertex++ = z0;

			Vector3 vNormal = Vector3(x0, y0, z0).normalisedCopy();
			*pVertex++ = vNormal.x;
			*pVertex++ = vNormal.y;
			*pVertex++ = vNormal.z;

			*pVertex++ = (float) seg / (float) nSegments;
			*pVertex++ = (float) ring / (float) nRings;

			if (ring != nRings) {
				// each vertex (except the last) has six indices pointing to it
				*pIndices++ = wVerticeIndex + nSegments + 1;
				*pIndices++ = wVerticeIndex;               
				*pIndices++ = wVerticeIndex + nSegments;
				*pIndices++ = wVerticeIndex + nSegments + 1;
				*pIndices++ = wVerticeIndex + 1;
				*pIndices++ = wVerticeIndex;
				wVerticeIndex ++;
			}
		}; // end for seg
	} // end for ring

	// Unlock
	vBuf->unlock();
	iBuf->unlock();
	// Generate face list
	pSphereVertex->useSharedVertices = true;

	// the original code was missing this line:
	pSphere->_setBounds( AxisAlignedBox( Vector3(-r, -r, -r), Vector3(r, r, r) ), false );
	pSphere->_setBoundingSphereRadius(r);

	// tangent vectors creation
	unsigned short src, dest;
	if (!pSphere->suggestTangentVectorBuildParams(VES_TANGENT, src, dest))
	{
		pSphere->buildTangentVectors(VES_TANGENT, src, dest);
	}

	// this line makes clear the mesh is loaded (avoids memory leaks)
	pSphere->load();
}
