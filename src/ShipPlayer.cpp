#include "ShipPlayer.h"
#include "GestShip.h"
using namespace Ogre;

ShipPlayer::ShipPlayer(PlayerControls * pControl, ListenerTime * listenerTime) : ShipAbstract()
{
    this->isAutoPiloted = false;
    shootDelay = 0 ;
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

    compteur = new Compteur(this, listenerTime);
	this->initCamera(CameraFixeAbstract::CAMERA_EXTERIEURE_FIXE);

    accelerationPressed = false;
    brakePressed = false;
    leftPressed = false;
    rightPressed = false;
    upPressed = false;
    downPressed = false;

	this->setColorLaser(Ogre::ColourValue::Green);

    this->defineParticules();
}

ShipPlayer::~ShipPlayer(void)
{
	this->playerControl->signalKeyPressed.remove(&ShipPlayer::keyPressed, this);
	this->playerControl->signalKeyReleased.remove(&ShipPlayer::keyReleased, this);
	this->playerControl->signalMouseMoved.remove(&ShipPlayer::mouseMoved, this);

    GestSceneManager::remCamera(this->gestCamera);
}

void ShipPlayer::updatePosition(void)
{
    this->updateParticules();
    update_differente_acceleration();

    if(this->isAutoPiloted)
    {
		thrusters->getEmitter(0)->setParticleVelocity(5+speed);
		thrusters->getEmitter(1)->setParticleVelocity(5+speed);
		Ogre::Vector3 direction = this->getNode()->_getDerivedPosition()-this->destination;
		//commenté pke bouffeur de FPS = les particules ne meurent pas

		if(direction.squaredLength()<40000000 && shootDelay--<=0)
		{
			if(!this->getIsDead())
				this->shootLaser();
			shootDelay = 15;
		}

		//Se tourne vers nous plus ou moins (mRotFactor == vitesse à laquelle c fait et avant que le vsx change de destination => inversement proportionnel)
		if(mRotating)
		{
			mRotProgress += mRotFactor;
			if(mRotProgress>1)
			{
				int iRand = Utils::randRangeInt(0, GestShip::getSingleton()->getAllShips(ObjectRoot::SHIP_IA).size()-1);
				this->destination = GestShip::getSingleton()->getAllShips(ObjectRoot::SHIP_IA).at(iRand)->getNode()->_getDerivedPosition()+Ogre::Vector3(Utils::randRangeInt(-10000,10000),Utils::randRangeInt(-10000,10000),Utils::randRangeInt(-10000,10000));
				mRotating = false;
				mRotating = true;
				mRotFactor = 1.0f / mRotFrames;
				mOrientSrc = this->getNode()->getOrientation();
				Ogre::Quaternion quat =  (this->getNode()->getOrientation()* Vector3::UNIT_Z).getRotationTo(    this->destination-this->getNode()->_getDerivedPosition());
				mOrientDest = quat * mOrientSrc;           // We want dest orientation, not a relative rotation (quat)
				mRotProgress = 0;
			}
			else
			{
				//rotation
				Quaternion delta = Quaternion::Slerp(mRotProgress, mOrientSrc, mOrientDest, true);
				this->getNode()->setOrientation(delta);
			}
		}
        //si on est encore loin on avance
        if(direction.squaredLength()>4000000)
        {
            this->setSpeed(speed);

        }else{
            this->setSpeed(0);
        }
        /*
             if (this->getSpeed() != 0)
            {
                this->moveRelative(0.0, 0.0, this->getSpeed());
            }*/
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

    }
	else
    {

        thrusters->getEmitter(0)->setParticleVelocity(5+this->getSpeed());
        thrusters->getEmitter(1)->setParticleVelocity(5+this->getSpeed());
        //calcule des nouvelles vitesses et positions
        this->setSpeed(this->getSpeed()+this->getAcceleration());
        this->setTranslateSpeed(this->getTranslateSpeed()+this->getTranslateAcceleration());
        //if (this->getSpeed() != 0)
        //{
            //this->moveRelative(0.0, 0.0, this->getSpeed());
		if(this->typeCamera == CameraFixeAbstract::CAMERA_FIXE)
			this->moveRelative(this->getTranslateSpeed(), 0.0, -this->getSpeed());
		else
			this->moveRelative(this->getTranslateSpeed(), 0.0, this->getSpeed());
		//}
		this->setRollSpeed(this->getRollSpeed()+this->getRollAcceleration());
		this->rotateRollRelative(this->getRollSpeed());

		this->setYawSpeed(this->getYawSpeed()+this->getYawAcceleration());
		this->rotateYawRelative(this->getYawSpeed());

		this->setPitchSpeed(this->getPitchSpeed()+this->getPitchAcceleration());
		
		if(this->typeCamera == CameraFixeAbstract::CAMERA_FIXE)
			this->goUp(-this->getPitchSpeed());
		else
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
    }
    /**/
    check_out_of_battle();

    this->gestCamera->update_camera();
	//this->gestCamera->update_particles();
}


