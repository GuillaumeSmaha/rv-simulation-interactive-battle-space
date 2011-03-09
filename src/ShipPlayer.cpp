#include "ShipPlayer.h"
#include "GestShip.h"
using namespace Ogre;

ShipPlayer::ShipPlayer(PlayerControls * pControl, ListenerTime * listenerTime) : ShipAbstract()
{
    this->typeObject = ObjectRoot::SHIP_PLAYER;
    this->playerControl = pControl;
	pControl->signalKeyPressed.add(&ShipPlayer::keyPressed, this);
	pControl->signalKeyReleased.add(&ShipPlayer::keyReleased, this);
	pControl->signalMouseMoved.add(&ShipPlayer::mouseMoved, this);

	this->typeCamera = CameraFixeAbstract::CAMERA_NULL;
	this->gestCamera = NULL;


    this->nodeCameraTarget = this->getNode()->createChildSceneNode("cameraTarget"+Utils::toString(Utils::unique()));
    this->nodeCameraFirstPerson = this->getNode()->createChildSceneNode("cameraFirstPerson"+Utils::toString(Utils::unique()));
	this->nodeCameraExterieureFixe = this->getNode()->createChildSceneNode("cameraExterieurFixe"+Utils::toString(Utils::unique()));


	this->nodeCameraTarget->setPosition(0, 30, 200);
	this->nodeCameraFirstPerson->setPosition(0, 30, 30);
	this->nodeCameraExterieureFixe->setPosition(0, 150, -300);

    speedCompteur= new SpeedCompteur(this, listenerTime);
	this->initCamera(CameraFixeAbstract::CAMERA_EXTERIEURE_FIXE);

    accelerationPressed = false;
    brakePressed = false;
    leftPressed = false;
    rightPressed = false;
    upPressed = false;
    downPressed = false;
    this->defineParticules();

}

ShipPlayer::~ShipPlayer(void)
{
	this->playerControl->signalKeyPressed.remove(&ShipPlayer::keyPressed, this);
	this->playerControl->signalKeyReleased.remove(&ShipPlayer::keyReleased, this);
	this->playerControl->signalMouseMoved.remove(&ShipPlayer::mouseMoved, this);

    GestSceneManager::remCamera(this->gestCamera);
	delete this->gestCamera;
}

