#include "Application.h"
#include "CameraFixe.h"

Application::Application(void) {
	this->root = NULL;
	this->sceneMgr = NULL;
	this->window = NULL;
	
#ifdef _DEBUG
	this->resourcesCfg = "resources_d.cfg";
	this->pluginsCfg = "plugins_d.cfg";
#else
	this->resourcesCfg = "resources.cfg";
	this->pluginsCfg = "plugins.cfg";
#endif

	this->type_Camera = CAMERA_FIXE;
	this->gestCamera = NULL;
	
	this->shutDown = false;
}




//------------------------------------------------------------------------------

Application::~Application(void) {
	// remove ourself as a Window listener
	Ogre::WindowEventUtilities::removeWindowEventListener(this->window, this);
	windowClosed(this->window);
}

//------------------------------------------------------------------------------

bool Application::start(void) {
	// construct Ogre::Root
	this->root = new Ogre::Root(this->pluginsCfg);
 
	// load the ressources
	this->loadRessources();
	
	// restore the config or show the configuration dialog and 
	if(! this->root->restoreConfig() && ! this->root->showConfigDialog())
		return false;

	// initialise the system, create the default rendering window
	this->window = this->root->initialise(true, "Combat spatial");

	// get the generic SceneManager
	this->sceneMgr = this->root->createSceneManager(Ogre::ST_GENERIC);
	
	// init the input manager and create the listeners
	this->initListeners();
	
	// create the scene
	this->initScene();
	
	// create the camera
    switch(this->type_Camera) {
		case CAMERA_FIXE :
			this->gestCamera = new CameraFixe(this->sceneMgr, "mainCamera");
			break;
    }
	this->gestCamera->init_camera();
	
	// create one viewport, entire window
	// use the same color for the fog and viewport background
	//Ogre::Viewport* viewPort = this->window->addViewport(this->camera);
	Ogre::Viewport* viewPort = this->window->addViewport(this->gestCamera->get_camera(), 0);
	viewPort->setBackgroundColour(Ogre::ColourValue(0.0f, 0.0f, 0.0f));
	this->gestCamera->get_camera()->setAspectRatio(Ogre::Real(viewPort->getActualWidth()) / Ogre::Real(viewPort->getActualHeight()));	
		
	// start the scene rendering (main loop)
	this->root->startRendering();
	
	return true;
}

//------------------------------------------------------------------------------

void Application::initListeners(void) {
	// Init the input system
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;
 
	window->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
 
	this->inputManager = OIS::InputManager::createInputSystem(pl);
 
	this->keyboard = static_cast<OIS::Keyboard*>(inputManager->createInputObject(OIS::OISKeyboard, true));
	this->mouse = static_cast<OIS::Mouse*>(inputManager->createInputObject(OIS::OISMouse, true));
 
	// Set initial mouse clipping size
	windowResized(this->window);
	
	// Register the listeners
	Ogre::WindowEventUtilities::addWindowEventListener(this->window, this);
	this->root->addFrameListener(this);
	this->mouse->setEventCallback(this);
	this->keyboard->setEventCallback(this);

}

void Application::initScene(void) {	
	
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			plane, 150, 150, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
	Ogre::Entity* entGround = this->sceneMgr->createEntity("GroundEntity", "ground");
	entGround->setMaterialName("Rockwall");
	entGround->setCastShadows(false);
	Ogre::SceneNode *groundNode = this->sceneMgr->getRootSceneNode()->createChildSceneNode("ground");
	groundNode->attachObject(entGround);
	groundNode->setPosition(0, -50, 0);


	Ogre::SceneNode *headNodeObject = this->sceneMgr->getRootSceneNode()->createChildSceneNode("HeadNodeObject");	
	Ogre::SceneNode *headNodeLight = this->sceneMgr->getRootSceneNode()->createChildSceneNode("HeadNodeLight");	
		
	// charger le « mesh » à partir du nom de fichier et le nommer
	Ogre::Entity *entity = this->sceneMgr->createEntity("Suzanne", "suzanne.mesh");
	Ogre::SceneNode *nodeObjectSuzanne = headNodeObject->createChildSceneNode("NodeObjectSuzanne");
	nodeObjectSuzanne->attachObject(entity);
	nodeObjectSuzanne->setPosition(0, 0, 0);
	nodeObjectSuzanne->scale(10, 10, 10);
	
	/*Ogre::Entity *entity1 = this->sceneMgr->createEntity("SuzanneBoiteBas", "boite_bas.mesh");
	Ogre::Entity *entity2 = this->sceneMgr->createEntity("SuzanneBoiteFermeture", "fermeture.mesh");
	entity = this->sceneMgr->createEntity("SuzanneBoiteHaut", "boite_haut.mesh");
	Ogre::SceneNode *nodeObjectSuzanneBoiteHaut = headNodeObject->createChildSceneNode("NodeObjectSuzanneBoiteHaut");
	nodeObjectSuzanneBoiteHaut->attachObject(entity);
	nodeObjectSuzanneBoiteHaut->setPosition(0, 0, 0);
	nodeObjectSuzanneBoiteHaut->scale(10, 10, 10);*/

    // Set ambient light
    //this->sceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    this->sceneMgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));
 
    // Create a light
    Ogre::Light* l = this->sceneMgr->createLight("MainLight"); 
    l->setPosition(20,80,50);
	Ogre::SceneNode *nodeLight1 = headNodeLight->createChildSceneNode("NodeLight1");
	nodeLight1->attachObject(l);
}