void ShipPlayer::check_out_of_battle(void){

	static int playSound = 100;
	if (Utils::distance(this->getPosition(),Ogre::Vector3(0,0,0))>50000)
	{
		if (playSound >= 100)
		{
			playSound = 0;
			this->isTouch(5);
			GestSound::getSingleton()->play(GestSound::SOUND_TRAITRE);
		}
		else
		{
			playSound++;
		}
		//Message *traitre = new Message(0);
		//traitre->Message::afficher_message("traitre","Retournez vous battre!");
	}
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
				this->gestCamera = new CameraFixe(MeshLoader::getSingleton()->getSceneManager(), "cameraFixe"+Utils::toString(Utils::unique()), this->getNode());
				this->isAutoPiloted = false;
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
        this->compteur->setViewport(ViewportLoader::getSingleton()->getListViewport()[this->idViewport]);
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
				this->gestCamera = new CameraFixe(MeshLoader::getSingleton()->getSceneManager(), "cameraFixe"+Utils::toString(Utils::unique()), this->getNode());
				this->isAutoPiloted = false;
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
		this->changeCamera(CameraFixeAbstract::CAMERA_FIXE);
	else if(this->typeCamera == CameraFixeAbstract::CAMERA_FIXE)
		this->changeCamera(CameraFixeAbstract::CAMERA_FISRT_PERSON);
}

void ShipPlayer::switchPrevCamera(void)
{
	if(this->typeCamera == CameraFixeAbstract::CAMERA_NULL)
		this->changeCamera(CameraFixeAbstract::CAMERA_EXTERIEURE_FIXE);
	else if(this->typeCamera == CameraFixeAbstract::CAMERA_EXTERIEURE_FIXE)
		this->changeCamera(CameraFixeAbstract::CAMERA_FISRT_PERSON);
	else if(this->typeCamera == CameraFixeAbstract::CAMERA_FISRT_PERSON)
		this->changeCamera(CameraFixeAbstract::CAMERA_FIXE);
	else if(this->typeCamera == CameraFixeAbstract::CAMERA_FIXE)
		this->changeCamera(CameraFixeAbstract::CAMERA_EXTERIEURE_FIXE);
}



