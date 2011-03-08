#include "Application.h"
//#include "HDRLogic.h"
#include "ViewportLoader.h"
using namespace Ogre;


Application::Application(void)
{
	this->root = NULL;
	this->sceneMgr = NULL;

#ifdef _DEBUG
	this->resourcesCfg = "resources_d.cfg";
	this->pluginsCfg = "plugins_d.cfg";
#else
	this->resourcesCfg = "resources.cfg";
	this->pluginsCfg = "plugins.cfg";
#endif

    this->menus = NULL;

	this->shutDown = false;

	this->isStatsOn = true;
	this->timeUntilNextToggle = 0;
}


//------------------------------------------------------------------------------

Application::~Application(void)
{

    GestLaser::getSingleton()->deleteAll();
    GestLaser::destroy();

    GestShip::getSingleton()->deleteAllShips();
    GestShip::destroy();

	GestPlanet::getSingleton()->deleteAllPlanet();
	GestPlanet::destroy();

	GestGroupAsteroids::getSingleton()->deleteAllGroupsAsteroids();
	GestGroupAsteroids::destroy();

	GestSceneManager::getSingleton()->deleteAll();

	GestSceneManager::destroy();

	GestSound::destroy();

    delete this->menus;
	delete this->player;
	delete this->player2;

	delete this->listenerMouse;
	delete this->listenerKeyboard;
	delete this->listenerTime;
	delete this->listenerFrame;
    delete this->listenerCollision;
	ViewportLoader::deleteViewportLoader();
	MeshLoader::deleteMeshLoader();

	delete this->listenerWindow;
    
	//this->root->destroySceneManager(this->sceneMgr);
    //delete this->root;
}

//------------------------------------------------------------------------------

bool Application::start(void)
{
	Utils::logFileInit("error.log");

	// construct Ogre::Root
	this->root = new Ogre::Root(this->pluginsCfg);

	// load the ressources
	this->loadRessources();

	// restore the config or show the configuration dialog and
	if(! this->root->restoreConfig() && ! this->root->showConfigDialog())
		return false;

	// initialise the system, create the default rendering window
	this->listenerWindow = new ListenerWindow(this->root, "Combat spatial");

	//create Sound singleton
	GestSound::getSingleton();

	// get the generic SceneManager
	this->sceneMgr = this->root->createSceneManager(Ogre::ST_GENERIC);

	//create SceneManager singleton
    GestSceneManager::getSingleton()->setSceneManager(this->sceneMgr);

	//init viewportLoader
	new ViewportLoader(this->listenerWindow);

	// Initialisation des ressources
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	//create Ship singleton
    GestShip::getSingleton();

	//create Laser singleton
	GestLaser::getSingleton();

	// create the scene graph
	this->initSceneGraph();

	// init the input manager and create the listeners
	this->initListeners();

    //initialise cegui
    menus= new Menus(this->listenerMouse, this->listenerKeyboard, this->player, this);
    menus->signalPaused.add(&ListenerTime::pause, this->listenerTime);

    // create the scene
	this->initScene();

	// activate debugging overlay
	debugOverlay = OverlayManager::getSingleton().getByName("Core/DebugOverlay");

	// On affiche l'overlay
	showDebugOverlay(true);

	/* Tests de HDR en cours :)
	std::vector<Viewport *> viewports = ViewportLoader::getSingleton()->getListViewport();

	Ogre::CompositorManager::getSingleton().registerCompositorLogic("HDR", new HDRLogic);
	Ogre::CompositorManager::getSingleton().addCompositor(viewports[0], "HDR", 0);
	Ogre::CompositorManager::getSingleton().setCompositorEnabled(viewports[0], "HDR", true);
	*/

	// start the scene rendering (main loop)
	this->root->startRendering();

	return true;
}

void Application::update(void *)
{


}

//------------------------------------------------------------------------------

void Application::killApplication()
{
	this->setShutDown(true);
	this->listenerFrame->shutdown();
}

void Application::killInputManager(void *)
{
	OIS::InputManager::destroyInputSystem(this->inputManager);
	this->inputManager = 0;
}

void Application::updateStats(void *)
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

		const RenderTarget::FrameStats& stats = this->listenerWindow->getRenderWindow()->getStatistics();
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

void Application::suspendre_jeux()
{
    this->player->suspendre_ecoute();
    this->player2->suspendre_ecoute();
}

void Application::redemarrer_jeux()
{
    this->player->reprendre_ecoute();
    this->player2->reprendre_ecoute();
}

