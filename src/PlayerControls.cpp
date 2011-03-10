#include "PlayerControls.h"

#include "Utils.h"

//~ int PlayerControls::maxOISKeyControl = 0xED+1;
//~ int PlayerControls::maxOISMouseControl = 7;

PlayerControls::PlayerControls(ListenerMouse* mouse, ListenerKeyboard* keyboard)
{    
	this->resetControls();
	
	this->setMouseMovedActif(true);
    
	this->setMouseControl(PlayerControls::SHOOT1, OIS::MB_Left);
	this->setMouseControl(PlayerControls::SHOOT2, OIS::MB_Right);
	
	this->setKeyControl(PlayerControls::QUIT, OIS::KC_F10);
	this->setKeyControl(PlayerControls::ACCELERATION, OIS::KC_UP);
	this->setKeyControl(PlayerControls::BRAKE, OIS::KC_DOWN);
	this->setKeyControl(PlayerControls::LEFT, OIS::KC_LEFT);
	this->setKeyControl(PlayerControls::RIGHT, OIS::KC_RIGHT);
	this->setKeyControl(PlayerControls::UP, OIS::KC_H);
	this->setKeyControl(PlayerControls::DOWN, OIS::KC_N);
	
	this->setKeyControl(PlayerControls::OPEN_MENU, OIS::KC_ESCAPE);
	
	this->setKeyControl(PlayerControls::SWITCH_NEXT_CAMERA, OIS::KC_M); // :
    
    this->keyboard = keyboard;
    this->mouse = mouse;

    this->keyboard->signalKeyPressed.add(&PlayerControls::keyboardPressed, this);
    this->keyboard->signalKeyReleased.add(&PlayerControls::keyboardReleased, this);
    this->mouse->signalMouseMoved.add(&PlayerControls::mouseMoved, this);
    this->mouse->signalMousePressed.add(&PlayerControls::mousePressed, this);
    this->mouse->signalMouseReleased.add(&PlayerControls::mouseReleased, this);
}

PlayerControls::~PlayerControls()
{
    this->keyboard->signalKeyPressed.remove(&PlayerControls::keyboardPressed, this);
    this->keyboard->signalKeyReleased.remove(&PlayerControls::keyboardReleased, this);
    this->mouse->signalMouseMoved.remove(&PlayerControls::mouseMoved, this);
    this->mouse->signalMousePressed.remove(&PlayerControls::mousePressed, this);
    this->mouse->signalMouseReleased.remove(&PlayerControls::mouseReleased, this);
}

void PlayerControls::resetControls(void)
{
	this->setMouseMovedActif(false);
	
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
		for(unsigned int i = 0 ; i < this->listMouseControl.size() ; i++)
		{
			if(this->listMouseControl[i] == keyControl)
				this->listMouseControl[i] = PlayerControls::NONE;
		}
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
		for(unsigned int i = 0 ; i < this->listKeyControl.size() ; i++)
		{
			if(this->listKeyControl[i] == keyControl)
				this->listKeyControl[i] = PlayerControls::NONE;
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
	if(this->getMouseMovedActif())
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
	PlayerControls::Controls key = this->listKeyControl[evt.key];
	
	return key;
}


PlayerControls::Controls PlayerControls::OISEventToControlKey(const OIS::MouseButtonID evt)
{
	PlayerControls::Controls key = this->listMouseControl[evt];
	
	return key;
}

void PlayerControls::suspendre_ecoute()
{
    this->keyboard->signalKeyPressed.remove(&PlayerControls::keyboardPressed, this);
    this->keyboard->signalKeyReleased.remove(&PlayerControls::keyboardReleased, this);
    this->mouse->signalMousePressed.remove(&PlayerControls::mousePressed, this);
    this->mouse->signalMouseMoved.remove(&PlayerControls::mouseMoved, this);
    this->mouse->signalMouseReleased.remove(&PlayerControls::mouseReleased, this);
}

void PlayerControls::reprendre_ecoute()
{
    this->keyboard->signalKeyPressed.add(&PlayerControls::keyboardPressed, this);
    this->keyboard->signalKeyReleased.add(&PlayerControls::keyboardReleased, this);
    this->mouse->signalMouseMoved.add(&PlayerControls::mouseMoved, this);
    this->mouse->signalMousePressed.add(&PlayerControls::mousePressed, this);
    this->mouse->signalMouseReleased.add(&PlayerControls::mouseReleased, this);
}

bool PlayerControls::getMouseMovedActif()
{
	return this->mouseMovedActif;
}

void PlayerControls::setMouseMovedActif(bool mouseMovedActif)
{
	this->mouseMovedActif = mouseMovedActif;
}
