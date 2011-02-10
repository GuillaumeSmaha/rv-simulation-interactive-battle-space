#include "ListenerFrame.h"

ListenerFrame::ListenerFrame(ListenerKeyboard * keyboard, ListenerMouse * mouse, Application * app)
{
    this->keyboard = keyboard;
    this->mouse = mouse;
    this->app = app;
}

bool ListenerFrame::frameRenderingQueued(const Ogre::FrameEvent& evt) {

	return true;
}

bool ListenerFrame::frameEnded(const Ogre::FrameEvent& evt)
{
	return true;
}