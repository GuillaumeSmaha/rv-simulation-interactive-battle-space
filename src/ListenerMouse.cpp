#include "ListenerMouse.h"

ListenerMouse::ListenerMouse(OIS::InputManager * inputManager, CameraFixeAbstract * gestCamera)
{
	this->inputManager = inputManager;
	this->mouse = static_cast<OIS::Mouse*>(inputManager->createInputObject(OIS::OISMouse, true));
	this->mouse->setEventCallback(this);
	this->gestCamera = gestCamera;
}

ListenerMouse::~ListenerMouse()
{
	this->inputManager->destroyInputObject(this->mouse);
}
void ListenerMouse::capture(void)
{
    this->mouse->capture();
}
CameraFixeAbstract *  ListenerMouse::getCamera(void)
{
    return this->gestCamera;

}
bool ListenerMouse::mouseMoved(const OIS::MouseEvent &evt) {

	float mRotateSpeed = 0.1f;

	this->gestCamera->getCamera()->yaw(Ogre::Degree(-evt.state.X.rel * mRotateSpeed));
	this->gestCamera->getCamera()->pitch(Ogre::Degree(-evt.state.Y.rel * mRotateSpeed));

	return true;
}

bool ListenerMouse::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {

	return true;
}

bool ListenerMouse::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {

	return true;
}
