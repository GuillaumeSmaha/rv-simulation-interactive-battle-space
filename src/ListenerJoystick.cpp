#include "ListenerJoystick.h"

ListenerJoystick::ListenerJoystick(OIS::InputManager * inputManager)
{
 	this->inputManager = inputManager;
	this->joystick = static_cast<OIS::JoyStick*>(inputManager->createInputObject(OIS::OISJoyStick, true));
	this->joystick->setEventCallback(this);
}

ListenerJoystick::~ListenerJoystick()
{
    //dtor
}

   bool ListenerJoystick::povMoved( const OIS::JoyStickEvent &e, int pov )
   {

       return true;
   }
    bool ListenerJoystick::axisMoved( const OIS::JoyStickEvent &e, int axis )

   {

       return true;
   }
    bool ListenerJoystick::sliderMoved( const OIS::JoyStickEvent &e, int sliderID )

   {

       return true;
   }
    bool ListenerJoystick::buttonPressed( const OIS::JoyStickEvent &e, int button )

   {

       return true;
   }
    bool ListenerJoystick::buttonReleased( const OIS::JoyStickEvent &e, int button )

   {

       return true;
   }
