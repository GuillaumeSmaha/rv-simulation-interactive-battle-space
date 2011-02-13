#include "ListenerKeyboard.h"

ListenerKeyboard::ListenerKeyboard(OIS::InputManager * inputManager)
{
    this->inputManager = inputManager;
	this->keyboard = static_cast<OIS::Keyboard*>(inputManager->createInputObject(OIS::OISKeyboard, true));
	this->keyboard->setEventCallback(this);
}

ListenerKeyboard::~ListenerKeyboard()
{
	this->inputManager->destroyInputObject(this->keyboard);
}

void ListenerKeyboard::capture(void)
{
    this->keyboard->capture();
}

bool ListenerKeyboard::keyPressed(const OIS::KeyEvent &evt)
{
	this->signalKeyPressed.dispatch(evt);
	return true;
}


bool ListenerKeyboard::keyReleased(const OIS::KeyEvent &evt)
{
/*
	switch(evt.key)
	{
		case OIS::KC_UP :
		case OIS::KC_DOWN :
			//this->app->_translateZ = 0;
			break;

		case OIS::KC_LEFT :
		case OIS::KC_RIGHT :
			//this->app->_translateX = 0;
			break;
	}*/
	this->signalKeyReleased.dispatch(evt);

	return true;
}
