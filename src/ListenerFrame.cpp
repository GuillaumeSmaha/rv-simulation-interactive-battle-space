#include "ListenerFrame.h"

ListenerFrame::ListenerFrame(Application * app, Ogre::Root * root)
{
    this->app = app;
	root->addFrameListener(this);
}

ListenerFrame::~ListenerFrame()
{
}

bool ListenerFrame::frameRenderingQueued(const Ogre::FrameEvent& evt)
{

	// Stop the rendering if the window was closed, or the application stoped
	if(this->app->getListenerWindow()->getRenderWindow()->isClosed() || this->app->getShutDown())
	{
		return false;
	}

    // capture value of each device
    this->app->getListenerMouse()->getMouse()->capture();
	this->app->getListenerKeyboard()->getKeyboard()->capture();

	if (this->app->timeUntilNextToggle >= 0)
		this->app->timeUntilNextToggle -= evt.timeSinceLastFrame;
    
    this->app->getGestCamera()->getCamera()->moveRelative( Ogre::Vector3(this->app->_translateX, 0.0f, this->app->_translateZ) );
    
	return true;
}

bool ListenerFrame::frameEnded(const Ogre::FrameEvent& evt)
{
	this->app->updateStats();
	return true;
}
