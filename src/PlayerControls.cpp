#include "PlayerControls.h"

int PlayerControls::maxOISKeyControl = 0xED+1;
int PlayerControls::maxOISMouseControl = 7;

PlayerControls::PlayerControls(ListenerMouse* mouse, ListenerKeyboard* keyboard)
{    
	this->resetControls();
    
	this->setMouseControl(PlayerControls::SHOOT1, OIS::MB_Left);
	this->setMouseControl(PlayerControls::SHOOT2, OIS::MB_Right);
	
	this->setKeyControl(PlayerControls::QUIT, OIS::KC_ESCAPE);
	this->setKeyControl(PlayerControls::ACCELERATION, OIS::KC_UP);
	this->setKeyControl(PlayerControls::BRAKE, OIS::KC_DOWN);
	this->setKeyControl(PlayerControls::LEFT, OIS::KC_LEFT);
	this->setKeyControl(PlayerControls::RIGHT, OIS::KC_RIGHT);
	this->setKeyControl(PlayerControls::UP, OIS::KC_H);
	this->setKeyControl(PlayerControls::DOWN, OIS::KC_N);
	
    keyboard->signalKeyPressed.add(&PlayerControls::keyboardPressed, this);
    keyboard->signalKeyReleased.add(&PlayerControls::keyboardReleased, this);
    mouse->signalMouseMoved.add(&PlayerControls::mouseMoved, this);
    mouse->signalMousePressed.add(&PlayerControls::mousePressed, this);
    mouse->signalMouseReleased.add(&PlayerControls::mouseReleased, this);
}

PlayerControls::~PlayerControls()
{
    //dtor
}

void PlayerControls::resetControls(void)
{
	this->listKeyControl.resize(PlayerControls::maxOISKeyControl);
	for(unsigned int i = 0 ; i < this->listKeyControl.size() ; i++)
		this->listKeyControl[i] = PlayerControls::NONE;
		
	this->listMouseControl.resize(PlayerControls::maxOISMouseControl);
	for(unsigned int i = 0 ; i < this->listMouseControl.size() ; i++)
		this->listMouseControl[i] = PlayerControls::NONE;
}

void PlayerControls::setKeyControl(const PlayerControls::Controls keyControl, const OIS::KeyCode key)
{
	if(key <= PlayerControls::maxOISKeyControl)
	{
		for(unsigned int i = 0 ; i < this->listKeyControl.size() ; i++)
		{
			if(this->listKeyControl[i] == keyControl)
				this->listKeyControl[i] = PlayerControls::NONE;
		}		
		this->listKeyControl[key] = keyControl;
	}
}

void PlayerControls::setMouseControl(const PlayerControls::Controls keyControl, const OIS::MouseButtonID mouseId)
{
	if(mouseId <= PlayerControls::maxOISMouseControl)
	{
		for(unsigned int i = 0 ; i < this->listMouseControl.size() ; i++)
		{
			if(this->listMouseControl[i] == keyControl)
				this->listMouseControl[i] = PlayerControls::NONE;
		}
		this->listMouseControl[mouseId] = keyControl;
	}
}

void PlayerControls::keyboardPressed(const OIS::KeyEvent &evt)
{
    Controls key = this->OISEventToControlKey(evt);
    if(key != PlayerControls::NONE)
    {
         this->signalKeyPressed.dispatch(key);
    }
}

void PlayerControls::keyboardReleased(const OIS::KeyEvent &evt)
{
    Controls key = this->OISEventToControlKey(evt);
    if(key != PlayerControls::NONE)
    {
        this->signalKeyReleased.dispatch(key);
    }
}

void PlayerControls::mouseMoved(Ogre::Vector3 vect)
{
    this->signalMouseMoved.dispatch(vect);
}

void PlayerControls::mousePressed(OIS::MouseButtonID evt)
{
    Controls key = this->OISEventToControlKey(evt);
    if(key != PlayerControls::NONE)
    {
         this->signalKeyPressed.dispatch(key);
    }
}

void PlayerControls::mouseReleased(OIS::MouseButtonID evt)
{
    Controls key = this->OISEventToControlKey(evt);
    if(key != NONE)
    {
         this->signalKeyReleased.dispatch(key);
    }
}

PlayerControls::Controls PlayerControls::OISEventToControlKey(const OIS::KeyEvent &evt)
{
    /*PlayerControls::Controls key;
	switch(evt.key)
	{
		case OIS::KC_ESCAPE :
            key = PlayerControls::QUIT;
			break;

		case OIS::KC_UP :
		case OIS::KC_Z :
            key = PlayerControls::ACCELERATION;
			break;

		case OIS::KC_DOWN :
		case OIS::KC_S :
            key = PlayerControls::BRAKE;
            break;

		case OIS::KC_LEFT :
		case OIS::KC_Q :
            key = PlayerControls::LEFT;
			break;

		case OIS::KC_RIGHT :
		case OIS::KC_D :
            key = PlayerControls::RIGHT;
			break;
	    case OIS::KC_H :
            key = PlayerControls::UP;
			break;
	    case OIS::KC_N :
            key = PlayerControls::DOWN;
			break;

		default:
			key = PlayerControls::NONE;
			break;
	}
	
	return key;
	*/
	
	PlayerControls::Controls key = this->listKeyControl[evt.key];
	
	return key;
}


PlayerControls::Controls PlayerControls::OISEventToControlKey(const OIS::MouseButtonID evt)
{
    /*PlayerControls::Controls key;
    
	switch(evt)
	{
		case OIS::MB_Left :
            key = PlayerControls::SHOOT1;
			break;
		case OIS::MB_Right :
            key = PlayerControls::SHOOT2;
			break;
		default:
			key = PlayerControls::NONE;
			break;
	}
	return key;*/
	
	PlayerControls::Controls key = this->listMouseControl[evt];
	
	return key;
}
