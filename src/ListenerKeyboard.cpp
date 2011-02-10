#include "ListenerKeyboard.h"

ListenerKeyboard::ListenerKeyboard(OIS::InputManager * inputManager, Application * app)
{
	this->inputManager = inputManager;
	this->keyboard = static_cast<OIS::Keyboard*>(inputManager->createInputObject(OIS::OISKeyboard, true));
	this->app = app;
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

bool ListenerKeyboard::keyPressed(const OIS::KeyEvent &evt) {
	float translateSpeed = 2.5;
	
	switch(evt.key)
	{
		case OIS::KC_ESCAPE :

			this->app->shutDown = true;
			break;

		case OIS::KC_UP :
			this->app->_translateZ = -translateSpeed;
			break;

		case OIS::KC_DOWN :
			this->app->_translateZ = translateSpeed;
			break;

		case OIS::KC_LEFT :
			this->app->_translateX = -translateSpeed;
			break;

		case OIS::KC_RIGHT :
			this->app->_translateX = translateSpeed;
			break;
	}

	return true;
}

bool ListenerKeyboard::keyReleased(const OIS::KeyEvent &evt) {


	switch(evt.key)
	{
		case OIS::KC_UP :
		case OIS::KC_DOWN :
			this->app->_translateZ = 0;
			break;

		case OIS::KC_LEFT :
		case OIS::KC_RIGHT :
			this->app->_translateX = 0;
			break;
	}

	return true;
}