void Application::restartScene(void)
{
    GestShip::getSingleton()->resetPosAllShips();
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
}


//------------------------------------------------------------------------------

void Application::initListeners(void)
{
	// Init the input system
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	this->listenerWindow->getRenderWindow()->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	this->inputManager = OIS::InputManager::createInputSystem(pl);
	this->listenerFrame = new ListenerFrame(this->root);

    this->listenerTime = new ListenerTime(25, this->listenerFrame);
	//this->listenerFrame->signalFrameEnded.add(&Application::updateStats, this);
	this->listenerTime->signalTimerElapsed.add(&Application::updateStats, this);

	this->listenerTime->signalTimerElapsed.add(&Application::update, this);

	this->listenerWindow->signalWindowClosed.add(&Application::killInputManager, this);
	this->listenerWindow->signalWindowClosed.add(&ListenerFrame::shutdown, this->listenerFrame);


	this->listenerMouse = new ListenerMouse(this->inputManager);
	this->listenerKeyboard = new ListenerKeyboard(this->inputManager);


	this->listenerWindow->setMouseControl(this->listenerMouse);
	this->listenerWindow->windowResized(this->listenerWindow->getRenderWindow());


    //this->listenerTime->signalTimerElapsed.add(&ListenerMouse::capture, this->listenerMouse);
    //this->listenerTime->signalTimerElapsed.add(&ListenerKeyboard::capture, this->listenerKeyboard);
    this->listenerFrame->signalFrameRendering.add(&ListenerMouse::capture, this->listenerMouse);
	this->listenerFrame->signalFrameRendering.add(&ListenerKeyboard::capture, this->listenerKeyboard);

	player = new PlayerControls(this->listenerMouse, this->listenerKeyboard);
	player->signalKeyPressed.add(&Application::onKeyPressed, this);
	player2 = new PlayerControls(this->listenerMouse, this->listenerKeyboard);
	player2->signalKeyPressed.add(&Application::onKeyPressed, this);

    this->listenerCollision= new ListenerCollision(this->listenerFrame);

}

void Application::initSceneGraph(void)
{
	//Groupes Vaisseaux
	this->sceneMgr->getRootSceneNode()->createChildSceneNode(NODE_NAME_GROUPE_VAISSEAUX);

	//Groupe décor
	Ogre::SceneNode * GroupeDecors = this->sceneMgr->getRootSceneNode()->createChildSceneNode(NODE_NAME_GROUPE_DECOR);
		//Groupe planetes
		GroupeDecors->createChildSceneNode(NODE_NAME_GROUPE_DECOR_GROUPE_PLANETES);
		//Groupe soleils
		GroupeDecors->createChildSceneNode(NODE_NAME_GROUPE_DECOR_GROUPE_SOLEILS);

	//Ensemble de groupes d'astéroides
	this->sceneMgr->getRootSceneNode()->createChildSceneNode(NODE_NAME_ENSEMBLE_GROUPE_ASTEROIDES);

	//Groupe lasers
	this->sceneMgr->getRootSceneNode()->createChildSceneNode(NODE_NAME_GROUPE_LASERS);

	//Groupe missiles
	this->sceneMgr->getRootSceneNode()->createChildSceneNode(NODE_NAME_GROUPE_MISSILES);
}


