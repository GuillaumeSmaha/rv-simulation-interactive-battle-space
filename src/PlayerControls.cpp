#include "PlayerControls.h"

PlayerControls::PlayerControls(ListenerMouse* mouse, ListenerKeyboard* keyboard)
{
    keyboard->signalKeyPressed.add(&PlayerControls::keyboardPressed, this);
    keyboard->signalKeyReleased.add(&PlayerControls::keyboardReleased, this);
    mouse->signalMouseMoved.add(&PlayerControls::mouseMoved, this);
    mouse->signalMousePressed.add(&PlayerControls::mousePressed, this);
    mouse->signalMouseReleased.add(&PlayerControls::mouseReleased, this);
    //ctor
}

PlayerControls::~PlayerControls()
{
    //dtor
}

void PlayerControls::mouseMoved(Ogre::Vector3 vect)
{
    this->signalMouseMoved.dispatch(vect);
}

void PlayerControls::mousePressed(OIS::MouseButtonID evt)
{
    Controls key = this->OISEventToControlKey(evt);
    if(key != NONE)
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

void PlayerControls::keyboardPressed(const OIS::KeyEvent &evt)
{
    Controls key = this->OISEventToControlKey(evt);
    if(key != NONE)
    {
         this->signalKeyPressed.dispatch(key);
    }
}

PlayerControls::Controls PlayerControls::OISEventToControlKey(OIS::MouseButtonID evt)
{
    PlayerControls::Controls key;
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
	return key;
}

PlayerControls::Controls PlayerControls::OISEventToControlKey(const OIS::KeyEvent &evt)
{
    PlayerControls::Controls key;
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

}

void PlayerControls::keyboardReleased(const OIS::KeyEvent &evt)
{

    Controls key = this->OISEventToControlKey(evt);
    if(key != NONE)
    {
        this->signalKeyReleased.dispatch(key);
    }
}