void ShipPlayer::updatePosition(void)
{
    this->updateParticules();
    update_differente_acceleration();

    //calcule des nouvelles vitesses et positions
    this->setSpeed(this->getSpeed()+this->getAcceleration());
	this->setTranslateSpeed(this->getTranslateSpeed()+this->getTranslateAcceleration());
	//if (this->getSpeed() != 0)
	//{
		//this->moveRelative(0.0, 0.0, this->getSpeed());
	this->moveRelative(this->getTranslateSpeed(), 0.0, this->getSpeed());
	//}
    this->setRollSpeed(this->getRollSpeed()+this->getRollAcceleration());
    this->rotateRollRelative(this->getRollSpeed());

	this->setYawSpeed(this->getYawSpeed()+this->getYawAcceleration());
    this->rotateYawRelative(this->getYawSpeed());

    this->setPitchSpeed(this->getPitchSpeed()+this->getPitchAcceleration());
    this->goUp(this->getPitchSpeed());

    //on réduit chacune des accélération
    if(this->getAcceleration() > 0)
    {
		this->setAcceleration(this->getAcceleration()-0.1);
		if(this->getAcceleration() < 0)
			this->setAcceleration(0);
	}
    else if(this->getAcceleration() < 0)
    {
		this->setAcceleration(this->getAcceleration()+0.1);
		if(this->getAcceleration() > 0)
			this->setAcceleration(0);
	}

	if(this->getTranslateAcceleration() > 0)
    {
		this->setTranslateAcceleration(this->getTranslateAcceleration()-1);
		if(this->getTranslateAcceleration() < 0)
			this->setTranslateAcceleration(0);
	}
    else if(this->getTranslateAcceleration() < 0)
    {
		this->setTranslateAcceleration(this->getTranslateAcceleration()+1);
		if(this->getTranslateAcceleration() > 0)
			this->setTranslateAcceleration(0);
	}
    this->setPitchAcceleration(Ogre::Radian(0));
	this->setYawAcceleration(Ogre::Radian(0));
    this->setRollAcceleration(Ogre::Radian(0));

	//on reduit la vitesse de rotation
    if(this->getRollSpeed() > Ogre::Radian(0))
    {
		this->setRollSpeed(this->getRollSpeed()-Ogre::Radian(0.001+0.005*(1.0-this->getFactorRotation(2))));
		if(this->getRollSpeed() < Ogre::Radian(0))
			this->setRollSpeed(Ogre::Radian(0));
	}
    else if(this->getRollSpeed() < Ogre::Radian(0))
    {
		this->setRollSpeed(this->getRollSpeed()+Ogre::Radian(0.001+0.005*(1.0-this->getFactorRotation(2))));
		if(this->getRollSpeed() > Ogre::Radian(0))
			this->setRollSpeed(Ogre::Radian(0));
	}

	if(this->getYawSpeed() > Ogre::Radian(0))
    {
		this->setYawSpeed(this->getYawSpeed()-Ogre::Radian(0.001+0.005*(1.0-this->getFactorRotation(2))));
		if(this->getYawSpeed() < Ogre::Radian(0))
			this->setYawSpeed(Ogre::Radian(0));
	}
    else if(this->getYawSpeed() < Ogre::Radian(0))
    {
		this->setYawSpeed(this->getYawSpeed()+Ogre::Radian(0.001+0.005*(1.0-this->getFactorRotation(2))));
		if(this->getYawSpeed() > Ogre::Radian(0))
			this->setYawSpeed(Ogre::Radian(0));
	}

    if(this->getPitchSpeed() > Ogre::Radian(0))
    {
		this->setPitchSpeed(this->getPitchSpeed()-Ogre::Radian(0.001+0.005*(1.0-this->getFactorRotation(2))));
		if(this->getPitchSpeed() < Ogre::Radian(0))
			this->setPitchSpeed(Ogre::Radian(0));
	}
    else if(this->getPitchSpeed() < Ogre::Radian(0))
    {
		this->setPitchSpeed(this->getPitchSpeed()+Ogre::Radian(0.001+0.005*(1.0-this->getFactorRotation(2))));
		if(this->getPitchSpeed() > Ogre::Radian(0))
			this->setPitchSpeed(Ogre::Radian(0));
	}

    /*this->setAcceleration(0);
    this->setPitchAcceleration(Ogre::Radian(0));
    this->setRollAcceleration(Ogre::Radian(0));
    */
	if (Utils::distance(this->getPosition(),Ogre::Vector3(0,0,0))>10000)
	{
		this->setOrientation(0,0,0,0);
		GestSound::getSingleton()->play(GestSound::SOUND_TRAITRE);
		//Message *traitre = new Message(0);
		//traitre->Message::afficher_message("traitre","Retournez vous battre!");
	}
    this->gestCamera->update_camera();
}

void ShipPlayer::initCamera(CameraFixeAbstract::CameraType type)
{
	if(this->gestCamera == NULL && type != CameraFixeAbstract::CAMERA_NULL)
	{
		this->typeCamera = type;
		this->getEntity()->setVisible(true);

		switch(this->typeCamera)
		{
			case CameraFixeAbstract::CAMERA_NULL :
			case CameraFixeAbstract::CAMERA_FIXE :
				this->gestCamera = new CameraFixe(MeshLoader::getSingleton()->getSceneManager(), "cameraFixe"+Utils::toString(Utils::unique()));
				break;

			case CameraFixeAbstract::CAMERA_FISRT_PERSON :
				this->gestCamera = new CameraFixeTarget(MeshLoader::getSingleton()->getSceneManager(), "cameraFirstPerson"+Utils::toString(Utils::unique()), this->getNodeCameraTarget(), this->getNodeCameraFirstPerson());
				this->getEntity()->setVisible(false);
				break;

			case CameraFixeAbstract::CAMERA_EXTERIEURE_FIXE :
				this->gestCamera = new CameraFixeTarget(MeshLoader::getSingleton()->getSceneManager(), "cameraExterieureFixe"+Utils::toString(Utils::unique()), this->getNodeCameraTarget(), this->getNodeCameraExterieureFixe());
				break;
		}

		this->gestCamera->init_camera();
		GestSceneManager::addCamera(this->gestCamera);

		this->idViewport = ViewportLoader::getSingleton()->addViewport(this->gestCamera);
        this->speedCompteur->setViewport(ViewportLoader::getSingleton()->getListViewport()[this->idViewport]);
	}
}

