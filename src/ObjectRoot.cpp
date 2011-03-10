#include "ObjectRoot.h"
#include "ListenerCollision.h"

using namespace Ogre;
using namespace OgreBulletCollisions;

ObjectRoot::ObjectRoot()
{
    shape = NULL;
    rigidBody = NULL;
}

ObjectRoot::~ObjectRoot()
{
    if(shape != NULL)
        delete shape;

    if(rigidBody != NULL)
        delete rigidBody;
}


void ObjectRoot::createCollisionObject(ListenerCollision * listenerCollision, int size)
{

    std::cout<<"size="<<size<<"ObjectType: "<<typeObject<<std::endl;
    Ogre::Vector3 pos = this->getNode()->getPosition();

	switch(this->typeObject)
	{
		case SHIP_PLAYER :
		case SHIP_IA :
		{
			OgreBulletCollisions::StaticMeshToShapeConverter * shapeConverter = new OgreBulletCollisions::StaticMeshToShapeConverter(this->getEntity());

			OgreBulletCollisions::ConvexHullCollisionShape * convexCollisionShape = shapeConverter->createConvex();
			this->shape = (OgreBulletCollisions::CollisionShape *) convexCollisionShape;

			delete shapeConverter;
			break;
		}
		case SHIP_BATTLE_STATION :
		{
			Ogre::Matrix4 mat = Ogre::Matrix4::IDENTITY;
			for(int i = 0 ; i < 3 ; i ++)
				mat[i][i] *= this->getNode()->_getDerivedScale()[i];
			
			OgreBulletCollisions::StaticMeshToShapeConverter * shapeConverter = new OgreBulletCollisions::StaticMeshToShapeConverter(this->getEntity(), mat);

			OgreBulletCollisions::ConvexHullCollisionShape * convexCollisionShape = shapeConverter->createConvex();
			this->shape = (OgreBulletCollisions::CollisionShape *) convexCollisionShape;

			delete shapeConverter;
			break;
		}
		
		case PLANET :
			this->shape = new OgreBulletCollisions::SphereCollisionShape(size);
			break;
			
		case ASTEROID :
			this->shape = new OgreBulletCollisions::SphereCollisionShape(size);
			break;
			
		case MISSILE :
			this->shape = new OgreBulletCollisions::SphereCollisionShape(10.0);
			break;
			
		case LASER :
			this->shape = new OgreBulletCollisions::SphereCollisionShape(10.0);
			break;
	}


    std::ostringstream rigidBodyString;
    rigidBodyString << "RigidObjectRoot" << Utils::toString(this->typeObject) << "_" << Utils::toString(Utils::unique());
    std::cout<<"nom: "<<rigidBodyString.str()<<std::endl;
    this->rigidBody = new OgreBulletDynamics::RigidBody(rigidBodyString.str() ,listenerCollision->getWorld());

    this->rigidBody->setShape (this->getNode(),  this->shape, 0.6, 0.6, 1.0, pos ,Quaternion(0,0,0,1));
    this->getEntity()->setCastShadows(true);

}