void Application::initScene(void)
{
	// Mise en place du SkyBox "Etoiles"
	this->sceneMgr->setSkyBox(true, "SpaceSkyBox", 5000);

	// constructeur: Planet(rayonPlanete, typePlanete, avec_atmosphere)

	Planet *planet1 = new Planet(10000, true);
	//planet1->getEntity()->setQueryFlags(PLANET_QUERY_MASK);
    planet1->setPosition(2500.0, 300.0, 22500.0);
	
	
	//Tingshuo Debut
	//planet1->getEntity()->setQueryFlags(PLANET_QUERY_MASK);
	//planet1->getEntity()->setCastShadows(true);
	//const Ogre::Vector3 pos(2500.0, 300.0, 22500.0);
	//Ogre::Vector3 size = planet1->getEntity()->getBoundingBox().getSize();
	//size *= 0.60;
	//OgreBulletDynamics::RigidBody *body = this->listenerFrame->addSphere(planet1->getEntity(), planet1->getNode(), pos, Quaternion(0,0,0,1),
	//	size.x, 1.0, 1.0, 0.0);
	//Tingshuo Fin


	//planet1->setScale(150.0, 150.0, 150.0);

	Planet *planet2 = new Planet(2500, 2, false);
	planet2->setPosition(20000.0, 900.0, 15000.0);
	//planet2->setScale(200.0, 200.0, 200.0);
    
    planet1->createCollisionObject(this->listenerCollision);
    planet2->createCollisionObject(this->listenerCollision);


	GestPlanet::getSingleton()->addPlanet(planet1);
	GestPlanet::getSingleton()->addPlanet(planet2);


	ShipPlayer * ship = new ShipPlayer(this->player, listenerTime);
    ship->setPosition(-500,-500,-500);
    
	ship->createCollisionObject(this->listenerCollision);
    //Tingshuo Debut
//	ship->getEntity()->setQueryFlags(SHIP_QUERY_MASK);
//
//	ship->getEntity()->setCastShadows(true);
//	const Ogre::Vector3 pos_ship(-50,-50,-50);
//	Ogre::Vector3 size_ship = ship->getEntity()->getBoundingBox().getSize();
//	size_ship *= 0.48;
//	OgreBulletDynamics::RigidBody *body_ship = this->listenerFrame->addSphere(ship->getEntity(), ship->getNode(), pos_ship, Quaternion(0,0,0,1),
//		size_ship.x, 1.0, 1.0, 0.0);
	//Tingshuo Fin
	//ship->setOrientation(5, 5, 5, 5);
	GestShip::getSingleton()->addShip(ship);

/*
	ShipPlayer * ship2 = new ShipPlayer(this->player2, listenerTime);
    ship2->setPosition(-130,0,0);
    ship2->touched();
    GestShip::getSingleton()->addShip(ship2);
*/

    ShipIA * ship3 = new ShipIA();
    ship3->setPosition(130,0,10000);
//    ship3->getNode()->setRotate(Ogre::Vector3(0,0,180));
    //ship3->getNode()->setScale(Ogre::Vector3(50,50,50));
    ship3->touched();
    GestShip::getSingleton()->addShip(ship3);
    Ogre::BillboardSet * bill = this->sceneMgr->createBillboardSet("test", 1);
    //~ Ogre::Billboard * board = bill->createBillboard(Ogre::Vector3(0,0,0), ColourValue::White);
    bill->createBillboard(Ogre::Vector3(0,0,0), ColourValue::White);
    bill->setMaterialName("test");
   // bill->setColor(ColourValue::Red);
    ship3->getNode()->attachObject(bill);
	//création de la ceinture d'asteroids
	GestGroupAsteroids::getSingleton()->createGroup(32,100,Ogre::Radian(0.01),planet2->getMInnerRadius(), planet2->getNode(), 0.05);
	//création de 4 asteroids se balandant dans l'espace (autour de la terre)
	GestGroupAsteroids::getSingleton()->createGroup(4,10000,Ogre::Radian(0.01),planet1->getMInnerRadius()*3, planet1->getNode(), 0.05);


	//this->listenerTime->signalTimerElapsed.add(&GestPlanet::updatePlanet,GestPlanet::getSingleton());
    this->listenerTime->signalTimerElapsed.add(&GestShip::updateShips, GestShip::getSingleton());
    this->listenerTime->signalTimerElapsed.add(&GestLaser::updateLasers, GestLaser::getSingleton());
    this->listenerTime->signalTimerElapsed.add(&GestGroupAsteroids::updateGroupsAsteroids, GestGroupAsteroids::getSingleton());

	// A faire dans listenerFrame car listenerTime trop lent !!
	this->listenerFrame->signalFrameEnded.add(&GestPlanet::updatePlanet, GestPlanet::getSingleton());



//Temporaire :
    // Set ambient light
    //this->sceneMgr->setAmbientLight(Ogre::ColourValue(1.0, 1.0, 1.0));
	this->sceneMgr->setAmbientLight(Ogre::ColourValue::Black);
    // Create a light
    Ogre::Light* l = this->sceneMgr->createLight("Sun");
	l->setType(Ogre::Light::LT_POINT);
	l->setDiffuseColour(1.0, 1.0, 1.0);
	l->setSpecularColour(1.0, 1.0, 1.0);
    //l->setPosition(320,480,500);
	l->setPosition(32, 48, -5000);
	l->setDirection(Ogre::Vector3::UNIT_Z);
	//l->setType(Light::LT_POINT);
	Ogre::SceneNode * nodeLight1 = this->sceneMgr->getRootSceneNode()->createChildSceneNode("NodeLight1");
	nodeLight1->attachObject(l);


}

void Application::onKeyPressed(PlayerControls::Controls key)
{
	switch(key)
	{
		case PlayerControls::QUIT :
			this->killApplication();
			break;

		default:
			break;
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
