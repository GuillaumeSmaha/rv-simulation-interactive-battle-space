#include "ListenerFrame.h"

ListenerFrame::ListenerFrame()
{
	
}

bool ListenerFrame::frameRenderingQueued(const Ogre::FrameEvent& evt) {
	
	// Stop the rendering if the window was closed, or the application stoped
	/*
	if(this->window->isClosed() || this->shutDown)
		return false;

    // capture value of each device
    this->keyboard->capture();
    this->mouse->capture();
    
    this->gestCamera->getCamera()->moveRelative( Ogre::Vector3(this->_translateX, 0.0f, this->_translateZ) );
	*/
	
	return true;
}
