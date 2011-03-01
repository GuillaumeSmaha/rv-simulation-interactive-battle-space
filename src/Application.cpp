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

    this->menus=NULL;
    //this->gestShip= NULL;

	this->shutDown = false;

	this->isStatsOn = true;
	this->timeUntilNextToggle = 0;
}


//------------------------------------------------------------------------------

Application::~Application(void)
{

    GestShip::getSingleton()->deleteAllShips();
    GestShip::destroy();

//    gestShip->deleteAllShips();
//    delete this->gestShip;

	GestPlanet::getSingleton()->deleteAllPlanet();
	GestPlanet::destroy();
	//gestPlanet->deleteAllPlanet();
	//delete this->gestPlanet;

	//gestGroupAsteroids->deleteAllGroupsAsteroids();
	GestGroupAsteroids::getSingleton()->deleteAllGroupsAsteroids();
	GestGroupAsteroids::destroy();

	GestSceneManager::getSingleton()->deleteAll();

	GestSceneManager::destroy();

    delete this->menus;
	//delete this->gestGroupAsteroids;
	delete this->player;
	delete this->player2;

	delete this->listenerMouse;
	delete this->listenerKeyboard;
	delete this->listenerFrame;
	delete this->listenerTime;

	ViewportLoader::deleteViewportLoader();
	MeshLoader::deleteMeshLoader();

	//delete this->listenerWindow;

    delete this->root;
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
	//this->window = this->root->initialise(true, "Combat spatial");


	// get the generic SceneManager
	this->sceneMgr = this->root->createSceneManager(Ogre::ST_GENERIC);

    GestSceneManager::getSingleton()->setSceneManager(this->sceneMgr);
	//init meshLoader
	//new MeshLoader();

	//init viewportLoader
	new ViewportLoader(this->listenerWindow);

	// Initialisation des ressources
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

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
void Application::update(void*)
{


}
void Application::updateStats(void*)
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

void Application::killApplication()
{
	this->setShutDown(true);
	this->listenerFrame->shutdown();
}

void Application::killInputManager(void*)
{
	OIS::InputManager::destroyInputSystem(this->inputManager);
	this->inputManager = 0;
	//this->listenerFrame->shutdown();
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

    //this->listenerTime->signalTimerElapsed.add(&ListenerMouse::capture, this->listenerMouse);
    //this->listenerTime->signalTimerElapsed.add(&ListenerKeyboard::capture, this->listenerKeyboard);
    this->listenerFrame->signalFrameRendering.add(&ListenerMouse::capture, this->listenerMouse);
	this->listenerFrame->signalFrameRendering.add(&ListenerKeyboard::capture, this->listenerKeyboard);

	//Test * t = new Test(4);
	//t->add(this->listenerFrame, this->listenerMouse);

   // this->listenerFrame->signalFrameRendering.add(&ListenerKeyboard::capture, this->listenerKeyboard);

    // capture value of each device
    //this->app->getListenerMouse()->getMouse()->capture();
	//this->app->getListenerKeyboard()->getKeyboard()->capture();

	player = new PlayerControls(this->listenerMouse, this->listenerKeyboard);
	player->signalKeyPressed.add(&Application::onKeyPressed, this);


}

void Application::onKeyPressed(PlayerControls::Controls key)
{
	switch(key)
	{
		case PlayerControls::QUIT :
			this->killApplication();
			break;
	}
}

void Application::restartScene(void)
{
    GestShip::getSingleton()->resetPosAllShips();
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



	// constructeur: Planet(rayonPlanete, typePlanete, avec_atmosphere)
	Planet *planet1 = new Planet(10000, true);
	planet1->setPosition(2500.0, 300.0, 22500.0);
	//planet1->setScale(150.0, 150.0, 150.0);

	Planet *planet2 = new Planet(2500, 2, false);
	planet2->setPosition(20000.0, 900.0, 15000.0);
	//planet2->setScale(200.0, 200.0, 200.0);

	GestPlanet::getSingleton()->addPlanet(planet1);
	GestPlanet::getSingleton()->addPlanet(planet2);
    GestShip::getSingleton();


	ShipPlayer * ship = new ShipPlayer(this->player);
    ship->setPosition(-50,-50,-50);
    //ship->setOrientation(5, 5, 5, 5);

	/*ShipPlayer * ship2 = new ShipPlayer(this->player2);
    ship2->setPosition(-130,0,0);
    ship2->touched();*/

    ShipIA * ship3 = new ShipIA();
    ship3->setPosition(130,0,0);
    ship3->touched();
//    Utils::logFile("test");
//    GestShip::getS
    GestShip::getSingleton()->addShip(ship);
    //gestShip->addShip(ship2);
    GestShip::getSingleton()->addShip(ship3);
    //Utils::log("test2");

	//coordonnée du centre de la ceinture d'asteroids
	Vector3 vec;
	vec[0]=0;
	vec[1]=0;
	vec[2]=0;
	//création de la ceinture d'asteroids
	GestGroupAsteroids::getSingleton()->createGroup(20,Ogre::Radian(0.01),100,vec,0.01);

	//this->listenerTime->signalTimerElapsed.add(&GestPlanet::updatePlanet,GestPlanet::getSingleton());
    this->listenerTime->signalTimerElapsed.add(&GestShip::updateShips,GestShip::getSingleton());
    this->listenerTime->signalTimerElapsed.add(&GestGroupAsteroids::updateGroupsAsteroids,GestGroupAsteroids::getSingleton());

	// A faire dans listenerFrame car listenerTime trop lent !!
	this->listenerFrame->signalFrameEnded.add(&GestPlanet::updatePlanet,GestPlanet::getSingleton());

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


void Application::suspendre_jeux()
{
    this->player->suspendre_ecoute();
}

void Application::redemarrer_jeux()
{
    this->player->reprendre_ecoute();
}
