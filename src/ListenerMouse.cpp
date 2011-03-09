#include "ListenerMouse.h"

ListenerMouse::ListenerMouse(OIS::InputManager * inputManager)
{
	this->inputManager = inputManager;
	this->mouse = static_cast<OIS::Mouse*>(inputManager->createInputObject(OIS::OISMouse, true));
	this->mouse->setEventCallback(this);
}

ListenerMouse::~ListenerMouse()
{
	this->inputManager->destroyInputObject(this->mouse);
}

void ListenerMouse::capture(void * paramCapture)
{
    this->mouse->capture();
}

bool ListenerMouse::mouseMoved(const OIS::MouseEvent &evt)
{
	this->signalMouseMoved.dispatch(Ogre::Vector3(evt.state.X.rel, evt.state.Y.rel, evt.state.Y.rel));

	return true;
}

bool ListenerMouse::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    this->signalMousePressed.dispatch(id);
	return true;
}

bool ListenerMouse::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{

    this->signalMouseReleased.dispatch(id);
	return true;
}