void ShipPlayer::updateParticules(void)
{
    int i = 0;
    int j = -1;
    Ogre::Real dist = -1;
    Ogre::Real distCurrent;

    for(i=GestShip::getSingleton()->getAllShips(ObjectRoot::SHIP_IA).size()-1; i>=0;i--)
    {
       distCurrent = GestShip::getSingleton()->getAllShips(ObjectRoot::SHIP_IA).at(i)->getNode()->getPosition().squaredDistance(this->getNode()->getPosition());
       if(dist<0 || distCurrent < dist)
       {
            dist = distCurrent;
            j = i;
       }
    }

    if(j>-1)
    {
        Ogre::Matrix3 m;
        this->getNode()->getOrientation().ToRotationMatrix(m);
        emitter->setDirection((GestShip::getSingleton()->getAllShips(ObjectRoot::SHIP_IA).at(j)->getNode()->getPosition() - this->getNode()->getPosition())*m);
        Ogre::Vector3 rot = emitter->getDirection();
        rot.normalise();
        emitter->setPosition(rot*80-this->getEntity()->getBoundingBox().getCenter()+Ogre::Vector3(0,0,100));
    }


    dist = -1;
    //~ distCurrent;

    for(i=GestShip::getSingleton()->getAllShips(ObjectRoot::SHIP_BATTLE_STATION).size()-1; i>=0;i--)
    {
       distCurrent = GestShip::getSingleton()->getAllShips(ObjectRoot::SHIP_BATTLE_STATION).at(i)->getNode()->getPosition().squaredDistance(this->getNode()->getPosition());
       if(dist<0 || distCurrent < dist)
       {
            dist = distCurrent;
            j = i;
       }
    }

    if(j>-1)
    {
        Ogre::Matrix3 m;
        this->getNode()->getOrientation().ToRotationMatrix(m);
        emitterFriend->setDirection((GestShip::getSingleton()->getAllShips(ObjectRoot::SHIP_BATTLE_STATION).at(j)->getNode()->getPosition() - this->getNode()->getPosition())*m);
        Ogre::Vector3 rot = emitterFriend->getDirection();
        rot.normalise();
        emitterFriend->setPosition(rot*80-this->getEntity()->getBoundingBox().getCenter()+Ogre::Vector3(0,0,100));
    }

}

void ShipPlayer::defineParticules(void)
{

    Ogre::ParticleSystem* thrusters = MeshLoader::getSingleton()->getSceneManager()->createParticleSystem(25);
    thrusters->setMaterialName("Reactor");
    thrusters->setDefaultDimensions(10, 10);
    thrusters->setKeepParticlesInLocalSpace(true);

	// Création de 1 émetteur pour le système de particules vers l'ennemi

    emitter = thrusters->addEmitter("Point");
    // set the emitter properties
    emitter->setAngle(Ogre::Degree(0));
    emitter->setTimeToLive(0.3);
    emitter->setEmissionRate(25);
    emitter->setParticleVelocity(200);
    emitter->setColour(Ogre::ColourValue::Red, Ogre::ColourValue::Red);

    emitterFriend = thrusters->addEmitter("Point");
    // set the emitter properties
    emitterFriend->setAngle(Ogre::Degree(0));
    emitterFriend->setTimeToLive(0.3);
    emitterFriend->setEmissionRate(25);
    emitterFriend->setParticleVelocity(200);
    emitterFriend->setColour(Ogre::ColourValue::White, Ogre::ColourValue::White);


    this->getNode()->createChildSceneNode(Vector3(0, 6.5, -77))->attachObject(thrusters);
    ShipAbstract::defineParticules();
}




void ShipPlayer::update_differente_acceleration()
{
    if(!this->isAutoPiloted)
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
         //   this->exploded();
          //  this->setIsDead(false);
          this->switchAutopilote();
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
    if(!this->isAutoPiloted)
    {
        this->pitchAccelerate(Ogre::Radian(mouseVec[1] / 8000.0));
        this->yawAccelerate(Ogre::Radian(-mouseVec[0] / 8000.0));
	}

	//this->rollAccelerate(Ogre::Radian(mouseVec[0] / 3000.0));
	//this->getNode()->rotate(rotation);
	//this->getNode()->yaw(Radian(-mouseVec[0] / 2000.0));
	//this->getNode()->translate(-mouseVec[0] / 10.0, 0, 0);
}



Ogre::Real ShipPlayer::getFactorRotation(int method)
{
	Ogre::Real factor;
	Ogre::Real ratio = this->getSpeed()/ShipAbstract::MAXSPEED;
	if(method == 2)
	{
		factor = ratio*ratio*ratio;
		//~ factor = std::min(1.0, std::max(0.0, ratio*ratio*ratio*0.5+0.5));
	}
	else
	{
		if(ratio < 0.01)
		{
			factor = 0.0;
		}
		else
		{
			if(this->typeCamera == CameraFixeAbstract::CAMERA_FIXE)
				return 1.0;
			//~ factor = (log10(ratio)+2.0)/2.0;
			factor = std::min(1.0, std::max(0.0, ((log10(ratio)+2.0)/2.0) * 0.25 + 0.75));
		}
	}

	return factor;
}

