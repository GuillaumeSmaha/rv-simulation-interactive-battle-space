#include "ShipPlayer.h"

using namespace Ogre;

ShipPlayer::ShipPlayer(PlayerControls * pControl) : ShipAbstract()
{
	pControl->signalKeyPressed.add(&ShipPlayer::keyPressed, this);
	pControl->signalMouseMoved.add(&ShipPlayer::mouseMoved, this);

	this->typeCamera = CameraFixeAbstract::CAMERA_NULL;
	this->gestCamera = NULL;


    this->nodeCameraTarget = this->getNode()->createChildSceneNode("cameraTarget"+Utils::toString(Utils::unique()));
    this->nodeCameraFirstPerson = this->getNode()->createChildSceneNode("cameraFirstPerson"+Utils::toString(Utils::unique()));
	this->nodeCameraExterieureFixe = this->getNode()->createChildSceneNode("cameraExterieurFixe"+Utils::toString(Utils::unique()));


	this->nodeCameraTarget->setPosition(0, 15, 60);
	this->nodeCameraFirstPerson->setPosition(0, 15, 30);
	this->nodeCameraExterieureFixe->setPosition(0, 150, -300);

	this->initCamera(CameraFixeAbstract::CAMERA_EXTERIEURE_FIXE);
}

ShipPlayer::~ShipPlayer(void)
{
    GestSceneManager::remCamera(this->gestCamera);
	delete this->gestCamera;
}

void ShipPlayer::updatePosition(void)
{
	Vector3 position = this->getPosition();
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
		this->setRollSpeed(this->getRollSpeed()-Ogre::Radian(0.001));
		if(this->getRollSpeed() < Ogre::Radian(0))
			this->setRollSpeed(Ogre::Radian(0));
	}
    else if(this->getRollSpeed() < Ogre::Radian(0))
    {
		this->setRollSpeed(this->getRollSpeed()+Ogre::Radian(0.001));
		if(this->getRollSpeed() > Ogre::Radian(0))
			this->setRollSpeed(Ogre::Radian(0));
	}

	if(this->getYawSpeed() > Ogre::Radian(0))
    {
		this->setYawSpeed(this->getYawSpeed()-Ogre::Radian(0.001));
		if(this->getYawSpeed() < Ogre::Radian(0))
			this->setYawSpeed(Ogre::Radian(0));
	}
    else if(this->getYawSpeed() < Ogre::Radian(0))
    {
		this->setYawSpeed(this->getYawSpeed()+Ogre::Radian(0.001));
		if(this->getYawSpeed() > Ogre::Radian(0))
			this->setYawSpeed(Ogre::Radian(0));
	}

    if(this->getPitchSpeed() > Ogre::Radian(0))
    {
		this->setPitchSpeed(this->getPitchSpeed()-Ogre::Radian(0.001));
		if(this->getPitchSpeed() < Ogre::Radian(0))
			this->setPitchSpeed(Ogre::Radian(0));
	}
    else if(this->getPitchSpeed() < Ogre::Radian(0))
    {
		this->setPitchSpeed(this->getPitchSpeed()+Ogre::Radian(0.001));
		if(this->getPitchSpeed() > Ogre::Radian(0))
			this->setPitchSpeed(Ogre::Radian(0));
	}

    /*this->setAcceleration(0);
    this->setPitchAcceleration(Ogre::Radian(0));
    this->setRollAcceleration(Ogre::Radian(0));
    */

    this->gestCamera->update_camera();
}

void ShipPlayer::initCamera(CameraFixeAbstract::CameraType type)
{
	if(this->gestCamera == NULL && type != CameraFixeAbstract::CAMERA_NULL)
	{
		this->typeCamera = type;

		switch(this->typeCamera)
		{
			case CameraFixeAbstract::CAMERA_FIXE :
				this->gestCamera = new CameraFixe(MeshLoader::getSingleton()->getSceneManager(), "cameraFixe"+Utils::toString(Utils::unique()));
				break;

			case CameraFixeAbstract::CAMERA_FISRT_PERSON :
				this->gestCamera = new CameraFixeTarget(MeshLoader::getSingleton()->getSceneManager(), "cameraFirstPerson"+Utils::toString(Utils::unique()), this->getNodeCameraTarget(), this->getNodeCameraFirstPerson());
				break;

			case CameraFixeAbstract::CAMERA_EXTERIEURE_FIXE :
				this->gestCamera = new CameraFixeTarget(MeshLoader::getSingleton()->getSceneManager(), "cameraExterieureFixe"+Utils::toString(Utils::unique()), this->getNodeCameraTarget(), this->getNodeCameraExterieureFixe());
				break;
		}

		this->gestCamera->init_camera();
		GestSceneManager::addCamera(this->gestCamera);

		this->idViewport = ViewportLoader::getSingleton()->addViewport(this->gestCamera);
	}
}

void ShipPlayer::changeCamera(CameraFixeAbstract::CameraType type)
{
	if(this->typeCamera != type && type != CameraFixeAbstract::CAMERA_NULL)
	{
		this->typeCamera = type;
		CameraFixeAbstract * tmpGestCamera = this->gestCamera;

		switch(this->typeCamera)
		{
			case CameraFixeAbstract::CAMERA_FIXE :
				this->gestCamera = new CameraFixe(MeshLoader::getSingleton()->getSceneManager(), "cameraFixe"+Utils::toString(Utils::unique()));
				break;

			case CameraFixeAbstract::CAMERA_FISRT_PERSON :
				this->gestCamera = new CameraFixeTarget(MeshLoader::getSingleton()->getSceneManager(), "cameraFirstPerson"+Utils::toString(Utils::unique()), this->getNodeCameraTarget(), this->getNodeCameraFirstPerson());
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

void ShipPlayer::keyPressed(PlayerControls::Controls key)
{
    Quaternion r(Degree(90), Vector3::UNIT_X);
    Quaternion orientation;
    switch(key)
	{
		case PlayerControls::SHOOT1 :
            this->exploded();
            break;
		case PlayerControls::ACCELERATION :
            this->accelerate(1);
            break;
        case PlayerControls::BRAKE:
            this->accelerate(-1);
            break;
        case PlayerControls::LEFT :
            this->rollAccelerate(Ogre::Radian(-0.02));
			this->translateAccelerate(0.1);
            break;
        case PlayerControls::RIGHT :
            this->rollAccelerate(Ogre::Radian(0.02));
			this->translateAccelerate(-0.1);
            break;
        case PlayerControls::UP :
            this->pitchAccelerate(Ogre::Radian(0.001));
            break;
        case PlayerControls::DOWN :
            this->pitchAccelerate(Ogre::Radian(-0.001));
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
