#include "Application.h"


using namespace Ogre;

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

	this->type_Camera = CameraFixeAbstract::CAMERA_FIXE;
	this->gestCamera = NULL;
	
	this->shutDown = false;
	
	this->_translateX = 0;
	this->_translateZ = 0;
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

	//init meshLoader
	new MeshLoader(this->sceneMgr);
	
	// init the input manager and create the listeners
	this->initListeners();
	
	// create the scene graph
	this->initSceneGraph();
	
	// create the scene
	this->initScene();
	
	// create the camera
    switch(this->type_Camera) {
		case CameraFixeAbstract::CAMERA_FIXE :
			this->gestCamera = new CameraFixe(this->sceneMgr, "camera_fixe");
			break;
			
		case CameraFixeAbstract::CAMERA_FISRT_PERSON :
			this->gestCamera = new CameraFirstPerson(this->sceneMgr, "camera_firstPerson", this->sceneMgr->getSceneNode("GroupeVaisseaux_Vaisseau1_Camera_FirstPerson"));
			break;
			
		case CameraFixeAbstract::CAMERA_EXTERIEURE_FIXE :
			this->gestCamera = new CameraExterieureFixe(this->sceneMgr, "camera_exterieureFixe", this->sceneMgr->getSceneNode("GroupeVaisseaux_Vaisseau1_Camera_ExtFixe"));
			break;
    }
	this->gestCamera->init_camera();
	
	// create one viewport, entire window
	// use the same color for the fog and viewport background
	Ogre::Viewport * viewPort = this->window->addViewport(this->gestCamera->getCamera(), 0);
	viewPort->setBackgroundColour(Ogre::ColourValue(0.0f, 0.0f, 0.0f));	
	this->gestCamera->getCamera()->setAspectRatio(Ogre::Real(viewPort->getActualWidth()) / Ogre::Real(viewPort->getActualHeight()));
		
	// start the scene rendering (main loop)
	this->root->startRendering();
	
	return true;
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


