#include "PlayerControls.h"

PlayerControls::PlayerControls(/*ListenerMouse* mouse,*/ ListenerKeyboard* keyboard)
{
    keyboard->signalKeyPressed.add(&PlayerControls::keyboardPressed, this);
    keyboard->signalKeyReleased.add(&PlayerControls::keyboardReleased, this);
    //ctor
}

PlayerControls::~PlayerControls()
{
    //dtor
}

void PlayerControls::keyboardPressed(const OIS::KeyEvent &evt)
{
    this->signalKeyPressed.dispatch(this->OISEventToControlKey(evt));

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
            key = PlayerControls::ACCELERATION;
			break;

		case OIS::KC_DOWN :
            key = PlayerControls::BRAKE;
            break;

		case OIS::KC_LEFT :
            key = PlayerControls::LEFT;
			break;

		case OIS::KC_RIGHT :
            key = PlayerControls::RIGHT;
			break;
	}
	return key;

}
void PlayerControls::keyboardReleased(const OIS::KeyEvent &evt)
{

    this->signalKeyReleased.dispatch(this->OISEventToControlKey(evt));
}