void ShipPlayer::changeCamera(CameraFixeAbstract::CameraType type)
{
	if(this->typeCamera != type && type != CameraFixeAbstract::CAMERA_NULL)
	{
		this->typeCamera = type;
		CameraFixeAbstract * tmpGestCamera = this->gestCamera;
		this->getEntity()->setVisible(true);

		switch(this->typeCamera)
		{
			case CameraFixeAbstract::CAMERA_NULL :
			case CameraFixeAbstract::CAMERA_FIXE :
				this->gestCamera = new CameraFixe(MeshLoader::getSingleton()->getSceneManager(), "cameraFixe"+Utils::toString(Utils::unique()));
				break;

			case CameraFixeAbstract::CAMERA_FISRT_PERSON :
				this->gestCamera = new CameraFixeTarget(MeshLoader::getSingleton()->getSceneManager(), "cameraFirstPerson"+Utils::toString(Utils::unique()), this->getNodeCameraTarget(), this->getNodeCameraFirstPerson());
				this->getEntity()->setVisible(false);
				break;

			case CameraFixeAbstract::CAMERA_EXTERIEURE_FIXE :
				this->gestCamera = new CameraFixeTarget(MeshLoader::getSingleton()->getSceneManager(), "cameraExterieureFixe"+Utils::toString(Utils::unique()), this->getNodeCameraTarget(), this->getNodeCameraExterieureFixe());
				break;
		}

		this->gestCamera->init_camera();

		ViewportLoader::getSingleton()->changeCameraViewport(this->idViewport, this->gestCamera);
        GestSceneManager::addCamera(this->gestCamera);
        GestSceneManager::remCamera(tmpGestCamera);
		delete tmpGestCamera;
	}
}

void ShipPlayer::switchNextCamera(void)
{
	if(this->typeCamera == CameraFixeAbstract::CAMERA_NULL)
		this->changeCamera(CameraFixeAbstract::CAMERA_FISRT_PERSON);
	else if(this->typeCamera == CameraFixeAbstract::CAMERA_FISRT_PERSON)
		this->changeCamera(CameraFixeAbstract::CAMERA_EXTERIEURE_FIXE);
	else if(this->typeCamera == CameraFixeAbstract::CAMERA_EXTERIEURE_FIXE)
		this->changeCamera(CameraFixeAbstract::CAMERA_FISRT_PERSON);
}

void ShipPlayer::switchPrevCamera(void)
{
	if(this->typeCamera == CameraFixeAbstract::CAMERA_NULL)
		this->changeCamera(CameraFixeAbstract::CAMERA_EXTERIEURE_FIXE);
	else if(this->typeCamera == CameraFixeAbstract::CAMERA_EXTERIEURE_FIXE)
		this->changeCamera(CameraFixeAbstract::CAMERA_FISRT_PERSON);
	else if(this->typeCamera == CameraFixeAbstract::CAMERA_FISRT_PERSON)
		this->changeCamera(CameraFixeAbstract::CAMERA_EXTERIEURE_FIXE);
}



void ShipPlayer::updateParticules(void)
{
    unsigned int i = 0;
    while(GestShip::getSingleton()->getAllShips().at(i) == this)
    {
        if(GestShip::getSingleton()->getAllShips().size() > i+1)
        {
			i++;
        }

    }
    Ogre::Matrix3 m;
    this->getNode()->getOrientation().ToRotationMatrix(m);
    emitter->setDirection((GestShip::getSingleton()->getAllShips().at(i)->getNode()->getPosition() - this->getNode()->getPosition())*m);
    Ogre::Vector3 rot = emitter->getDirection();
    rot.normalise();
    emitter->setPosition(rot*80-this->getEntity()->getBoundingBox().getCenter()+Ogre::Vector3(0,0,100));
}
	