void Application::initSceneGraph(void) {
	
	//FondEtoiles
//	Ogre::SceneNode * FondEtoiles = this->sceneMgr->getRootSceneNode()->createChildSceneNode("FondEtoiles");	
	
	//Groupes Vaisseaux
	Ogre::SceneNode * GroupeVaisseaux = this->sceneMgr->getRootSceneNode()->createChildSceneNode("GroupeVaisseaux");	
	//a definir qqpart, ptre dans Ship
	/*
		//Vaisseau 1
		Ogre::SceneNode * GroupeVaisseaux_Vaisseau1 = GroupeVaisseaux->createChildSceneNode("GroupeVaisseaux_Vaisseau1");
			Ogre::SceneNode * GroupeVaisseaux_Vaisseau1_Reacteur = GroupeVaisseaux_Vaisseau1->createChildSceneNode("GroupeVaisseaux_Vaisseau1_Reacteur");
			Ogre::SceneNode * GroupeVaisseaux_Vaisseau1_Corps = GroupeVaisseaux_Vaisseau1->createChildSceneNode("GroupeVaisseaux_Vaisseau1_Corps");
			Ogre::SceneNode * GroupeVaisseaux_Vaisseau1_Arme = GroupeVaisseaux_Vaisseau1->createChildSceneNode("GroupeVaisseaux_Vaisseau1_Arme");
			Ogre::SceneNode * GroupeVaisseaux_Vaisseau1_Camera = GroupeVaisseaux_Vaisseau1->createChildSceneNode("GroupeVaisseaux_Vaisseau1_Camera");
				Ogre::SceneNode * GroupeVaisseaux_Vaisseau1_Camera_FirstPerson = GroupeVaisseaux_Vaisseau1_Camera->createChildSceneNode("GroupeVaisseaux_Vaisseau1_Camera_FirstPerson");
				Ogre::SceneNode * GroupeVaisseaux_Vaisseau1_Camera_ThirdPerson = GroupeVaisseaux_Vaisseau1_Camera->createChildSceneNode("GroupeVaisseaux_Vaisseau1_Camera_ThirdPerson");
				Ogre::SceneNode * GroupeVaisseaux_Vaisseau1_Camera_ExtFixe = GroupeVaisseaux_Vaisseau1_Camera->createChildSceneNode("GroupeVaisseaux_Vaisseau1_Camera_ExtFixe");
		//Vaisseau 2
		Ogre::SceneNode * GroupeVaisseaux_Vaisseau2 = GroupeVaisseaux->createChildSceneNode("GroupeVaisseaux_Vaisseau2");
			Ogre::SceneNode * GroupeVaisseaux_Vaisseau2_Reacteur = GroupeVaisseaux_Vaisseau1->createChildSceneNode("GroupeVaisseaux_Vaisseau2_Reacteur");
			Ogre::SceneNode * GroupeVaisseaux_Vaisseau2_Corps = GroupeVaisseaux_Vaisseau1->createChildSceneNode("GroupeVaisseaux_Vaisseau2_Corps");
			Ogre::SceneNode * GroupeVaisseaux_Vaisseau2_Arme = GroupeVaisseaux_Vaisseau1->createChildSceneNode("GroupeVaisseaux_Vaisseau2_Arme");
			Ogre::SceneNode * GroupeVaisseaux_Vaisseau2_Camera = GroupeVaisseaux_Vaisseau1->createChildSceneNode("GroupeVaisseaux_Vaisseau2_Camera");
				Ogre::SceneNode * GroupeVaisseaux_Vaisseau2_Camera_FirstPerson = GroupeVaisseaux_Vaisseau1_Camera->createChildSceneNode("GroupeVaisseaux_Vaisseau2_Camera_FirstPerson");
				Ogre::SceneNode * GroupeVaisseaux_Vaisseau2_Camera_ThirdPerson = GroupeVaisseaux_Vaisseau1_Camera->createChildSceneNode("GroupeVaisseaux_Vaisseau2_Camera_ThirdPerson");
				Ogre::SceneNode * GroupeVaisseaux_Vaisseau2_Camera_ExtFixe = GroupeVaisseaux_Vaisseau1_Camera->createChildSceneNode("GroupeVaisseaux_Vaisseau2_Camera_ExtFixe");
	*/
		
	//Groupe décor
	Ogre::SceneNode * GroupeDecors = this->sceneMgr->getRootSceneNode()->createChildSceneNode("GroupeDecors");	
		//Groupe planetes
		Ogre::SceneNode * GroupeDecors_GroupePlanete = GroupeDecors->createChildSceneNode("GroupeDecors_GroupePlanetes");
		//Groupe soleils
		Ogre::SceneNode * GroupeDecors_GroupeSoleil = GroupeDecors->createChildSceneNode("GroupeDecors_GroupeSoleils");
	
	//Ensemble de groupes d'astéroides
	Ogre::SceneNode * EnsembleGroupesAsteroides = this->sceneMgr->getRootSceneNode()->createChildSceneNode("EnsembleGroupesAsteroides");	
}


