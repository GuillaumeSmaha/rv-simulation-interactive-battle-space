#include "ListenerKeyboard.h"

ListenerKeyboard::ListenerKeyboard(OIS::InputManager * inputManager)
{
	this->inputManager = inputManager;
	this->keyboard = static_cast<OIS::Keyboard*>(inputManager->createInputObject(OIS::OISKeyboard, true));
}

ListenerKeyboard::~ListenerKeyboard()
{
	this->inputManager->destroyInputObject(this->keyboard);
}

bool ListenerKeyboard::keyPressed(const OIS::KeyEvent &evt) {
	float translateSpeed = 2.5;
	
	switch(evt.key)
	{
		case OIS::KC_ESCAPE :
			//this->shutDown = true;
			break;
			
		case OIS::KC_UP :
			//this->_translateZ = -translateSpeed;
			break;
			
		case OIS::KC_DOWN :
			//this->_translateZ = translateSpeed;
			break;
			
		case OIS::KC_LEFT :
			//this->_translateX = -translateSpeed;
			break;
			
		case OIS::KC_RIGHT :
			//this->_translateX = translateSpeed;
			break;
	}
    
	return true;
}

bool ListenerKeyboard::keyReleased(const OIS::KeyEvent &evt) {
	
	switch(evt.key)
	{
		case OIS::KC_UP :
		case OIS::KC_DOWN :
			//this->_translateZ = 0;
			break;
			
		case OIS::KC_LEFT :
		case OIS::KC_RIGHT :
			//this->_translateX = 0;
			break;
	}
	
	return true;
}
