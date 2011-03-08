#include "ListenerFrame.h"

ListenerFrame::ListenerFrame( Ogre::Root * root): closed(false)
{
   	root->addFrameListener(this);
}

ListenerFrame::~ListenerFrame()
{
}

bool ListenerFrame::frameRenderingQueued(const Ogre::FrameEvent& evt)
{

    if(this->closed)
    {
        return false;
    }

    this->signalFrameRendering.dispatch();
	return true;
}

void ListenerFrame::shutdown(void*)
{
    this->closed = true;

}

bool ListenerFrame::frameStarted(const Ogre::FrameEvent &evt)
{
	this->signalFrameStarted.dispatch(evt);
    return true;
}

bool ListenerFrame::frameEnded(const Ogre::FrameEvent &evt)
{
	this->signalFrameEnded.dispatch(evt);
	return true;
}