//------------------------------------------------------------------------------

void Application::loadRessources(void) {
	// setup resources
	// Load resource paths from config file
	Ogre::ConfigFile cf;
	cf.load(this->resourcesCfg);
 
	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
  
	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
		}
	}
	
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

//------------------------------------------------------------------------------

bool Application::frameRenderingQueued(const Ogre::FrameEvent& evt) {
	int newStatus;
	
	// Stop the rendering if the window was closed, or the application stoped
	if(this->window->isClosed() || this->shutDown)
		return false;

    // capture value of each device
    this->keyboard->capture();
    this->mouse->capture();

	return true;
}

//------------------------------------------------------------------------------

void Application::windowResized(Ogre::RenderWindow *rw)
{
	unsigned int width, height, depth;
	int left, top;

	// Adjust mouse clipping area
	rw->getMetrics(width, height, depth, left, top); 
	const OIS::MouseState &ms = this->mouse->getMouseState();
	ms.width = width;
	ms.height = height;

}
 
void Application::windowClosed(Ogre::RenderWindow *rw)
{
	// Only close for window that created OIS (the main window)
	if(rw == this->window)
	{
		if(this->inputManager)
		{
			// Unattach OIS before window shutdown (very important under Linux)
			this->inputManager->destroyInputObject(this->mouse);
			this->inputManager->destroyInputObject(this->keyboard);
 
			OIS::InputManager::destroyInputSystem(this->inputManager);
			this->inputManager = 0;
		}
	}

}

bool Application::keyPressed(const OIS::KeyEvent &evt) {
	
	// Quit
	switch(evt.key)
	{
		case OIS::KC_ESCAPE:
			this->shutDown = true;
			break;
			
		case OIS::KC_UP:
			this->gestCamera->get_camera()->move(Ogre::Vector3(0, 0, 5));
			break;
			
		case OIS::KC_DOWN:
			this->gestCamera->get_camera()->move(Ogre::Vector3(0, 0, -5));
			break;
			
		case OIS::KC_H:
			this->gestCamera->get_camera()->move(Ogre::Vector3(0, 5, 0));
			break;
			
		case OIS::KC_N:
			this->gestCamera->get_camera()->move(Ogre::Vector3(0, -5, 0));
			break;
			
		case OIS::KC_G:
			this->gestCamera->get_camera()->move(Ogre::Vector3(5, 0, 0));
			break;
			
		case OIS::KC_B:
			this->gestCamera->get_camera()->move(Ogre::Vector3(-5, 0, 0));
			break;
	}
	
	std::cout << "PosCamera : " << this->gestCamera->get_camera()->getPosition()[0] << "/" << this->gestCamera->get_camera()->getPosition()[1] << "/" << this->gestCamera->get_camera()->getPosition()[2] << std::endl;
	
	return true;
}

bool Application::keyReleased(const OIS::KeyEvent &evt) {
	
	return true;
}

bool Application::mouseMoved(const OIS::MouseEvent &evt) {
	
	float mRotateSpeed = 0.1f;
	
	this->gestCamera->get_camera()->yaw(Ogre::Degree(-evt.state.X.rel * mRotateSpeed));
	this->gestCamera->get_camera()->pitch(Ogre::Degree(-evt.state.Y.rel * mRotateSpeed));
	
	return true;
}

bool Application::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
	
	return true;
}

bool Application::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {

	return true;
}

//------------------------------------------------------------------------------

int main(void) {
	Application appli;
	
	try {
	    appli.start();
	} catch( Ogre::Exception& e ) {
		std::cerr << "An exception has occured: " << e.getFullDescription().c_str() << std::endl;
		return 1;
	}
	
	return 0;
}

