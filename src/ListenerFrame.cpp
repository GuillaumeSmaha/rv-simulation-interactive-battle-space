#include "ListenerFrame.h"

ListenerFrame::ListenerFrame(ListenerKeyboard * keyboard, ListenerMouse * mouse, Application * app)
{
    this->keyboard = keyboard;
    this->mouse = mouse;
    this->app = app;
}

bool ListenerFrame::frameRenderingQueued(const Ogre::FrameEvent& evt) {

	// Stop the rendering if the window was closed, or the application stoped

	if(this->app->listenerWindow->window->isClosed() || this->app->shutDown)
		return false;

    // capture value of each device
    this->keyboard->capture();
    this->mouse->capture();
    if( this->mouse->getCamera() != NULL)
    {
       // Utils::log("test");
        this->mouse->getCamera()->getCamera()->moveRelative( Ogre::Vector3(this->app->_translateX, 0.0f, this->app->_translateZ) );
    }

   // this->mouse->getCamera()->getCamera()->moveRelative( Ogre::Vector3(this->app->_translateX, 0.0f, this->app->_translateZ) );

	return true;
}