void ShipPlayer::defineParticules(void)
{

    Ogre::ParticleSystem* thrusters = MeshLoader::getSingleton()->getSceneManager()->createParticleSystem(25);
    thrusters->setMaterialName("Reactor");
    thrusters->setDefaultDimensions(10, 10);
    thrusters->setKeepParticlesInLocalSpace(true);

	// Création de 1 émetteur pour le système de particules vers l'ennemi
	for (unsigned int i = 0; i < 1; i++)
	{
		emitter = thrusters->addEmitter("Point");

		// set the emitter properties
		emitter->setAngle(Ogre::Degree(0));
		emitter->setTimeToLive(0.3);
		emitter->setEmissionRate(25);
		emitter->setParticleVelocity(200);
		emitter->setColour(Ogre::ColourValue::Red, Ogre::ColourValue::Red);
		emitter->setPosition(Ogre::Vector3(i == 0 ? 5.7 : -18, 0, 0));
	}
    this->getNode()->createChildSceneNode(Vector3(0, 6.5, -77))->attachObject(thrusters);
    ShipAbstract::defineParticules();
}




void ShipPlayer::update_differente_acceleration()
{
    if(accelerationPressed)
    {
        this->accelerate(0.2);
    }
    if(brakePressed)
    {
        this->accelerate(-0.4);
    }
    if(leftPressed)
    {
        this->rollAccelerate(Ogre::Radian(-0.009));
	    this->translateAccelerate(0.005);
    }
    if(rightPressed)
    {
        this->rollAccelerate(Ogre::Radian(0.009));
        this->translateAccelerate(-0.005);
    }
    if(upPressed)
    {
        this->pitchAccelerate(Ogre::Radian(0.003));
    }
    if(downPressed)
    {
        this->pitchAccelerate(Ogre::Radian(-0.003));
    }

}


void ShipPlayer::keyPressed(PlayerControls::Controls key)
{
    Quaternion r(Degree(90), Vector3::UNIT_X);
    Quaternion orientation;
    switch(key)
	{
		case PlayerControls::SHOOT1 :
            this->shootLaser();
            GestSound::getSingleton()->play(GestSound::SOUND_SHOOT);
            break;
		case PlayerControls::SHOOT2 :
            this->exploded();
            this->setIsDead(false);
            break;
		case PlayerControls::ACCELERATION :
            accelerationPressed = true;
            break;
        case PlayerControls::BRAKE:
            brakePressed = true;
            break;
        case PlayerControls::LEFT :
            leftPressed = true;
            break;
        case PlayerControls::RIGHT :
            rightPressed = true;
            break;
        case PlayerControls::UP :
            upPressed = true;
            break;
        case PlayerControls::DOWN :
            downPressed = true;
		default:
			break;
	}
}

void ShipPlayer::keyReleased(PlayerControls::Controls key)
{
    Quaternion r(Degree(90), Vector3::UNIT_X);
    Quaternion orientation;
    switch(key)
	{
		case PlayerControls::ACCELERATION :
            accelerationPressed = false;
            break;
        case PlayerControls::BRAKE:
            brakePressed = false;
            break;
        case PlayerControls::LEFT :
            leftPressed = false;
            break;
        case PlayerControls::RIGHT :
            rightPressed = false;
            break;
        case PlayerControls::UP :
            upPressed = false;
            break;
        case PlayerControls::DOWN :
            downPressed = false;
            break;
        case PlayerControls::SWITCH_NEXT_CAMERA :
            this->switchNextCamera();
            break;
		default:
			break;
	}
}



void ShipPlayer::mouseMoved(Ogre::Vector3 mouseVec)
{
	// TODO: Amélioreeeeeeeeeeeeeer =)

	//Quaternion rotation(Degree(-mouseVec[0] / 40.0), Vector3::UNIT_Y);

	this->pitchAccelerate(Ogre::Radian(mouseVec[1] / 8000.0));
	this->yawAccelerate(Ogre::Radian(-mouseVec[0] / 8000.0));

	//this->rollAccelerate(Ogre::Radian(mouseVec[0] / 3000.0));
	//this->getNode()->rotate(rotation);
	//this->getNode()->yaw(Radian(-mouseVec[0] / 2000.0));
	//this->getNode()->translate(-mouseVec[0] / 10.0, 0, 0);
}
