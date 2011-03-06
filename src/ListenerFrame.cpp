#include "ListenerFrame.h"

ListenerFrame::ListenerFrame( Ogre::Root * root, Ogre::SceneManager * mSceneMgr): closed(false)
{
	//Tingshuo Debut
	mNumEntitiesInstanced = 0; // how many shapes are created
    //Start Bullet
    mWorld = new OgreBulletDynamics::DynamicsWorld(mSceneMgr, Ogre::AxisAlignedBox(Ogre::Vector3 (-1000000, -1000000, -1000000), Ogre::Vector3 (1000000,  1000000,  1000000)), Ogre::Vector3(0,-9.81,0));
    //add Debug info display tool
    debugDrawer = new OgreBulletCollisions::DebugDrawer();
    debugDrawer->setDrawWireframe(true);   // we want to see the Bullet containers
    mWorld->setDebugDrawer(debugDrawer);
    mWorld->setShowDebugShapes(true);      // enable it if you want to see the Bullet containers
    Ogre::SceneNode *node_debugDrawer = mSceneMgr->getRootSceneNode()->createChildSceneNode("debugDrawer", Ogre::Vector3::ZERO);
    node_debugDrawer->attachObject(static_cast <Ogre::SimpleRenderable *> (debugDrawer));
	//Tingshuo Fin
	root->addFrameListener(this);
}

ListenerFrame::~ListenerFrame()
{
	//Tingshuo Debut
	//OgreBullet physic delete - RigidBodies
    std::deque<OgreBulletDynamics::RigidBody *>::iterator itBody = mBodies.begin();
    while (mBodies.end() != itBody)
    {   
		delete *itBody;
        ++itBody;
    }   
    //OgreBullet physic delete - Shapes
    std::deque<OgreBulletCollisions::CollisionShape *>::iterator itShape = mShapes.begin();
    while (mShapes.end() != itShape)
    {   
        delete *itShape;
        ++itShape;
    }
    mBodies.clear();
    mShapes.clear();
    delete mWorld->getDebugDrawer();
    mWorld->setDebugDrawer(0);
    delete mWorld;
	//Tingshuo Fin
}

bool ListenerFrame::frameRenderingQueued(const Ogre::FrameEvent& evt)
{

    if(this->closed)
    {
        return false;
    }

    this->signalFrameRendering.dispatch();
	return true;
}
void ListenerFrame::shutdown(void*)
{
    this->closed = true;

}

//Tingshuo Debut
bool ListenerFrame::frameStarted(const Ogre::FrameEvent& evt)
{
	bool ret = Ogre::FrameListener::frameStarted(evt);
	mWorld->stepSimulation(evt.timeSinceLastFrame); 
	return ret;
}
//Tingshuo Fin

bool ListenerFrame::frameEnded(const Ogre::FrameEvent& evt)
{
	//this->app->updateStats();
	//Tingshuo Debut
	bool ret = Ogre::FrameListener::frameEnded(evt);
	mWorld->stepSimulation(evt.timeSinceLastFrame); 
	this->signalFrameEnded.dispatch();
	return ret;
	//Tingshuo Fin
}

//Tingshuo Debut
OgreBulletDynamics::RigidBody* ListenerFrame::addSphere(const Ogre::Entity *entity, Ogre::SceneNode *node, const Ogre::Vector3 &pos, const Ogre::Quaternion &q, const Ogre::Real radius, 
			const Ogre::Real bodyRestitution, const Ogre::Real bodyFriction, const Ogre::Real bodyMass)
{
	OgreBulletCollisions::SphereCollisionShape *sceneSphereShape = new OgreBulletCollisions::SphereCollisionShape(radius);

    OgreBulletDynamics::RigidBody *defaultBody = new OgreBulletDynamics::RigidBody(
        "defaultSphereRigid" + Ogre::StringConverter::toString(mNumEntitiesInstanced),
        mWorld);

    defaultBody->setShape (node,  sceneSphereShape, bodyRestitution, bodyFriction, bodyMass, pos, q);

    mShapes.push_back(sceneSphereShape);
    mBodies.push_back(defaultBody);
    mNumEntitiesInstanced++;

    return defaultBody;
}
//Tingshuo Fin