#include "Application.h"


using namespace Ogre;

Application::Application(void) {
	this->root = NULL;
	this->sceneMgr = NULL;

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
	
	this->isStatsOn = true;
	this->timeUntilNextToggle = 0;
}


//------------------------------------------------------------------------------

Application::~Application(void)
{
	// remove ourself as a Window listener
	delete this->listenerKeyboard;
	delete this->listenerKeyboard;
	
	Ogre::WindowEventUtilities::removeWindowEventListener(this->window, this);
	windowClosed(this->window);
}

//------------------------------------------------------------------------------

bool Application::start(void)
{
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

	// Initialisation des ressources
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

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
	// init the input manager and create the listeners
	this->initListeners();

	// create one viewport, entire window
	// use the same color for the fog and viewport background
	Ogre::Viewport * viewPort = this->window->addViewport(this->gestCamera->getCamera(), 0);
	viewPort->setBackgroundColour(Ogre::ColourValue(0.0f, 0.0f, 0.0f));
	this->gestCamera->getCamera()->setAspectRatio(Ogre::Real(viewPort->getActualWidth()) / Ogre::Real(viewPort->getActualHeight()));

	// activate debugging overlay
	debugOverlay = OverlayManager::getSingleton().getByName("Core/DebugOverlay");

	// On affiche l'overlay
	showDebugOverlay(true);
	
	// start the scene rendering (main loop)
	this->root->startRendering();

	return true;
}


//------------------------------------------------------------------------------