void Application::initScene(void) {	
	
// Mise en place du SkyBox "Etoiles"
	this->sceneMgr->setSkyBox(true, "SpaceSkyBox", 5000);
	
//SpaceShip notre vaisseau 1 :
	//Ogre::Entity *entityVaisseau = this->sceneMgr->createEntity("Suzanne", "suzanne.mesh");
	/*Ogre::Entity *entityVaisseau = this->sceneMgr->createEntity("Spaceship", "razor.mesh");
	entityVaisseau->setMaterialName("razor");*/
   /* Ogre::Entity *entityVaisseau = MeshLoader::getSingleton()->getEntity(SHIP);
	Ogre::SceneNode * GroupeVaisseaux_Vaisseau1_Corps = this->sceneMgr->getSceneNode("GroupeVaisseaux_Vaisseau1_Corps");

	GroupeVaisseaux_Vaisseau1_Corps->attachObject(entityVaisseau);
	GroupeVaisseaux_Vaisseau1_Corps->setPosition(0, 0, 0);
	entityVaisseau = MeshLoader::getSingleton()->getEntity(SHIP);
	GroupeVaisseaux_Vaisseau1_Corps = this->sceneMgr->getSceneNode("GroupeVaisseaux_Vaisseau1_Corps")->createChildSceneNode("vsx2");

	GroupeVaisseaux_Vaisseau1_Corps->attachObject(entityVaisseau);
	GroupeVaisseaux_Vaisseau1_Corps->setPosition(100, 100, 30);
	GroupeVaisseaux_Vaisseau1_Corps->setOrientation(5,5,5,5);*/
	//GroupeVaisseaux_Vaisseau1_Corps->scale(10, 10, 10);
    Ship * ship = new Ship();
    ship->setPosition(-50,-50,-50);
    ship = new Ship();
    ship->setPosition(130,0,0);
    ship->getNode()->setOrientation(5, 5, 5, 5);
    ship->touched();

    /*
	// Création du système de particules
    Ogre::ParticleSystem* thrusters = this->sceneMgr->createParticleSystem(25);
    thrusters ->setMaterialName("Reactor");
    thrusters ->setDefaultDimensions(25, 25);

	// Création de 2 émetteurs pour le système de particules
	for (unsigned int i = 0; i < 2; i++)
	{
		Ogre::ParticleEmitter* emitter = thrusters ->addEmitter("Point");

		// set the emitter properties
		emitter->setAngle(Ogre::Degree(3));
		emitter->setTimeToLive(0.5);
		emitter->setEmissionRate(25);
		emitter->setParticleVelocity(25);
		emitter->setDirection(Vector3::NEGATIVE_UNIT_Z);
		emitter->setColour(ColourValue::White, ColourValue::Red);
		emitter->setPosition(Vector3(i == 0 ? 5.7 : -18, 0, 0));
	}

	// On attache les particules du réacteur à l'arrière du vaisseau
    this->sceneMgr->getRootSceneNode()->createChildSceneNode(Vector3(0, 6.5, -67))->attachObject(thrusters);
    */
	
	
//Temporaire : 	
    // Set ambient light
    this->sceneMgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));
    // Create a light
    Ogre::Light* l = this->sceneMgr->createLight("MainLight"); 
    l->setPosition(20,80,50);
	Ogre::SceneNode * nodeLight1 = this->sceneMgr->getRootSceneNode()->createChildSceneNode("NodeLight1");
	nodeLight1->attachObject(l);
}

//------------------------------------------------------------------------------

bool Application::frameRenderingQueued(const Ogre::FrameEvent& evt) {
	
	// Stop the rendering if the window was closed, or the application stoped
	if(this->window->isClosed() || this->shutDown)
		return false;

    // capture value of each device
    this->keyboard->capture();
    this->mouse->capture();
    
    this->gestCamera->getCamera()->moveRelative( Ogre::Vector3(this->_translateX, 0.0f, this->_translateZ) );

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
	float translateSpeed = 2.5;
	
	switch(evt.key)
	{
		case OIS::KC_ESCAPE :
			this->shutDown = true;
			break;
			
		case OIS::KC_UP :
			this->_translateZ = -translateSpeed;
			break;
			
		case OIS::KC_DOWN :
			this->_translateZ = translateSpeed;
			break;
			
		case OIS::KC_LEFT :
			this->_translateX = -translateSpeed;
			break;
			
		case OIS::KC_RIGHT :
			this->_translateX = translateSpeed;
			break;
	}
    
	return true;
}

bool Application::keyReleased(const OIS::KeyEvent &evt) {
	
	switch(evt.key)
	{
		case OIS::KC_UP :
		case OIS::KC_DOWN :
			this->_translateZ = 0;
			break;
			
		case OIS::KC_LEFT :
		case OIS::KC_RIGHT :
			this->_translateX = 0;
			break;
	}
	
	return true;
}

bool Application::mouseMoved(const OIS::MouseEvent &evt) {	

	float mRotateSpeed = 0.1f;

	this->gestCamera->getCamera()->yaw(Ogre::Degree(-evt.state.X.rel * mRotateSpeed));
	this->gestCamera->getCamera()->pitch(Ogre::Degree(-evt.state.Y.rel * mRotateSpeed));
		
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

