#include "demo.h"

Demo::Demo(void) {
	this->root = NULL;
	this->sceneMgr = NULL;
	this->window = NULL;
	
	this->resourcesCfg = "resources.cfg";
	this->pluginsCfg = "plugins.cfg";
	
	this->camera = NULL;
	
	this->shutDown = false;
}

//------------------------------------------------------------------------------

Demo::~Demo(void) {
	// remove ourself as a Window listener
	Ogre::WindowEventUtilities::removeWindowEventListener(this->window, this);
	windowClosed(this->window);
}

//------------------------------------------------------------------------------

bool Demo::start(void) {
	// construct Ogre::Root
	this->root = new Ogre::Root(this->pluginsCfg);
 
	// load the ressources
	this->loadRessources();
	
	// restore the config or show the configuration dialog and 
	if(! this->root->restoreConfig() && ! this->root->showConfigDialog())
		return false;

	// initialise the system, create the default rendering window
	this->window = this->root->initialise(true, "Diablotin");

	// get the generic SceneManager
	this->sceneMgr = this->root->createSceneManager(Ogre::ST_GENERIC);
	
	// init the input manager and create the listeners
	this->initListeners();
	
	// create the scene
	this->initScene();
	
	// create the camera
	this->camera = this->sceneMgr->createCamera("mainCam");
	this->camera->setPosition(Ogre::Vector3(20, 20, 20));
	this->camera->lookAt(this->sceneMgr->getRootSceneNode()->getPosition());
	
	// create one viewport, entire window
	// use the same color for the fog and viewport background
	Ogre::Viewport* viewPort = this->window->addViewport(this->camera, 0);
	viewPort->setBackgroundColour(Ogre::ColourValue(0.5f, 0.5f, 1.0f));
	this->camera->setAspectRatio(
		Ogre::Real(viewPort->getActualWidth()) / Ogre::Real(viewPort->getActualHeight()));	
		
	// start the scene rendering (main loop)
	this->root->startRendering();
	
	return true;
}

//------------------------------------------------------------------------------

void Demo::initListeners(void) {
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

void Demo::initScene(void) {	


	Ogre::SceneNode *headNode = this->sceneMgr->createSceneNode("HeadNode");	
	this->sceneMgr->getRootSceneNode()->addChild(headNode);
		
	// charger le « mesh » à partir du nom de fichier et le nommer
	Ogre::Entity *entity = this->sceneMgr->createEntity("Cube", "Cube.mesh");
	// lier l'objet à un nouveau nœud
	Ogre::SceneNode *node = this->sceneMgr->createSceneNode();
	node->attachObject(entity);
	// attacher ce nœud à la scène (ici, à un autre nœud nommé « parentNode »)
	headNode->addChild(node);

    // Set ambient light
    this->sceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
 
    // Create a light
    Ogre::Light* l = this->sceneMgr->createLight("MainLight"); 
    l->setPosition(20,80,50);

}

//------------------------------------------------------------------------------

void Demo::loadRessources(void) {
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

bool Demo::frameRenderingQueued(const Ogre::FrameEvent& evt) {
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

void Demo::windowResized(Ogre::RenderWindow *rw)
{
	unsigned int width, height, depth;
	int left, top;

	// Adjust mouse clipping area
	rw->getMetrics(width, height, depth, left, top); 
	const OIS::MouseState &ms = this->mouse->getMouseState();
	ms.width = width;
	ms.height = height;

}
 
void Demo::windowClosed(Ogre::RenderWindow *rw)
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

bool Demo::keyPressed(const OIS::KeyEvent &evt) {
	
	// Quit
	switch(evt.key)
	{
		case OIS::KC_ESCAPE:
			this->shutDown = true;
			break;
	}
	
	return true;
}

bool Demo::keyReleased(const OIS::KeyEvent &evt) {
	
	return true;
}

bool Demo::mouseMoved(const OIS::MouseEvent &evt) {
	
	float mRotateSpeed = 0.1f;
	
	this->camera->yaw(Ogre::Degree(-evt.state.X.rel * mRotateSpeed));
	this->camera->pitch(Ogre::Degree(-evt.state.Y.rel * mRotateSpeed));
	
	return true;
}

bool Demo::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
	
	return true;
}

bool Demo::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {

	return true;
}

//------------------------------------------------------------------------------

int main(void) {
	Demo demo;
	
	try {
		demo.start();
	} catch( Ogre::Exception& e ) {
		std::cerr << "An exception has occured: " << e.getFullDescription().c_str() << std::endl;
		return 1;
	}
	
	return 0;
}