void Application::loadRessources(void)
{
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

	/* Fait dans le start() sinon plantage car il faut laisser du temps aux 
	 * ressources de se charger.
	 */
	//Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}


//------------------------------------------------------------------------------

void Application::initListeners(void)
{
	// Init the input system
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	this->window->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	this->inputManager = OIS::InputManager::createInputSystem(pl);

	this->listenerKeyboard = new ListenerKeyboard(this->inputManager, this);
    //this->root->addFrameListener(new ListenerFrame(this->listenerKeyboard, new ListenerMouse(this->inputManager, this->gestCamera),this));
	
	// Set initial mouse clipping size
	windowResized(this->window);

	// Register the listeners
	Ogre::WindowEventUtilities::addWindowEventListener(this->window, this);
	this->root->addFrameListener(this);
	//this->mouse->setEventCallback(this);
	//this->keyboard->setEventCallback(this);
	//this->keyboard->setEventCallback(new ListenerKeyboard());
}


void Application::initSceneGraph(void)
{

	//Groupes Vaisseaux
	Ogre::SceneNode * GroupeVaisseaux = this->sceneMgr->getRootSceneNode()->createChildSceneNode(NODE_NAME_GROUPE_VAISSEAUX);
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
	Ogre::SceneNode * GroupeDecors = this->sceneMgr->getRootSceneNode()->createChildSceneNode(NODE_NAME_GROUPE_DECOR);
		//Groupe planetes
		Ogre::SceneNode * GroupeDecors_GroupePlanete = GroupeDecors->createChildSceneNode(NODE_NAME_GROUPE_DECOR_GROUPE_PLANETES);
		//Groupe soleils
		Ogre::SceneNode * GroupeDecors_GroupeSoleil = GroupeDecors->createChildSceneNode(NODE_NAME_GROUPE_DECOR_GROUPE_SOLEILS);

	//Ensemble de groupes d'astéroides
	Ogre::SceneNode * EnsembleGroupesAsteroides = this->sceneMgr->getRootSceneNode()->createChildSceneNode(NODE_NAME_ENSEMBLE_GROUPE_ASTEROIDES);
}


void Application::initScene(void)
{

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


    Ogre::Entity * planet = MeshLoader::getSingleton()->getNodedEntity(MeshLoader::PLANET, true);
	planet->getParentSceneNode()->setPosition(1300,1300,15300);
	planet->getParentSceneNode()->setScale(35,35,35);

//	MeshLoader::getSingleton()->getNodedEntity(MeshLoader::PLANET, true)->getParentSceneNode()->setPosition(300,300,300);
	MeshLoader::getSingleton()->getNodedEntity(MeshLoader::PLANET, true)->getParentSceneNode()->setPosition(300,-300,-300);
	MeshLoader::getSingleton()->getNodedEntity(MeshLoader::PLANET, true)->getParentSceneNode()->setPosition(-300,300,300);

		//MeshLoader::getSingleton()->getNodedEntity(MeshLoader::PLANET3)->getParentSceneNode()->setScale(10,10,10);
	//MeshLoader::getSingleton()->getNodedEntity(MeshLoader::PLANET)->getParentSceneNode()->setScale(10,10,10);
	/*
	Ogre::Entity *sphere = sceneMgr->createEntity("name", "Prefab_Sphere");
	sphere->setMaterialName("pluton");*/

//	this->sceneMgr->getSceneNode("GroupeDecors")->createChildSceneNode("vsx2ssss")->attachObject(sphere);
	//shete
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
    //l->setPosition(320,480,500);
	l->setPosition(32,48,50);
	//l->setType(Light::LT_POINT);
	Ogre::SceneNode * nodeLight1 = this->sceneMgr->getRootSceneNode()->createChildSceneNode("NodeLight1");
	nodeLight1->attachObject(l);
}

//------------------------------------------------------------------------------

void Application::updateStats(void)
{
	static String currFps = "Current FPS: ";
	static String avgFps = "Average FPS: ";
	static String bestFps = "Best FPS: ";
	static String worstFps = "Worst FPS: ";
	static String tris = "Triangle Count: ";
	static String batches = "Batch Count: ";

	// update stats when necessary
	try {
		OverlayElement* guiAvg = OverlayManager::getSingleton().getOverlayElement("Core/AverageFps");
		OverlayElement* guiCurr = OverlayManager::getSingleton().getOverlayElement("Core/CurrFps");
		OverlayElement* guiBest = OverlayManager::getSingleton().getOverlayElement("Core/BestFps");
		OverlayElement* guiWorst = OverlayManager::getSingleton().getOverlayElement("Core/WorstFps");

		const RenderTarget::FrameStats& stats = this->window->getStatistics();
		guiAvg->setCaption(avgFps + StringConverter::toString(stats.avgFPS));
		guiCurr->setCaption(currFps + StringConverter::toString(stats.lastFPS));
		guiBest->setCaption(bestFps + StringConverter::toString(stats.bestFPS)
			+" "+StringConverter::toString(stats.bestFrameTime)+" ms");
		guiWorst->setCaption(worstFps + StringConverter::toString(stats.worstFPS)
			+" "+StringConverter::toString(stats.worstFrameTime)+" ms");

		OverlayElement* guiTris = OverlayManager::getSingleton().getOverlayElement("Core/NumTris");
		guiTris->setCaption(tris + StringConverter::toString(stats.triangleCount));

		OverlayElement* guiBatches = OverlayManager::getSingleton().getOverlayElement("Core/NumBatches");
		guiBatches->setCaption(batches + StringConverter::toString(stats.batchCount));

		OverlayElement* guiDbg = OverlayManager::getSingleton().getOverlayElement("Core/DebugText");
		guiDbg->setCaption(debugText);
	}
	catch(...) { /* ignore */ }
}

//------------------------------------------------------------------------------

void Application::showDebugOverlay(bool show)
{
	if (debugOverlay)
	{
		if (show)
			debugOverlay->show();
		else
			debugOverlay->hide();
	}
}

//------------------------------------------------------------------------------

bool Application::frameRenderingQueued(const Ogre::FrameEvent& evt) {
	
	// Stop the rendering if the window was closed, or the application stoped
	if(this->window->isClosed() || this->shutDown)
		return false;

    // capture value of each device
	//this->listenerKeyboard->getKeyboard()->capture();
    //this->listenerMouse->getMouse()->capture();

	if (timeUntilNextToggle >= 0)
		timeUntilNextToggle -= evt.timeSinceLastFrame;
    
    this->gestCamera->getCamera()->moveRelative( Ogre::Vector3(this->_translateX, 0.0f, this->_translateZ) );

	return true;
}

//------------------------------------------------------------------------------

bool Application::frameEnded(const Ogre::FrameEvent& evt)
{
	updateStats();
	return true;
}

//------------------------------------------------------------------------------

void Application::windowResized(Ogre::RenderWindow *rw)
{
	unsigned int width, height, depth;
	int left, top;

	// Adjust mouse clipping area
	rw->getMetrics(width, height, depth, left, top); 
	//const OIS::MouseState &ms = this->mouse->getMouseState();
	//ms.width = width;
	//ms.height = height;

}
 
void Application::windowClosed(Ogre::RenderWindow *rw)
{
	// Only close for window that created OIS (the main window)
	if(rw == this->window)
	{
		if(this->inputManager)
		{
			// Unattach OIS before window shutdown (very important under Linux)
			//this->inputManager->destroyInputObject(this->mouse);
			//this->inputManager->destroyInputObject(this->keyboard);
 
			OIS::InputManager::destroyInputSystem(this->inputManager);
			this->inputManager = 0;
		}
	}

}

//------------------------------------------------------------------------------

int main(void)
{
	Application appli;

	try {
	    appli.start();
	} catch( Ogre::Exception& e ) {
		std::cerr << "An exception has occured: " << e.getFullDescription().c_str() << std::endl;
		return 1;
	}

	return 0;
}