void ShipPlayer::moveRelative(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z)
{
	if(this->typeCamera == CameraFixeAbstract::CAMERA_FIXE)
	{
		this->gestCamera->getCamera()->moveRelative(Ogre::Vector3(x, y, z));
		return;
	}
	Ogre::Vector3 vec = Ogre::Vector3(x, y, z);
	this->moveRelative(vec);
}

void ShipPlayer::moveRelative(const Ogre::Vector3 &vec)
{
	if(this->typeCamera == CameraFixeAbstract::CAMERA_FIXE)
	{
		this->gestCamera->getCamera()->moveRelative(vec);
		return;
	}
	Vector3 trans = this->getOrientation() * vec;
	Vector3 pos = this->getPosition() + trans;
	this->setPosition(pos[0], pos[1], pos[2]);
}

void ShipPlayer::rotateRollRelative(const Ogre::Radian w)
{
	if(this->typeCamera == CameraFixeAbstract::CAMERA_FIXE)
	{
		this->gestCamera->getCamera()->roll(w);
		return;
	}
    this->entity->getParentNode()->roll(w);
}

void ShipPlayer::rotateYawRelative(const Ogre::Radian w)
{
	if(this->typeCamera == CameraFixeAbstract::CAMERA_FIXE)
	{
		this->gestCamera->getCamera()->yaw(w);
		return;
	}
    this->entity->getParentNode()->yaw(w);
}

void ShipPlayer::goUp(const Ogre::Radian w)
{
	if(this->typeCamera == CameraFixeAbstract::CAMERA_FIXE)
	{
		this->gestCamera->getCamera()->pitch(w);
		return;
	}
    this->entity->getParentNode()->pitch(w);
}


Quaternion ShipPlayer::getOrientation(void)
{
	if(this->typeCamera == CameraFixeAbstract::CAMERA_FIXE)
	{
		return this->gestCamera->getCamera()->getOrientation();
	}
	return this->getNode()->getOrientation();
}

void ShipPlayer::setOrientation(const Ogre::Quaternion &q)
{
	if(this->typeCamera == CameraFixeAbstract::CAMERA_FIXE)
	{
		this->gestCamera->getCamera()->setOrientation(q);
		return;
	}
    if(firstDir)
    {
        dirInit = q;
        firstDir = false;
    }
	this->getNode()->setOrientation(q);
}

void ShipPlayer::setOrientation(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z, const Ogre::Real a)
{
	if(this->typeCamera == CameraFixeAbstract::CAMERA_FIXE)
	{
		this->gestCamera->getCamera()->setOrientation(Ogre::Quaternion(x, y, z, a));
		return;
	}
    if(firstDir)
    {
        dirInit = Quaternion(x,y,z,a);
        firstDir = false;
    }
	this->getNode()->setOrientation(x, y, z, a);
}


Ogre::Vector3 ShipPlayer::getPosition(void)
{
	if(this->typeCamera == CameraFixeAbstract::CAMERA_FIXE)
	{
		return this->gestCamera->getCamera()->getPosition();
	}
    return this->getNode()->getPosition();
}

void ShipPlayer::setPosition(const Ogre::Vector3 &v)
{
	if(this->typeCamera == CameraFixeAbstract::CAMERA_FIXE)
	{
		this->gestCamera->getCamera()->setPosition(v);
		return;
	}
    if(firstPos)
    {
        posInit = v;
        firstPos = false;
    }
    this->getNode()->setPosition(v);
}

void ShipPlayer::setPosition(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z)
{
	if(this->typeCamera == CameraFixeAbstract::CAMERA_FIXE)
	{
		this->gestCamera->getCamera()->setPosition(x, y, z);
		return;
	}
    if(firstPos)
    {
        posInit[0] = x;
        posInit[1] = y;
        posInit[2] = z;
        firstPos = false;
    }
    this->getNode()->setPosition(x, y, z);
}