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

    OgreBulletCollisions::StaticMeshToShapeConverter * shapeConverter= new OgreBulletCollisions::StaticMeshToShapeConverter(this->getEntity());
        if(typeObject==SHIP_PLAYER|| typeObject==SHIP_IA){
            OgreBulletCollisions::ConvexHullCollisionShape * convexCollisionShape =shapeConverter->createConvex();
            this->shape =(OgreBulletCollisions::CollisionShape *) convexCollisionShape;

            delete shapeConverter;
        }
        if(typeObject==PLANET){
	        this->shape = new OgreBulletCollisions::SphereCollisionShape(size);
        }
        if(typeObject==ASTEROID){
            this->shape = new OgreBulletCollisions::SphereCollisionShape(50.0);
        }
        if(typeObject== MISSILE){
            this->shape = new OgreBulletCollisions::SphereCollisionShape(10.0);
        }
        if(typeObject==LASER){
            this->shape = new OgreBulletCollisions::SphereCollisionShape(10.0);
        }


    std::ostringstream rigidBodyString;
    rigidBodyString << "RigidObjectRoot" << Utils::toString(this->typeObject) << "_" << Utils::toString(Utils::unique());
    this->rigidBody = new OgreBulletDynamics::RigidBody(rigidBodyString.str() ,listenerCollision->getWorld());

    this->rigidBody->setShape (this->getNode(),  this->shape, 0.6, 0.6, 1.0, pos ,Quaternion(0,0,0,1));
    this->getEntity()->setCastShadows(true);

}



